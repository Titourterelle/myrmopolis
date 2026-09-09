#pragma once

#include "tile.hpp"
#include "snapshot.hpp"

namespace myrmo {

class AnthillTile : public Tile {
    public:
        explicit AnthillTile(unsigned int x, unsigned int y) noexcept;

        void interact(Ant &ant) noexcept override;
        [[nodiscard]] snapshot::Tile takeTileSnapshot() const noexcept override;
        
    private:
        int food_reserve{0};
};

}