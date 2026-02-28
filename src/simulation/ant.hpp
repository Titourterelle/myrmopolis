#pragma once

#include "environment/tile.hpp"

class Board;
class Colony;

class Ant
{
    public:
        explicit Ant(Colony &colony, Tile &spawn_tile) noexcept;
        bool isTransportingFood() const noexcept;
        void act() noexcept;
        void pickFood();
        void dropFood() noexcept;

    private:
        void move(Tile &next_tile) noexcept;
        

        Tile *actual_tile = nullptr;
        const Colony *colony;
        const Board *board;
        bool is_transporting_food = false;
};