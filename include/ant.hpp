#pragma once

#include "tile.hpp"

class Colony;

class Ant
{
    public:
        explicit Ant(Colony &colony) noexcept;
        bool isTransportingFood() const noexcept;
    
    private:
        void move(Tile& nextTile) noexcept;
        void pickFood() noexcept;
        void dropFood() noexcept;

        Tile *actualTile = nullptr;
        const Colony *colony;
        bool transportFood = false;
};