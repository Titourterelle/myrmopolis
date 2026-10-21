#pragma once

#include "pheromones.hpp"
#include "snapshot.hpp"
#include "tile.hpp"

namespace myrmo {

class LandTile : public Tile {
    public:
        explicit LandTile(unsigned int x, unsigned int y, unsigned int food = 0) noexcept;
        explicit LandTile(Coordinates coords, unsigned int food = 0) noexcept;

        void interact(Ant& ant) noexcept override;
        [[nodiscard]] snapshot::Tile takeTileSnapshot() const noexcept override;

        void addPheromones(const PheromoneType& type) noexcept;

    private:
        void addFood(unsigned int quantity = 1) noexcept;
        void removeFood(unsigned int quantity = 1) noexcept;

        unsigned int food_;
};

}