#ifndef ANTHILL
#define ANTHILL

#include "tile.hpp"

class Anthill : public Tile
{
    public:
        Anthill(const int row, const int column) noexcept;
};

#endif