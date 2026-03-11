#include "tile.hpp"
#include "environment/pheromones.hpp"

using namespace myrmo;

Tile::Tile(const int x, const int y) noexcept : position(Coordinates(x, y)) {}

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