#include "board.hpp"
#include "anthill_tile.hpp"
#include "colony.hpp"
#include "snapshot.hpp"

#include <memory>
#include <ranges>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "simulation/map_generator.hpp"

namespace myrmo {
// Public

Board::Board(const BoardSettings& settings) :
    board_settings_(settings),
    map_(settings.column, settings.row)
{
    checkSettings();
    createTiles();
    initColonies();
}

void Board::step() const noexcept {
    for (const auto& colony : colonies_) {
        colony->step();
    }
}

snapshot::Snapshot Board::createSnapshot() const noexcept {
    snapshot::Snapshot snapshot;

    snapshot.width = map_.width;
    snapshot.height = map_.height;

    snapshot.number_of_colonies = colonies_.size();
    snapshot.number_of_ants = 0;
    for (const auto& colony : colonies_) {
        snapshot.number_of_ants += colony->getNumberOfAnts();
    }

    for (const auto& tile : map_.tiles) {
        snapshot.tiles.push_back(tile->takeTileSnapshot());
    }

    for (const auto& colony : colonies_) {
        snapshot::Colony snapshot_colony;
        snapshot_colony.name = colony->getName();
        
        for (const auto& ant : colony->getAnts()) {
            const auto [x, y] = ant->getPosition();
            const unsigned int id = ant->getId();

            snapshot_colony.ants.push_back(snapshot::Ant{.id = id, .x = x, .y = y});
        }

        for (const auto& anthill : colony->getAnthills()) {
            const auto [x, y] = anthill->getCoordinates();

            snapshot_colony.anthills_coords.emplace_back(x, y);
        }

        snapshot.colonies.push_back(snapshot_colony);
    }
    
    return snapshot;
    
}

std::vector<Tile*> Board::getAdjacentTiles(const Tile &tile) const noexcept {
    const auto [x, y] = tile.getCoordinates();
    std::vector<Tile*> adjacent_tiles;

    bool up {false};
    bool down {false};
    bool right {false};
    bool left {false};

    const auto at_coords = [this](const unsigned int i, const unsigned int j) {return i*map_.height + j;};

    if (x != 0) {
        left = true;
        adjacent_tiles.push_back(map_.tiles[at_coords(x - 1, y)].get());
    }
    if (x + 1 != map_.width) {
        right = true;
        adjacent_tiles.push_back(map_.tiles[at_coords(x + 1, y)].get());
    }
    if (y != 0) {
        down = true;
        adjacent_tiles.push_back(map_.tiles[at_coords(x, y - 1)].get());
    }
    if (y + 1 != map_.height) {
        up = true;
        adjacent_tiles.push_back(map_.tiles[at_coords(x, y + 1)].get());
    }

    if (y % 2 == 0) {
        if (up && left) {
            adjacent_tiles.push_back(map_.tiles[at_coords(x - 1, y + 1)].get());
        }
        if (down && left) {
            adjacent_tiles.push_back(map_.tiles[at_coords(x - 1, y - 1)].get());
        }
    }
    else {
        if (up && right) {
            adjacent_tiles.push_back(map_.tiles[at_coords(x + 1, y + 1)].get());
        }
        if (down && right) {
            adjacent_tiles.push_back(map_.tiles[at_coords(x + 1, y - 1)].get());
        }
    }
    return adjacent_tiles;
}

// Private

void Board::checkSettings() const {
    if (board_settings_.row == 0 || board_settings_.column == 0) {
        throw std::runtime_error("The dimensions are invalid");
    }

    std::unordered_set<std::string> colonies_names;
    for (const auto& [name, initial_number_of_ants] : board_settings_.colonies) {
        if (initial_number_of_ants == 0) {
            throw std::runtime_error("The initial number of ants is invalid");
        }
        if (!colonies_names.insert(name).second) {
            throw std::runtime_error("Two colonies cannot have the same name");
        }
    }
}

void Board::createTiles() noexcept {
    // TODO : make possible to set the seed
    const MapSettings map_settings{.seed = 0, .number_of_colonies = board_settings_.colonies.size()};
    MapGenerator map_gen{map_settings};

    const std::vector<AnthillTile*> anthills = map_gen.createMap(map_);

    for (auto [anthill, colony] : std::ranges::views::zip(anthills, board_settings_.colonies)) {
        starting_anthills_.insert({colony.name, anthill});
    }
}

void Board::initColonies() noexcept {
    for (const auto& [name, initial_number_of_ants] : board_settings_.colonies) {
        colonies_.push_back(
            std::make_unique<Colony>(
                name, *this,
                *starting_anthills_.at(name),
                initial_number_of_ants
                ));
    }
}
};