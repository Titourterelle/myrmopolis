#ifndef ANTHILL
#define ANTHILL

#include "tile.hpp"

class Anthill : public Tile
{
    public:
        explicit Anthill(const int row, const int column) noexcept;
};

#endif