#pragma once

#include "map_utils.hpp"
#include "environment/anthill_tile.hpp"

#include <random>
#include <set>

namespace myrmo {

class MapGenerator {
    public:
        explicit MapGenerator(MapSettings  settings);

        [[nodiscard]] std::vector<AnthillTile*> createMap(TileMap& map);

    private:
        std::set<Tile::Coordinates> chooseAnthillsCoords(unsigned int height, unsigned int width);

        const MapSettings settings_;
        std::mt19937 random_engine_;
        std::bernoulli_distribution is_containing_food_distrib_;
        std::uniform_int_distribution<> quantity_food_distrib_;
    };

}
