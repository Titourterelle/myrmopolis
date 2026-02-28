#include "ant.hpp"
#include "colony.hpp"
#include "environment/tile.hpp"

#include <iostream>
#include <stdexcept>

Ant::Ant(Colony &colony, Tile &spawnTile) noexcept :
    colony(&colony),
    board(&colony.getBoard()),
    actualTile(&spawnTile)
{
    std::cout << "Création d'une fourmi" << std::endl;
}

bool Ant::isTransportingFood() const noexcept
{
    return transportFood;
}

void Ant::act() noexcept
{
    //TODO : Move the ant depending on the adjacent tiles
    actualTile->interact(*this);
}

void Ant::pickFood()
{
    if(isTransportingFood())
    {
        throw std::runtime_error("The ant is already transporting food");
    }

    transportFood = true;
}

void Ant::dropFood() noexcept
{
    transportFood = false;
}


void Ant::move(Tile &nextTile) noexcept
{
    actualTile = &nextTile;
}