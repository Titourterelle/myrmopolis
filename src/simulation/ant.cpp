#include "ant.hpp"
#include "colony.hpp"
#include "environment/tile.hpp"

#include <iostream>
#include <stdexcept>

Ant::Ant(Colony &colony, Tile &spawn_tile) noexcept :
    colony(&colony),
    board(&colony.getBoard()),
    actual_tile(&spawn_tile)
{
    std::cout << "Création d'une fourmi" << std::endl;
}

bool Ant::isTransportingFood() const noexcept
{
    return is_transporting_food;
}

void Ant::act() noexcept
{
    //TODO : Move the ant depending on the adjacent tiles
    actual_tile->interact(*this);
}

void Ant::pickFood()
{
    if(isTransportingFood())
    {
        throw std::runtime_error("The ant is already transporting food");
    }

    is_transporting_food = true;
}

void Ant::dropFood() noexcept
{
    is_transporting_food = false;
}


void Ant::move(Tile &next_tile) noexcept
{
    actual_tile = &next_tile;
}