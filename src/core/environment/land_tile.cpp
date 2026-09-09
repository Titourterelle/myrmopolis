#include "land_tile.hpp"
#include "snapshot.hpp"
#include "tile.hpp"
#include "ant.hpp"
#include "pheromones.hpp"

using namespace myrmo;

// Public

LandTile::LandTile(const unsigned int x, const unsigned int y) noexcept : Tile(x, y) {}

void LandTile::interact(Ant &ant) noexcept {
    if (ant.isTransportingFood()) {
        addPheromones(PheromoneType::Food);
    }
    else {
        addPheromones(PheromoneType::Home);

        if (food > 0) {
            ant.pickFood();
            removeFood();
        }
    }
}

snapshot::Tile LandTile::takeTileSnapshot() const noexcept {
    snapshot::Tile snapshot_tile = Tile::takeTileSnapshot();

    snapshot_tile.type = snapshot::TileType::Land;
    snapshot_tile.food = food;

    return snapshot_tile;
}

void LandTile::addPheromones(const PheromoneType &type) noexcept {
    if (type == PheromoneType::Home) {
        ++pheromones.home;
    }
    else if (type == PheromoneType::Food) {
        ++pheromones.food;
    }
}

// Private

void LandTile::addFood(const unsigned int quantity = 1) noexcept {
    food += quantity;
}

void LandTile::removeFood(const unsigned quantity = 1) noexcept {
    food -= quantity;
}