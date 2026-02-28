#pragma once

#include "tile.hpp"
#include "pheromones.hpp"

class LandTile : public Tile
{
    public:
        explicit LandTile(const int x, const int y) noexcept;

        void interact(Ant &ant) noexcept override;

        void addPheromones(const PheromoneType& type) noexcept;
        
    private:
        void addFood(const unsigned int quantity = 1) noexcept;
        void removeFood(const unsigned int quantity = 1) noexcept;

        Pheromones pheromones{0, 0};
        int food{0};
};