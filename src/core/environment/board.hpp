#pragma once

#include "settings.hpp"
#include "anthill_tile.hpp"
#include "tile.hpp"
#include "simulation/colony.hpp"

#include <unordered_map>
#include <utility>
#include <vector>
#include <memory>

class Board
{
    public:
        explicit Board(const BoardSettings &settings);
        const std::vector<Tile*> getAdjacentTiles(const Tile &tile) const noexcept;
        void step() const noexcept;

    private:
        void checkSettings() const;
        void createTiles() noexcept;
        void initColonies() noexcept;

        const std::pair<int, int> dimensions;
        const BoardSettings board_settings;

        std::unordered_map<std::string, AnthillTile*> starting_anthills;
        
        std::vector<std::unique_ptr<Colony>> colonies;
        std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
};