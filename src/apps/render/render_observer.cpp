#include "render_observer.hpp"
#include "hex_grid.hpp"
#include "render_utils.hpp"

#include <cmath>
#include <numbers>
#include <cstddef>
#include <cstdlib>
#include <format>
#include <stdexcept>
#include <string>
#include <set>
#include <map>
#include <utility>
#include <vector>
#include <random>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Angle.hpp>

const std::string FRAMES_DIR = "/frames";

// Public

RenderObserver::RenderObserver() {
    if (std::system("ffmpeg -version > /dev/null 2>&1") != 0) {
        throw std::runtime_error("FFmpeg not found, please install it");
    }
    if(!ant_image.loadFromFile("../../assets/img/ant_64x64.png")) {
        throw std::runtime_error("Can't load the ant image");
    }
}

void RenderObserver::observe(const myrmo::snapshot::Snapshot &snapshot) {
    snapshots.push_back(snapshot);
}

void RenderObserver::generateVideo(const RenderSettings &render_settings) {
    settings = render_settings;
    try {
        renderFrames();
        encodeVideo();
    } catch (const std::exception& e) {
        clean();
        throw;
    }
    clean();
}

// Private

enum class RenderObserver::FoodIntesity {
    None,
    Low,
    Medium,
    High,
    Ultra
};

void RenderObserver::renderFrames() {
    std::filesystem::create_directories(settings.frames_dir);

    float radius;
    if (settings.quality == RenderQuality::Low) {
        radius = 20;
    }
    else if (settings.quality == RenderQuality::Medium) {
        radius = 50;
    }
    else if (settings.quality == RenderQuality::High) {
        radius = 100;
    }
    else {
        radius = 50;
    }
    const HexGrid grid{snapshots[0].width, snapshots[0].height, radius};

    auto makeEven = [](unsigned int v) { return v % 2 == 0 ? v : v + 1; };
    resolution.first  = makeEven(grid.getWidth());
    resolution.second = makeEven(grid.getHeight());

    current_snapshot = snapshots[0];

    for (size_t i = 0; i < snapshots.size(); ++i) {
        previous_snapshot = current_snapshot;
        current_snapshot = snapshots[i];
        createStepFrames(grid);
    }
}

void RenderObserver::createStepFrames(const HexGrid &grid) {
    sf::RenderTexture base{{resolution.first, resolution.second}};

    base.clear(sf::Color::Black);

    // Grid
    sf::CircleShape hexagon{grid.getCellsRadius(), 6};
    hexagon.setOutlineThickness(2);
    hexagon.setOutlineColor(sf::Color::Black);

    std::set<sf::Vector2i, Vector2iCompare> anthills = getAnthillsCoord(previous_snapshot);
    std::map<sf::Vector2i, RenderObserver::FoodIntesity, Vector2iCompare> tile_food = getTileFoodIntensity(previous_snapshot);

    for (const auto& cell : grid.getHexCells()) {
        const sf::Vector2i cell_coords{cell.coords.x, cell.coords.y};
        if (anthills.contains(cell_coords)) {
            hexagon.setFillColor(sf::Color::Red);
        }
        else {
            switch (tile_food.at(cell_coords)) {
                case RenderObserver::FoodIntesity::None :
                    hexagon.setFillColor(sf::Color::White);
                    break;

                    case RenderObserver::FoodIntesity::Low :
                    hexagon.setFillColor(sf::Color{0, 250, 125});
                    break;
                    
                    case RenderObserver::FoodIntesity::Medium :
                    hexagon.setFillColor(sf::Color{0, 200, 100});
                    break;
                    
                    case RenderObserver::FoodIntesity::High :
                    hexagon.setFillColor(sf::Color{0, 150, 75});
                    break;
                    
                    case RenderObserver::FoodIntesity::Ultra :
                    hexagon.setFillColor(sf::Color{0, 100, 50});
                    break;
            }
        }
        
        hexagon.setPosition({cell.px.x, cell.px.y});
        base.draw(hexagon);
    }
    base.display();

    // Ants
    std::set<unsigned int> new_ants = updateAntsCoords(current_snapshot);
    updateAntsOffsets(new_ants, grid);
    
    sf::RenderTexture frame_texture{{resolution.first, resolution.second}};

    const sf::Vector2f ant_size = {grid.getCellsRadius()/ant_image.getSize().x, grid.getCellsRadius()/ant_image.getSize().y};
    
    sf::Sprite ant_sprite{ant_image};
    ant_sprite.setOrigin(sf::Vector2f(ant_image.getSize()) / 2.f);
    ant_sprite.setScale(ant_size);

    for (int i = 0; i < settings.frame_per_step; ++i) {
        frame_texture.clear();
        frame_texture.draw(sf::Sprite(base.getTexture()));
        drawAnts(frame_texture, ant_sprite, (float)i/settings.frame_per_step);
        frame_texture.display();

        const sf::Image frame = frame_texture.getTexture().copyToImage();

        if (!frame.saveToFile(framePath(i + current_snapshot.step*settings.frame_per_step))) {
            throw std::runtime_error("Can't save the frame");
        }
    }
}

void RenderObserver::drawAnts(sf::RenderTexture &frame_texture, sf::Sprite &ant_sprite, float t) const {
    const float ease = easeInOut(t);

    for (const auto& [id, ant] : ants_by_id) {
        const sf::Vector2f delta = ant.current_offset - ant.previous_offset;
        const sf::Vector2f pos = ant.previous_offset + (delta)*ease;
        const sf::Angle direction = sf::radians(std::atan2(delta.y, delta.x) + std::numbers::pi/2);

        ant_sprite.setPosition(pos);
        ant_sprite.setRotation(direction);
        
        frame_texture.draw(ant_sprite);
    }
}

std::set<sf::Vector2i, Vector2iCompare> RenderObserver::getAnthillsCoord(const myrmo::snapshot::Snapshot &snapshot) const noexcept {
    std::set<sf::Vector2i, Vector2iCompare> anthills;
    
    for (const auto& colony : snapshot.colonies) {
        for (const auto& anthill : colony.anthills_coords) {
            anthills.insert({anthill.first, anthill.second});
        }
    }

    return anthills;
}

std::map<sf::Vector2i, RenderObserver::FoodIntesity, Vector2iCompare> RenderObserver::getTileFoodIntensity(const myrmo::snapshot::Snapshot &snapshot) const noexcept {
    std::map<sf::Vector2i, FoodIntesity, Vector2iCompare> food_per_tile;
    
    for (const auto& tile : snapshot.tiles) {
        sf::Vector2i coords{tile.x, tile.y};
        
        if (!tile.food.has_value() || tile.food <= 0) {
            food_per_tile.insert({coords, FoodIntesity::None});
        }
        else if (tile.food < 5) {
            food_per_tile.insert({coords, FoodIntesity::Low});
        }
        else if (tile.food < 10) {
            food_per_tile.insert({coords, FoodIntesity::Medium});
        }
        else if (tile.food < 15) {
            food_per_tile.insert({coords, FoodIntesity::High});
        }
        else {
            food_per_tile.insert({coords, FoodIntesity::Ultra});
        }
    }

    return food_per_tile;
}

std::set<unsigned int> RenderObserver::updateAntsCoords(const myrmo::snapshot::Snapshot &snapshot) noexcept {
    std::set<unsigned int> new_ids;

    for (const auto& colony : snapshot.colonies) {
        for (const auto& ant : colony.ants) {

            if (ants_by_id.contains(ant.id)) {
                AntVisual *ant_visual = &ants_by_id.at(ant.id);

                ant_visual->previous_tile = ant_visual->current_tile;
                ant_visual->current_tile = sf::Vector2i{ant.x, ant.y};
            }
            else {
                AntVisual *ant_visual = &ants_by_id[ant.id];
                ant_visual->current_tile = sf::Vector2i{ant.x, ant.y};
                ant_visual->previous_tile = ant_visual->current_tile;

                new_ids.insert(ant.id);
            }
        }
    }

    return new_ids;
}

void RenderObserver::updateAntsOffsets(std::set<unsigned int> new_ants, const HexGrid &grid) noexcept {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    static std::uniform_real_distribution<> rho_dis(0, 1);
    static std::uniform_real_distribution<> theta_dis(0, 2*std::numbers::pi);

    const float radius = grid.getCellsRadius()*std::sqrt(3)/2;

    for (auto& [id, ant] : ants_by_id) {
        const sf::Vector2f current_pos = grid.getCellCenter(ant.current_tile);

        if (new_ants.contains(id)) {
            ant.current_offset = current_pos;
            ant.previous_offset = ant.current_offset;
            continue;
        }

        const float rho = radius*std::sqrt(rho_dis(gen));
        const float theta = theta_dis(gen);

        sf::Vector2f random_delta{rho*std::cos(theta), rho*std::sin(theta)};

        ant.previous_offset = ant.current_offset;
        ant.current_offset = current_pos + random_delta;
    }
}

std::string RenderObserver::framePath(size_t index) const noexcept {
    return std::format("{}/frame_{:06d}.png", settings.frames_dir, index);
}

void RenderObserver::encodeVideo() const {
    const std::string command = std::format(
        "ffmpeg -r {} -i {}/frame_%06d.png -c:v libx264 -pix_fmt yuv420p {}/output.mp4 -loglevel error",
        settings.fps,
        settings.frames_dir,
        settings.output_dir
    );

    const int result = std::system(command.c_str());
    if (result != 0) {
        throw std::runtime_error("FFmpeg failed with code : " + std::to_string(result));
    }
}

void RenderObserver::clean() const noexcept {
    if (std::filesystem::exists(settings.frames_dir)) {
        std::filesystem::remove_all(settings.frames_dir);
    }
}