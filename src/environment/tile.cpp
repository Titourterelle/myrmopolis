#include "tile.hpp"
#include "environment/pheromones.hpp"

#include <iostream>

Tile::Tile(const int x, const int y) noexcept : position(Coordinates(x, y))
{
    std::cout << "Création d'une tuile de coordonnées : " << position.x << ", " << position.y << std::endl;
}

const Tile::Coordinates& Tile::getCoordinates() const noexcept
{
    return position;
}

const Pheromones& Tile::getPheromones() const noexcept
{
    return pheromones;
}

bool Tile::operator==(const Tile &other_tile) const noexcept
{
    return (this->getCoordinates() == other_tile.getCoordinates());
}