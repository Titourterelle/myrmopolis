#ifndef __BOARD__
#define __BOARD__

#include "tile.hpp"

#include <vector>

class Board
{
    public:
        Board(const int row, const int column);

    private:
        void setDimensions(const int row, const int column);
        void createTiles() noexcept;

        int row;
        int column;
        
        std::vector<std::vector<Tile>> tiles;
};

#endif