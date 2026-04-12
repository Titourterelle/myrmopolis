#pragma once

#include "tile.hpp"
#include "pheromones.hpp"

namespace myrmo {

class LandTile : public Tile
{
    public:
        explicit LandTile(const int x, const int y) noexcept;

        std::string getType() const noexcept override {return "land";};
        void interact(Ant &ant) noexcept override;

        void addPheromones(const PheromoneType &type) noexcept;
        
    private:
        void addFood(const unsigned int quantity = 1) noexcept;
        void removeFood(const unsigned int quantity = 1) noexcept;

        int food{3};
};

}