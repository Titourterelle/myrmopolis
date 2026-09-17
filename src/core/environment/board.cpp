#include "board.hpp"
#include "anthill_tile.hpp"
#include "colony.hpp"
#include "land_tile.hpp"
#include "snapshot.hpp"

#include <map>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace myrmo;

// Public

Board::Board(const BoardSettings &settings) :
    dimensions(settings.column, settings.row),
    board_settings(settings)
{
    checkSettings();
    createTiles();
    initColonies();
}

void Board::step() const noexcept {
    for (const auto& colony : colonies) {
        colony->step();
    }
}

snapshot::Snapshot Board::createSnapshot() const noexcept {
    snapshot::Snapshot snapshot;

    snapshot.width = dimensions.first;
    snapshot.height = dimensions.second;

    snapshot.number_of_colonies = colonies.size();
    snapshot.number_of_ants = 0;
    for (const auto& colony : colonies) {
        snapshot.number_of_ants += colony->getNumberOfAnts();
    }

    for (const auto& column : tiles) {
        for (const auto& tile : column) {
            snapshot.tiles.push_back(tile->takeTileSnapshot());
        }
    }

    for (const auto& colony : colonies) {
        snapshot::Colony snapshot_colony;
        snapshot_colony.name = colony->getName();
        
        for (const auto& ant : colony->getAnts()) {
            const auto [x, y] = ant->getPosition();
            const unsigned int id = ant->getId();

            snapshot_colony.ants.push_back(snapshot::Ant{id, x, y});
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

    if (x != 0) {
        left = true;
        adjacent_tiles.push_back(tiles[x - 1][y].get());
    }
    if (x + 1 != dimensions.first) {
        right = true;
        adjacent_tiles.push_back(tiles[x + 1][y].get());
    }
    if (y != 0) {
        down = true;
        adjacent_tiles.push_back(tiles[x][y - 1].get());
    }
    if (y + 1 != dimensions.second) {
        up = true;
        adjacent_tiles.push_back(tiles[x][y + 1].get());
    }

    if (y % 2 == 0) {
        if (up && left) {
            adjacent_tiles.push_back(tiles[x - 1][y + 1].get());
        }
        if (down && left) {
            adjacent_tiles.push_back(tiles[x - 1][y - 1].get());
        }
    }
    else {
        if (up && right) {
            adjacent_tiles.push_back(tiles[x + 1][y + 1].get());
        }
        if (down && right) {
            adjacent_tiles.push_back(tiles[x + 1][y - 1].get());
        }
    }
    return adjacent_tiles;
}

// Private

void Board::checkSettings() const {
    if (board_settings.row == 0 || board_settings.column == 0) {
        throw std::runtime_error("The dimensions are invalid");
    }

    std::unordered_set<std::string> colonies_names;
    std::set<std::pair<unsigned int, unsigned int>> anthills_coordinates;
    for (const auto& colony : board_settings.colonies) {
        if (colony.x_anthill < 0 || colony.x_anthill >= dimensions.second || colony.y_anthill < 0 || colony.y_anthill >= dimensions.first) {
            throw std::runtime_error("An anthill cannot be set in the board");
        }
        if (colony.initial_number_of_ants == 0) {
            throw std::runtime_error("The initial number of ants is invalid");
        }
        if (!colonies_names.insert(colony.name).second) {
            throw std::runtime_error("Two colonies cannot have the same name");
        }
        if (!anthills_coordinates.insert(std::make_pair(colony.x_anthill, colony.y_anthill)).second) {
            throw std::runtime_error("Two anthills cannot be on the same tile");
        }
    }
}

void Board::createTiles() noexcept {
    std::map<Tile::Coordinates, std::string> anthill_owner;
    for (const auto& colony : board_settings.colonies) {
        anthill_owner.insert(std::make_pair(Tile::Coordinates(colony.x_anthill, colony.y_anthill), colony.name));
    }

    for (unsigned int c = 0; c < dimensions.first; ++c) {
        tiles.emplace_back();
        for (unsigned int r = 0; r < dimensions.second; ++r) {
            const Tile::Coordinates targetCoord{c, r};
            
            if (anthill_owner.contains(targetCoord)) {
                auto anthill = std::make_unique<AnthillTile>(c, r);
                starting_anthills.insert({anthill_owner.at(targetCoord), anthill.get()});
                tiles.at(c).push_back(std::move(anthill));
            }
            else {
                tiles.at(c).push_back(std::make_unique<LandTile>(c, r));
            }
        }
    }
}

void Board::initColonies() noexcept {
    for (const auto& colony : board_settings.colonies) {
        colonies.push_back(std::make_unique<Colony>(colony.name, *this, *starting_anthills.at(colony.name), colony.initial_number_of_ants));
    }
}