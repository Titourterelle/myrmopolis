#pragma once

#include "map_utils.hpp"

#include <random>

namespace myrmo {

class MapGenerator {
    public:
        explicit MapGenerator(MapSettings  settings);

        void createMap(TileMap& map) const;

    private:
        const MapSettings settings_;
        const std::mt19937 random_engine_;
    };

}
