#pragma once

#include "tile.hpp"

namespace myrmo {

class AnthillTile : public Tile
{
    public:
        explicit AnthillTile(const int x, const int y) noexcept;

        std::string getType() const noexcept override {return "anthill";};
        void interact(Ant &ant) noexcept override;

    private:
        int food_reserve{0};
};

}