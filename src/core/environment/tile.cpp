#include "tile.hpp"
#include "pheromones.hpp"
#include "snapshot.hpp"

using namespace myrmo;

// Public

Tile::Tile(const unsigned int x, const unsigned int y) noexcept : position_(Coordinates(x, y)) {}
Tile::Tile(const Coordinates coords) noexcept : position_(coords) {}

snapshot::Tile Tile::takeTileSnapshot() const noexcept {
    snapshot::Tile snapshot_tile;

    snapshot_tile.x = position_.x;
    snapshot_tile.y = position_.y;

    snapshot_tile.pheromones.insert({snapshot::PheromoneType::Home, pheromones_.home});
    snapshot_tile.pheromones.insert({snapshot::PheromoneType::Food, pheromones_.food});

    return snapshot_tile;
}

std::string Tile::getType() const noexcept {
    return "tile";
}

const Tile::Coordinates& Tile::getCoordinates() const noexcept {
    return position_;
}

const Pheromones& Tile::getPheromones() const noexcept {
    return pheromones_;
}

bool Tile::operator==(const Tile& other_tile) const noexcept {
    return (this->getCoordinates() == other_tile.getCoordinates());
}