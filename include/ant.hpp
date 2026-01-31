#ifndef ANT
#define ANT

#include "tile.hpp"

class Ant
{
    public:
        Ant() noexcept;
    
    private:
        void move(Tile &nextTile) noexcept;

        Tile *actualTile = nullptr;
};

#endif