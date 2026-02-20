#include "../include/ant.hpp"
#include "../include/colony.hpp"

#include <iostream>
#include <stdexcept>

Ant::Ant(Colony& colony) noexcept : colony(&colony)
{
    std::cout << "Création d'une fourmi" << std::endl;
}

bool Ant::isTransportingFood() const noexcept
{
    return transportFood;
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