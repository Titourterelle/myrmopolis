#pragma once

#include "anthill_tile.hpp"
#include "colony.hpp"
#include "settings.hpp"
#include "snapshot.hpp"
#include "tile.hpp"
#include "simulation/map_utils.hpp"

#include <memory>
#include <unordered_map>
#include <vector>

namespace myrmo {

class Board {
    public:
        explicit Board(const BoardSettings &settings);

        void step() const noexcept;
        snapshot::Snapshot createSnapshot() const noexcept;

        [[nodiscard]] std::vector<Tile*> getAdjacentTiles(const Tile& tile) const noexcept;

    private:
        void checkSettings() const;
        void createTiles() noexcept;
        void initColonies() noexcept;

        const BoardSettings board_settings_;

        std::unordered_map<std::string, AnthillTile*> starting_anthills_;

        std::vector<std::unique_ptr<Colony>> colonies_;
        TileMap map_;
};

}