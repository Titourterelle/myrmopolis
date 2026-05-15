#pragma once

#include "tile.hpp"
#include "pheromones.hpp"
#include "snapshot.hpp"

namespace myrmo {

class LandTile : public Tile {
    public:
        explicit LandTile(const int x, const int y) noexcept;

        void interact(Ant &ant) noexcept override;
        snapshot::Tile takeTileSnapshot() const noexcept override;

        void addPheromones(const PheromoneType &type) noexcept;
        
    private:
        void addFood(const unsigned int quantity = 1) noexcept;
        void removeFood(const unsigned int quantity = 1) noexcept;

        int food{3};
};

}