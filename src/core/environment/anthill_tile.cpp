#include "anthill_tile.hpp"
#include "ant.hpp"
#include "snapshot.hpp"

using namespace myrmo;

// Public

AnthillTile::AnthillTile(const unsigned int x, const unsigned int y) noexcept : Tile(x, y) {}

void AnthillTile::interact(Ant& ant) noexcept {
    if (ant.isTransportingFood()) {
        ant.dropFood();
        ++food_reserve_;
    }
}

snapshot::Tile AnthillTile::takeTileSnapshot() const noexcept {
    snapshot::Tile snapshot_tile = Tile::takeTileSnapshot();

    snapshot_tile.type = snapshot::TileType::Anthill;
    snapshot_tile.food = std::nullopt;

    return snapshot_tile;
}