#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace myrmo {
    namespace snapshot {

        enum class TileType
        {
            Land,
            Anthill,
            Other
        };

        enum class PheromoneType
        {
            Home,
            Food,
            Other
        };

        struct Tile
        {
            int x;
            int y;
            
            TileType type;

            std::unordered_map<PheromoneType, int> pheromones;

        };

        struct Ant
        {
            int x;
            int y;
        };

        struct Colony
        {
            std::string name;

            std::vector<Ant> ants;
            std::vector<std::pair<int, int>> anthills_coords;
        };

        struct Snapshot
        {
            int board_id;
            int step;
            int width;
            int height;
                
            int number_of_colonies;
            int number_of_ants;
                
            std::vector<Tile> tiles;
            std::vector<Colony> colonies;
                
        };

    }
}