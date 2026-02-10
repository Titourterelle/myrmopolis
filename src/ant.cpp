#include "../include/ant.hpp"

#include <iostream>

Ant::Ant() noexcept
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

void Ant::pickFood() noexcept
{

}

void Ant::dropFood() noexcept
{
    transportFood = false;
}