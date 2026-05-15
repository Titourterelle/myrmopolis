#pragma once

#include "tile.hpp"
#include "snapshot.hpp"

namespace myrmo {

class AnthillTile : public Tile {
    public:
        explicit AnthillTile(const int x, const int y) noexcept;

        void interact(Ant &ant) noexcept override;
        snapshot::Tile takeTileSnapshot() const noexcept override;
        
    private:
        int food_reserve{0};
};

}