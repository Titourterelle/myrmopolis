#include "anthillTile.hpp"
#include "simulation/ant.hpp"

#include <iostream>

AnthillTile::AnthillTile(const int x, const int y) noexcept : Tile(x, y)
{
    std::cout << "Cette tuile est une fourmilière" << std::endl;
}

void AnthillTile::interact(Ant &ant) noexcept
{
    if(ant.isTransportingFood())
    {
        ant.dropFood();
        ++foodReserve;
    }
}