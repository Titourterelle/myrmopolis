#pragma once

#include "environment/tile.hpp"

class Board;
class Colony;

class Ant
{
    public:
        explicit Ant(Colony &colony, Tile &spawnTile) noexcept;
        bool isTransportingFood() const noexcept;
        void act() noexcept;
        void pickFood();
        void dropFood() noexcept;

    private:
        void move(Tile &nextTile) noexcept;
        

        Tile *actualTile = nullptr;
        const Colony *colony;
        const Board *board;
        bool transportFood = false;
};