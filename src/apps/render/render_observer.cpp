#include "render_observer.hpp"
#include "hex_grid.hpp"
#include "progress_bar.hpp"
#include "render_utils.hpp"

#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <format>
#include <map>
#include <numbers>
#include <random>
#include <ranges>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>

#define FRAMES_DIR "/frames"

// Custom types

enum class RenderObserver::FoodIntensity {
    None,
    Low,
    Medium,
    High,
    Ultra
};

struct RenderObserver::AntVisual {
    sf::Vector2u previous_tile;
    sf::Vector2u current_tile;

    sf::Vector2f previous_offset;
    sf::Vector2f current_offset;
};

struct RenderObserver::Board {
    std::vector<myrmo::snapshot::Snapshot> snapshots;
    std::map<unsigned int, AntVisual> ants_by_id;
};


// Public

RenderObserver::RenderObserver() {
    if (std::system("ffmpeg -version > /dev/null 2>&1") != 0) {
        throw std::runtime_error("FFmpeg not found, please install it");
    }
    if(!ant_image_.loadFromFile("../../assets/img/ant_64x64.png")) {
        throw std::runtime_error("Can't load the ant image");
    }
}

RenderObserver::~RenderObserver() = default;

void RenderObserver::observe(const myrmo::snapshot::Snapshot& snapshot) {
    for (const auto& [id, board] : boards_by_id_) {
        if (id == snapshot.board_id) {
            board->snapshots.push_back(snapshot);
            return;
        }
    }

    boards_by_id_[snapshot.board_id] = std::make_unique<Board>();
    boards_by_id_.at(snapshot.board_id)->snapshots.push_back(snapshot);

}

void RenderObserver::generateVideo(const RenderSettings& render_settings, const std::string& base_name) {
    settings_ = render_settings;

    for (const auto& [id, board] : boards_by_id_) {
        current_board_ = board.get();
        const std::string name = std::format("{}-{}", base_name, id);

        try {
            renderFrames();
            encodeVideo(name);
        } catch (const std::exception& e) {
            clean();
            throw;
        }
        clean();
    }
}

void RenderObserver::generateVideo(const std::vector<RenderSettings>& render_settings) {
    int i = 1;
    for (const auto& setting : render_settings){
        const std::string name = std::format("output{}", i++);
        generateVideo(setting, name);
    }
}

// Private

void RenderObserver::renderFrames() {
    std::filesystem::create_directories(settings_.output_dir + FRAMES_DIR);

    current_snapshot_ = &current_board_->snapshots[0];
    const float radius = getCellsRadiusFromQuality(settings_.quality);

    const HexGrid grid{current_snapshot_[0].width, current_snapshot_[0].height, radius};

    auto makeEven = [](const unsigned int v) { return v % 2 == 0 ? v : v + 1; };
    resolution_.first  = makeEven(grid.getWidth());
    resolution_.second = makeEven(grid.getHeight());

    const ProgressBar progress_bar{static_cast<unsigned int>(current_board_->snapshots.size())};

    for (size_t i = 0; i < current_board_->snapshots.size(); ++i) {
        previous_snapshot_ = current_snapshot_;
        current_snapshot_ = &current_board_->snapshots[i];
        createStepFrames(grid);
        
        progress_bar.update(i+1);
    }
}

void RenderObserver::createStepFrames(const HexGrid& grid) {
    sf::RenderTexture base{{resolution_.first, resolution_.second}};

    base.clear(sf::Color::Black);

    // Grid
    sf::CircleShape hexagon{grid.getCellsRadius(), 6};
    hexagon.setOutlineThickness(2);
    hexagon.setOutlineColor(sf::Color::Black);

    const std::set<sf::Vector2u, Vector2uCompare> anthills = getAnthillsCoord(*previous_snapshot_);
    const std::map<sf::Vector2u, FoodIntensity, Vector2uCompare> tile_food = getTileFoodIntensity(*previous_snapshot_);

    for (const auto& [px, coords] : grid.getHexCells()) {
        const sf::Vector2u cell_coords{coords.x, coords.y};
        if (anthills.contains(cell_coords)) {
            hexagon.setFillColor(sf::Color::Red);
        }
        else {
            switch (tile_food.at(cell_coords)) {
                case FoodIntensity::None :
                    hexagon.setFillColor(sf::Color::White);
                    break;

                case FoodIntensity::Low :
                    hexagon.setFillColor(sf::Color{0, 250, 125});
                    break;
                    
                case FoodIntensity::Medium :
                    hexagon.setFillColor(sf::Color{0, 200, 100});
                    break;
                    
                case FoodIntensity::High :
                    hexagon.setFillColor(sf::Color{0, 150, 75});
                    break;
                    
                case FoodIntensity::Ultra :
                    hexagon.setFillColor(sf::Color{0, 100, 50});
                    break;
            }
        }
        
        hexagon.setPosition({px.x, px.y});
        base.draw(hexagon);
    }
    base.display();

    // Ants
    const std::set<unsigned int> new_ants = updateAntsCoords(*current_snapshot_);
    updateAntsOffsets(new_ants, grid);
    
    sf::RenderTexture frame_texture{{resolution_.first, resolution_.second}};

    const sf::Vector2f ant_size = {
        grid.getCellsRadius()/static_cast<float>(ant_image_.getSize().x),
        grid.getCellsRadius()/static_cast<float>(ant_image_.getSize().y)
    };
    
    sf::Sprite ant_sprite{ant_image_};
    ant_sprite.setOrigin(sf::Vector2f(ant_image_.getSize()) / 2.f);
    ant_sprite.setScale(ant_size);

    for (int i = 0; i < settings_.frames_per_step; ++i) {
        frame_texture.clear();
        frame_texture.draw(sf::Sprite(base.getTexture()));
        drawAnts(frame_texture, ant_sprite, static_cast<float>(i)/static_cast<float>(settings_.frames_per_step));
        frame_texture.display();

        const sf::Image frame = frame_texture.getTexture().copyToImage();
        if (!frame.saveToFile(framePath(i + current_snapshot_->step*settings_.frames_per_step))) {
            throw std::runtime_error("Can't save the frame");
        }
    }
}

void RenderObserver::drawAnts(sf::RenderTexture& frame_texture, sf::Sprite& ant_sprite, const float t) const {
    const float ease = easeInOut(t);

    for (const auto& ant : current_board_->ants_by_id | std::views::values) {
        const sf::Vector2f delta = ant.current_offset - ant.previous_offset;
        const sf::Vector2f pos = ant.previous_offset + (delta)*ease;
        const sf::Angle direction = sf::radians(static_cast<float>(std::atan2(delta.y, delta.x) + std::numbers::pi/2));

        ant_sprite.setPosition(pos);
        ant_sprite.setRotation(direction);
        
        frame_texture.draw(ant_sprite);
    }
}


float RenderObserver::getCellsRadiusFromQuality(const RenderQuality& quality) {
    switch (quality)
    {
        case RenderQuality::Low :
            return 20;
        case RenderQuality::Medium :
            return 50;
        case RenderQuality::High :
            return 100;
        default :
            return 50;
    }
}

std::set<sf::Vector2u, Vector2uCompare> RenderObserver::getAnthillsCoord(const myrmo::snapshot::Snapshot& snapshot) noexcept {
    std::set<sf::Vector2u, Vector2uCompare> anthills;
    
    for (const auto& colony : snapshot.colonies) {
        for (const auto& [x, y] : colony.anthills_coords) {
            anthills.insert({x, y});
        }
    }

    return anthills;
}

std::map<sf::Vector2u, RenderObserver::FoodIntensity, Vector2uCompare> RenderObserver::getTileFoodIntensity(const myrmo::snapshot::Snapshot& snapshot) noexcept {
    std::map<sf::Vector2u, FoodIntensity, Vector2uCompare> food_per_tile;
    
    for (const auto& tile : snapshot.tiles) {
        sf::Vector2u coords{tile.x, tile.y};
        
        if (!tile.food.has_value() || tile.food <= 0) {
            food_per_tile.insert({coords, FoodIntensity::None});
        }
        else if (tile.food < 5) {
            food_per_tile.insert({coords, FoodIntensity::Low});
        }
        else if (tile.food < 10) {
            food_per_tile.insert({coords, FoodIntensity::Medium});
        }
        else if (tile.food < 15) {
            food_per_tile.insert({coords, FoodIntensity::High});
        }
        else {
            food_per_tile.insert({coords, FoodIntensity::Ultra});
        }
    }

    return food_per_tile;
}

std::set<unsigned int> RenderObserver::updateAntsCoords(const myrmo::snapshot::Snapshot& snapshot) const noexcept {
    std::set<unsigned int> new_ids;

    for (const auto& colony : snapshot.colonies) {
        for (const auto& [id, x, y] : colony.ants) {

            if (current_board_->ants_by_id.contains(id)) {
                AntVisual *ant_visual = &current_board_->ants_by_id.at(id);

                ant_visual->previous_tile = ant_visual->current_tile;
                ant_visual->current_tile = sf::Vector2u{x, y};
            }
            else {
                AntVisual *ant_visual = &current_board_->ants_by_id[id];
                ant_visual->current_tile = sf::Vector2u{x, y};
                ant_visual->previous_tile = ant_visual->current_tile;

                new_ids.insert(id);
            }
        }
    }

    return new_ids;
}

void RenderObserver::updateAntsOffsets(const std::set<unsigned int>& new_ants, const HexGrid& grid) const noexcept {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    static std::uniform_real_distribution<> rho_dis(0, 1);
    static std::uniform_real_distribution<> theta_dis(0, 2*std::numbers::pi);

    const auto radius = static_cast<float>(grid.getCellsRadius()*std::sqrt(3)/2);

    for (auto& [id, ant] : current_board_->ants_by_id) {
        const sf::Vector2f current_pos = grid.getCellCenter(ant.current_tile);

        if (new_ants.contains(id)) {
            ant.current_offset = current_pos;
            ant.previous_offset = ant.current_offset;
            continue;
        }

        const auto rho = static_cast<float>(radius*std::sqrt(rho_dis(gen)));
        const auto theta = static_cast<float>(theta_dis(gen));

        const sf::Vector2f random_delta{rho*std::cos(theta), rho*std::sin(theta)};

        ant.previous_offset = ant.current_offset;
        ant.current_offset = current_pos + random_delta;
    }
}

std::string RenderObserver::framePath(const size_t index) const noexcept {
    return std::format("{}/frame_{:06d}.png", settings_.output_dir + FRAMES_DIR, index);
}

void RenderObserver::encodeVideo(const std::string& name) const {
    const std::string command = std::format(
        "ffmpeg -r {} -i {}/frame_%06d.png -c:v libx264 -pix_fmt yuv420p {}/{}.mp4 -loglevel error",
        settings_.fps,
        settings_.output_dir + FRAMES_DIR,
        settings_.output_dir,
        name
    );

    const int result = std::system(command.c_str());
    if (result != 0) {
        throw std::runtime_error("FFmpeg failed with code : " + std::to_string(result));
    }
}

void RenderObserver::clean() const noexcept {
    if (std::filesystem::exists(settings_.output_dir + FRAMES_DIR)) {
        std::filesystem::remove_all(settings_.output_dir + FRAMES_DIR);
    }
}