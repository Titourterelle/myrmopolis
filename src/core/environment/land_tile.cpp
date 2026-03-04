#include "land_tile.hpp"
#include "tile.hpp"
#include "simulation/ant.hpp"
#include "pheromones.hpp"

LandTile::LandTile(const int x, const int y) noexcept : Tile(x, y) {}

void LandTile::interact(Ant &ant) noexcept
{
    if(ant.isTransportingFood())
    {
        addPheromones(PheromoneType::Food);
    }
    else
    {
        addPheromones(PheromoneType::Home);

        if(food > 0)
        {
            ant.pickFood();
            removeFood();
        }
    }
}

void LandTile::addFood(const unsigned int quantity) noexcept
{
    food += quantity;
}

void LandTile::removeFood(const unsigned quantity) noexcept
{
    food -= quantity;
}

void LandTile::addPheromones(const PheromoneType &type) noexcept
{
    if(type == PheromoneType::Home)
    {
        ++pheromones.home;
    }
    else if(type == PheromoneType::Food)
    {
        ++pheromones.food;
    }
}