#pragma once

#include "anthill.hpp"
#include "colony.hpp"
#include "tile.hpp"
#include "settings.hpp"

#include <unordered_map>
#include <utility>
#include <vector>
#include <memory>

class Board
{
    public:
        explicit Board(const SimulationSettings& settings);
        const std::vector<Tile*> getAdjacentTiles(const Tile& actualTile) const;

    private:
        void checkSettings() const;
        void createTiles() noexcept;
        void initColonies() noexcept;

        const std::pair<int, int> dimensions;
        const SimulationSettings simulationSettings;

        std::unordered_map<std::string, Anthill*> startingAnthills;
        std::vector<std::unique_ptr<Colony>> colonies;
        std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
};