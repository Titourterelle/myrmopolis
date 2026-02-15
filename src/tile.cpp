#include "../include/tile.hpp"

#include <iostream>

Tile::Tile(const int x, const int y) noexcept : position(Coordinates(x, y))
{
    std::cout << "Création d'une tuile de coordonnées : " << position.x << ", " << position.y << std::endl;
}

const Tile::Coordinates& Tile::getCoordinates() const noexcept
{
    return position;
}

bool Tile::operator==(const Tile& otherTile) const noexcept
{
    return (this->getCoordinates() == otherTile.getCoordinates());
}