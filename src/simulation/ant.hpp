#pragma once

#include "environment/tile.hpp"
#include "environment/pheromones.hpp"

class Colony;

class Ant
{
    public:
        explicit Ant(Colony &colony, Tile &spawnTile) noexcept;
        bool isTransportingFood() const noexcept;
    
    private:
        void move(Tile& nextTile) noexcept;
        void pickFood();
        void dropFood() noexcept;
        void depositPheromones(const PheromoneType type) const noexcept;

        Tile *actualTile = nullptr;
        const Colony *colony;
        bool transportFood = false;
};