#pragma once

#include "map_utils.hpp"
#include "environment/anthill_tile.hpp"

#include <random>
#include <set>

namespace myrmo {

class MapGenerator {
    public:
        explicit MapGenerator(const MapSettings &settings);

        [[nodiscard]] std::vector<AnthillTile*> createMap(TileMap& map);

    private:
        std::set<Tile::Coordinates> chooseAnthillsCoords(unsigned int height, unsigned int width) noexcept;
        unsigned int chooseFoodQuantity() noexcept;

        const MapSettings settings_;

        std::mt19937 random_engine_;

    };

}
