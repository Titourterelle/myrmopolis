#pragma once

#include "optional"
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace myrmo::snapshot {
    enum class TileType {
        Land,
        Anthill,
        Other
    };

    enum class PheromoneType {
        Home,
        Food,
        Other
    };

    struct Tile {
        unsigned int x;
        unsigned int y;

        TileType type;

        std::unordered_map<PheromoneType, unsigned int> pheromones;

        std::optional<unsigned int> food;
    };

    struct Ant {
        unsigned int id;

        unsigned int x;
        unsigned int y;
    };

    struct Colony {
        std::string name;

        std::vector<Ant> ants;
        std::vector<std::pair<unsigned int, unsigned int>> anthills_coords;
    };

    struct Snapshot {
        unsigned int board_id;
        unsigned int step;
        unsigned int width;
        unsigned int height;

        unsigned int number_of_colonies;
        unsigned int number_of_ants;

        std::vector<Tile> tiles;
        std::vector<Colony> colonies;

    };
}