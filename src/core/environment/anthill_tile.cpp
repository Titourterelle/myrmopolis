#include "anthill_tile.hpp"
#include "ant.hpp"

using namespace myrmo;

AnthillTile::AnthillTile(const int x, const int y) noexcept : Tile(x, y) {}

void AnthillTile::interact(Ant &ant) noexcept
{
    if(ant.isTransportingFood())
    {
        ant.dropFood();
        ++food_reserve;
    }
}