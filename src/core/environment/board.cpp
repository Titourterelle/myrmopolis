#include "board.hpp"
#include "anthill_tile.hpp"
#include "land_tile.hpp"

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <set>
#include <utility>
#include <vector>

using namespace myrmo;

Board::Board(const BoardSettings &settings) :
    dimensions(settings.column, settings.row),
    board_settings(settings)
{
    checkSettings();
    createTiles();
    initColonies();
}

const std::vector<Tile*> Board::getAdjacentTiles(const Tile &tile) const noexcept
{
    const Tile::Coordinates base_tile_coordinates = tile.getCoordinates();
    std::vector<Tile*> adjacent_tiles;

    bool up {false};
    bool down {false};
    bool right {false};
    bool left {false};

    if(base_tile_coordinates.x != 0)
    {
        left = true;
        adjacent_tiles.push_back(tiles[base_tile_coordinates.x - 1][base_tile_coordinates.y].get());
    }
    if(base_tile_coordinates.x + 1 != dimensions.first)
    {
        right = true;
        adjacent_tiles.push_back(tiles[base_tile_coordinates.x + 1][base_tile_coordinates.y].get());
    }
    if(base_tile_coordinates.y != 0)
    {
        down = true;
        adjacent_tiles.push_back(tiles[base_tile_coordinates.x][base_tile_coordinates.y - 1].get());
    }
    if(base_tile_coordinates.y + 1 != dimensions.second)
    {
        up = true;
        adjacent_tiles.push_back(tiles[base_tile_coordinates.x][base_tile_coordinates.y + 1].get());
    }

    if(base_tile_coordinates.y % 2 == 0)
    {
        if(up && left)
        {
            adjacent_tiles.push_back(tiles[base_tile_coordinates.x - 1][base_tile_coordinates.y + 1].get());
        }
        if(down && left)
        {
            adjacent_tiles.push_back(tiles[base_tile_coordinates.x - 1][base_tile_coordinates.y - 1].get());
        }
    }
    else
    {
        if(up && right)
        {
            adjacent_tiles.push_back(tiles[base_tile_coordinates.x + 1][base_tile_coordinates.y + 1].get());
        }
        if(down && right)
        {
            adjacent_tiles.push_back(tiles[base_tile_coordinates.x + 1][base_tile_coordinates.y - 1].get());
        }
    }
    return adjacent_tiles;
}

void Board::step() const noexcept
{
    for(const auto& colony : colonies)
    {
        colony->step();
    }
}

void Board::checkSettings() const
{
    if(board_settings.row <= 0 || board_settings.column <= 0)
    {
        throw std::runtime_error("The dimensions are invalid");
    }

    std::unordered_set<std::string> colonies_names;
    std::set<std::pair<int, int>> anthills_coordinates;
    for(const auto& colony : board_settings.colonies)
    {
        if(colony.x_anthill < 0 || colony.x_anthill >= dimensions.second || colony.y_anthill < 0 || colony.y_anthill >= dimensions.first)
        {
            throw std::runtime_error("An anthill cannot be set in the board");
        }
        if(colony.initial_number_of_ants <= 0)
        {
            throw std::runtime_error("The initial number of ants is invalid");
        }
        if(!colonies_names.insert(colony.name).second)
        {
            throw std::runtime_error("Two colonies cannot have the same name");
        }
        if(!anthills_coordinates.insert(std::make_pair(colony.x_anthill, colony.y_anthill)).second)
        {
            throw std::runtime_error("Two anthills cannot be on the same tile");
        }
    }
}

void Board::createTiles() noexcept
{
    std::map<Tile::Coordinates, std::string> anthill_owner;
    for(const auto& colony : board_settings.colonies)
    {
        anthill_owner.insert(std::make_pair(Tile::Coordinates(colony.x_anthill, colony.y_anthill), colony.name));
    }

    for(auto c = 0; c < dimensions.first; ++c)
    {
        tiles.push_back({});
        for(auto r = 0; r < dimensions.second; ++r)
        {
            const Tile::Coordinates targetCoord{c, r};
            
            if(anthill_owner.contains(targetCoord))
            {
                auto anthill = std::make_unique<AnthillTile>(c, r);
                starting_anthills.insert({anthill_owner.at(targetCoord), anthill.get()});
                tiles.at(c).push_back(std::move(anthill));
            }
            else
            {
                tiles.at(c).push_back(std::make_unique<LandTile>(c, r));
            }
        }
    }
}

void Board::initColonies() noexcept
{
    for(const auto& colony : board_settings.colonies)
    {
        colonies.push_back(std::make_unique<Colony>(colony.name, *this, *starting_anthills.at(colony.name), colony.initial_number_of_ants));
    }
}