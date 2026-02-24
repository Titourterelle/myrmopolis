#include "tile.hpp"
#include "environment/pheromones.hpp"

#include <iostream>
#include <stdexcept>

Tile::Tile(const int x, const int y) noexcept : position(Coordinates(x, y))
{
    std::cout << "Création d'une tuile de coordonnées : " << position.x << ", " << position.y << std::endl;
}

const Tile::Coordinates& Tile::getCoordinates() const noexcept
{
    return position;
}

int Tile::getFoodQuantity() const noexcept
{
    return food;
}

void Tile::addFood(const int quantity)
{
    if(quantity <= 0)
    {
        throw std::invalid_argument("The quantity to add must be strictly positive");
    }

    food += quantity;
}

void Tile::removeFood(const int quantity)
{
    if(quantity <= 0)
    {
        throw std::invalid_argument("The quantity to remove must be strictly positive");
    }

    food -= quantity;
}

const Pheromones& Tile::getPheromones() const noexcept
{
    return pheromones;
}

void Tile::addPheromones(const PheromoneType type) noexcept
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

bool Tile::operator==(const Tile& otherTile) const noexcept
{
    return (this->getCoordinates() == otherTile.getCoordinates());
}