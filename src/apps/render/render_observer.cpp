#include "render_observer.hpp"
#include "hex_grid.hpp"

#include <cstdlib>
#include <format>
#include <stdexcept>
#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <utility>
#include <set>
#include <vector>

const std::string FRAMES_DIR = "/frames";

// Public

RenderObserver::RenderObserver() : frames_dir(save_dir + FRAMES_DIR) {
    if (std::system("ffmpeg -version > /dev/null 2>&1") != 0) {
        throw std::runtime_error("FFmpeg not found, please install it");
    }
}

void RenderObserver::observe(const myrmo::snapshot::Snapshot &snapshot) {
    snapshots.push_back(snapshot);
}

void RenderObserver::generateVideo(RenderQuality quality) {
    try {
        renderFrames(quality);
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

void RenderObserver::renderFrames(RenderQuality quality) {
    std::filesystem::create_directories(frames_dir);

    float radius;
    if (quality == RenderQuality::Low) {
        radius = 20;
    }
    else if (quality == RenderQuality::Medium) {
        radius = 50;
    }
    else if (quality == RenderQuality::High) {
        radius = 100;
    }
    else {
        radius = 50;
    }
    const HexGrid grid{snapshots[0].width, snapshots[0].height, radius};

    auto makeEven = [](unsigned int v) { return v % 2 == 0 ? v : v + 1; };
    resolution.first  = makeEven(grid.getWidth());
    resolution.second = makeEven(grid.getHeight());

    for (size_t i = 0; i < snapshots.size(); ++i) {
        sf::Image frame = createFrame(snapshots[i], grid);
        
        if (!frame.saveToFile(framePath(i))) {
            throw std::runtime_error("Can't save the frame");
        }
    }
}

sf::Image RenderObserver::createFrame(const myrmo::snapshot::Snapshot &snapshot, const HexGrid &grid) const {
    sf::RenderTexture texture{{resolution.first, resolution.second}};

    texture.clear(sf::Color::Black);
    
    sf::CircleShape hexagon{grid.getCellsRadius(), 6};
    hexagon.setOutlineThickness(2);
    hexagon.setOutlineColor(sf::Color::Black);

    std::set<std::pair<int, int>> anthills = getAnthillsCoord(snapshot);
    std::map<std::pair<int, int>, RenderObserver::FoodIntesity> tile_food = getTileFoodIntensity(snapshot);

    for (const auto& cell : grid.getHexCells()) {
        std::pair<int, int> cell_coords{cell.coord_x, cell.coord_y};
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
        
        hexagon.setPosition({cell.pixel_x, cell.pixel_y});
        texture.draw(hexagon);
    }


    const float ant_radius = grid.getCellsRadius()/10;
    sf::CircleShape circle{ant_radius};
    circle.setOrigin({ant_radius, ant_radius});
    circle.setFillColor(sf::Color::Blue);

    std::set<std::pair<int, int>> ants = getAntsCoord(snapshot);

    for (const auto &ant : ants) {
        std::pair<float, float> center = grid.getCellCenter(ant);

        circle.setPosition({center.first, center.second});

        texture.draw(circle);
    }

    return texture.getTexture().copyToImage();
}

std::set<std::pair<int, int>> RenderObserver::getAnthillsCoord(const myrmo::snapshot::Snapshot &snapshot) const noexcept {
    std::set<std::pair<int, int>> anthills;
    
    for (const auto &colony : snapshot.colonies) {
        for (const auto &anthill : colony.anthills_coords) {
            anthills.insert(anthill);
        }
    }

    return anthills;
}

std::set<std::pair<int, int>> RenderObserver::getAntsCoord(const myrmo::snapshot::Snapshot &snapshot) const noexcept {
    std::set<std::pair<int, int>> ants;
    
    for (const auto &colony : snapshot.colonies) {
        for (const auto &ant : colony.ants) {
            ants.insert({ant.x, ant.y});
        }
    }

    return ants;
}

std::map<std::pair<int, int>, RenderObserver::FoodIntesity> RenderObserver::getTileFoodIntensity(const myrmo::snapshot::Snapshot &snapshot) const noexcept {
    std::map<std::pair<int, int>, FoodIntesity> food_per_tile;
    
    for (const auto& tile : snapshot.tiles) {
        std::pair<int, int> coords{tile.x, tile.y};
        
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


std::string RenderObserver::framePath(size_t index) const noexcept {
    return std::format("{}/frame_{:06d}.png", frames_dir, index);
}

void RenderObserver::encodeVideo() const {
    const std::string command = std::format(
        "ffmpeg -r {} -i {}/frame_%06d.png -c:v libx264 -pix_fmt yuv420p {}/output.mp4 -loglevel error",
        fps,
        frames_dir,
        save_dir
    );

    const int result = std::system(command.c_str());
    if (result != 0) {
        throw std::runtime_error("FFmpeg failed with code : " + std::to_string(result));
    }
}

void RenderObserver::clean() const noexcept {
    if (std::filesystem::exists(frames_dir)) {
        std::filesystem::remove_all(frames_dir);
    }
}