#pragma once

#include "colony.hpp"
#include "tile.hpp"
#include "settings.hpp"

#include <vector>
#include <memory>

class Board
{
    public:
        explicit Board(const std::unordered_map<Settings, int>& settings);
        const std::vector<Tile*> getAdjacentTiles(const Tile& actualTile) const;

    private:
        void checkSettings() const;
        void createTiles() noexcept;
        void initColonies() noexcept;

        const int row;
        const int column;
        const Tile::Coordinates anthillCoordinates;
        const int numberOfColonies{1}; // TODO : Modifier les settings pour ajouter ce nouveau paramètre (par defaut 1)
        const int initialNumberOfAnts;

        std::vector<std::unique_ptr<Colony>> colonies;
        std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
};