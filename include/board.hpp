#ifndef BOARD
#define BOARD

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

        const int row;
        const int column;
        const Tile::Coordinates anthillCoordinates;
        const int initialNumberOfAnts;

        std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
};

#endif