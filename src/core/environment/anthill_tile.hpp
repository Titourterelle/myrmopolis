#pragma once

#include "snapshot.hpp"
#include "tile.hpp"

namespace myrmo {

class AnthillTile : public Tile {
    public:
        explicit AnthillTile(unsigned int x, unsigned int y) noexcept;
        explicit AnthillTile(Coordinates coords) noexcept;

        void interact(Ant& ant) noexcept override;
        [[nodiscard]] snapshot::Tile takeTileSnapshot() const noexcept override;
        
    private:
        int food_reserve_ = 0;
};

}