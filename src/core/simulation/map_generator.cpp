#include "map_generator.hpp"
#include "map_utils.hpp"
#include "environment/anthill_tile.hpp"
#include "environment/land_tile.hpp"

#include <algorithm>
#include <random>

namespace myrmo {

// Public

MapGenerator::MapGenerator(const MapSettings settings) :
    settings_(settings),
    random_engine_(settings_.seed),
    is_containing_food_distrib_(0.3),
    quantity_food_distrib_(1, 10) {}

std::vector<AnthillTile*> MapGenerator::createMap(TileMap& map) {
    std::vector<AnthillTile*> anthills;
    const std::set<Tile::Coordinates> anthills_coords = chooseAnthillsCoords(map.height, map.width);

    for (auto x = 0; x < map.width; x++) {
        for (auto y = 0; y < map.height; y++) {
            Tile::Coordinates coords(x, y);

            if (anthills_coords.contains(coords)) {
                map.tiles.push_back(std::make_unique<AnthillTile>(coords));             // No need to check the cast
                anthills.push_back(dynamic_cast<AnthillTile*>(map.tiles.back().get()));   // unless changes
                continue;
            }

            map.tiles.push_back(std::make_unique<LandTile>(coords));
        }
    }
    return anthills;
}

// Private

std::set<Tile::Coordinates> MapGenerator::chooseAnthillsCoords(const unsigned int height, const unsigned int width) {
    // TODO : improve algorithme performance
    std::vector<Tile::Coordinates> existing_coords;
    std::set<Tile::Coordinates> anthills_coords;

    for (auto x = 0; x < width; x++) {
        for (auto y = 0; y < height; y++) {
            existing_coords.push_back(Tile::Coordinates(x, y));
        }
    }

    std::ranges::shuffle(existing_coords, random_engine_);

    const size_t count = std::min(settings_.number_of_colonies, existing_coords.size());
    anthills_coords.insert(existing_coords.begin(), existing_coords.begin() + static_cast<long>(count));

    return anthills_coords;
}
}
