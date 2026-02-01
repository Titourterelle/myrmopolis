#ifndef BOARD
#define BOARD

#include "tile.hpp"
#include "ant.hpp"

#include <vector>

class Board
{
    public:
        Board(const int row, const int column, const int ant);

    private:
        void setDimensions(const int row, const int column);
        void createTiles() noexcept;
        void addAnts(const int numberOfAnts) noexcept;

        int row;
        int column;
        
        std::vector<std::vector<Tile>> tiles;
        std::vector<Ant> ants;
};

#endif