#include "../include/ant.hpp"

#include <iostream>

Ant::Ant() noexcept
{
    std::cout << "Création d'une fourmi" << std::endl;
}

void Ant::move(Tile &nextTile) noexcept
{
    actualTile = &nextTile;
}