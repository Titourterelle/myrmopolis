#include "../include/tile.hpp"

#include <iostream>

Tile::Tile(const int row, const int column) noexcept : position(Coordinates(row, column))
{
    std::cout << "Création d'une tuile de coordonnées : " << position.columnNumber << ", " << position.rowNumber << std::endl;
}

const Tile::Coordinates& Tile::getCoordinates() const noexcept
{
    return position;
}

bool Tile::operator==(const Tile& otherTile) const noexcept
{
    if(this->getCoordinates() == otherTile.getCoordinates())
    {
        return true;
    }
    else
    {
        return false;
    }
}