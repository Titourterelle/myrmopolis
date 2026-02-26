#include "ant.hpp"
#include "colony.hpp"

#include <iostream>
#include <stdexcept>

Ant::Ant(Colony& colony, Tile &spawnTile) noexcept : colony(&colony), actualTile(&spawnTile)
{
    std::cout << "Création d'une fourmi" << std::endl;
}

bool Ant::isTransportingFood() const noexcept
{
    return transportFood;
}

void Ant::act() noexcept
{
    //TODO : The action of the ant for 1 turn
}

void Ant::move(Tile& nextTile) noexcept
{
    actualTile = &nextTile;
}

void Ant::pickFood()
{
    if(transportFood)
    {
        throw std::runtime_error("The ant is already transporting food");
    }
    if(!(actualTile->getFoodQuantity() > 0))
    {
        throw std::runtime_error("There is no food the ant can pick on this tile");
    }
    actualTile->removeFood();
    transportFood = true;
}

void Ant::dropFood() noexcept
{
    actualTile->addFood();
    transportFood = false;
}

void Ant::depositPheromones(const PheromoneType type) const noexcept
{
    actualTile->addPheromones(type);
}