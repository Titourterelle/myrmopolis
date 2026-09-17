#pragma once

#include "anthill_tile.hpp"
#include "colony.hpp"
#include "settings.hpp"
#include "snapshot.hpp"
#include "tile.hpp"

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace myrmo {

class Board {
    public:
        explicit Board(const BoardSettings &settings);

        void step() const noexcept;
        snapshot::Snapshot createSnapshot() const noexcept;

        std::vector<Tile*> getAdjacentTiles(const Tile &tile) const noexcept;

    private:
        void checkSettings() const;
        void createTiles() noexcept;
        void initColonies() noexcept;

        const std::pair<unsigned int, unsigned int> dimensions;
        const BoardSettings board_settings;

        std::unordered_map<std::string, AnthillTile*> starting_anthills;
        
        std::vector<std::unique_ptr<Colony>> colonies;
        std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
};

}