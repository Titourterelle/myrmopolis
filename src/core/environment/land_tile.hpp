#pragma once

#include "tile.hpp"
#include "pheromones.hpp"
#include "snapshot.hpp"

namespace myrmo {

class LandTile : public Tile {
    public:
        explicit LandTile(unsigned int x, unsigned int y) noexcept;

        void interact(Ant &ant) noexcept override;
        [[nodiscard]] snapshot::Tile takeTileSnapshot() const noexcept override;

        void addPheromones(const PheromoneType &type) noexcept;
        
    private:
        void addFood(unsigned int quantity = 1) noexcept;
        void removeFood(unsigned int quantity = 1) noexcept;

        int food{10};
};

}