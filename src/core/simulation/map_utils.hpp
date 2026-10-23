#pragma once

#include "environment/tile.hpp"

#include <memory>
#include <vector>

namespace myrmo {

struct TileMap {
    const unsigned int width, height;
    std::vector<std::unique_ptr<Tile>> tiles;

    TileMap(const unsigned int width, const unsigned int height) : width(width), height(height) {
        tiles.reserve(height * width);
    }
};

struct MapSettings {
    unsigned long seed, number_of_colonies;
    double food_abundance;
};

};