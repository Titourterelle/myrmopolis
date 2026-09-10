#include "tile.hpp"
#include "pheromones.hpp"
#include "snapshot.hpp"

using namespace myrmo;

// Public

Tile::Tile(const unsigned int x, const unsigned int y) noexcept : position(Coordinates(x, y)) {}

snapshot::Tile Tile::takeTileSnapshot() const noexcept {
    snapshot::Tile snapshot_tile;

    snapshot_tile.x = position.x;
    snapshot_tile.y = position.y;

    snapshot_tile.pheromones.insert({snapshot::PheromoneType::Home, pheromones.home});
    snapshot_tile.pheromones.insert({snapshot::PheromoneType::Food, pheromones.food});

    return snapshot_tile;
}

std::string Tile::getType() const noexcept {
    return "tile";
}

const Tile::Coordinates& Tile::getCoordinates() const noexcept {
    return position;
}

const Pheromones& Tile::getPheromones() const noexcept {
    return pheromones;
}

bool Tile::operator==(const Tile &other_tile) const noexcept {
    return (this->getCoordinates() == other_tile.getCoordinates());
}