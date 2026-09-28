#include "map_generator.hpp"
#include "map_utils.hpp"
#include "environment/anthill_tile.hpp"
#include "environment/land_tile.hpp"

#include <random>
#include <utility>

namespace myrmo {

MapGenerator::MapGenerator(MapSettings settings) :
    settings_(std::move(settings)),
    random_engine_(settings_.seed) {}

void MapGenerator::createMap(TileMap& map) const {
    for (auto x = 0; x < map.width; x++) {
        for (auto y = 0; y < map.height; y++) {
            Tile::Coordinates coords(x, y);
            if (settings_.anthills_coordinates.contains(coords)) {
                map.tiles.push_back(std::make_unique<AnthillTile>(coords));
            }
            else {
                map.tiles.push_back(std::make_unique<LandTile>(coords));
            }
        }
    }
}

}
