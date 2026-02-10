#ifndef ANT
#define ANT

#include "tile.hpp"

class Ant
{
    public:
        Ant() noexcept;
        bool isTransportingFood() const noexcept;
    
    private:
        void move(Tile &nextTile) noexcept;
        void pickFood() noexcept;
        void dropFood() noexcept;

        Tile *actualTile = nullptr;
        bool transportFood = false;
};

#endif