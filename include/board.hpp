#ifndef BOARD
#define BOARD

#include "tile.hpp"
#include "ant.hpp"
#include "settings.hpp"

#include <vector>
#include <memory>

class Board
{
    public:
        Board(const std::unordered_map<Settings, int>& settings);
        const std::vector<Tile*> getAdjacentTiles(const Tile& actualTile) const;

    private:
        void setDimensions(const int row, const int column);
        void createTiles() noexcept;
        void addAnts(const int numberOfAnts) noexcept;

        int row;
        int column;
        
        std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
        std::vector<Ant> ants;
};

#endif