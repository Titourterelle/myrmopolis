#include "board.hpp"
#include "anthill.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <set>
#include <utility>
#include <vector>

Board::Board(const SimulationSettings& settings) :
    dimensions(settings.board.column, settings.board.row),
    simulationSettings(settings)
{
    checkSettings();
    createTiles();
    initColonies();
    std::cout << "Création d'un board" << std::endl;
}

const std::vector<Tile*> Board::getAdjacentTiles(const Tile& actualTile) const
{
    const Tile::Coordinates actualTileCoordinates = actualTile.getCoordinates();
    std::vector<Tile*> adjacentTiles;

    bool up {false};
    bool down {false};
    bool right {false};
    bool left {false};

    if(actualTileCoordinates.y != 0)
    {
        down = true;
        adjacentTiles.push_back(tiles[actualTileCoordinates.y - 1][actualTileCoordinates.x].get());
    }
    if(actualTileCoordinates.y + 1 != dimensions.second)
    {
        up = true;
        adjacentTiles.push_back(tiles[actualTileCoordinates.y + 1][actualTileCoordinates.x].get());
    }
    if(actualTileCoordinates.x != 0)
    {
        left = true;
        adjacentTiles.push_back(tiles[actualTileCoordinates.y][actualTileCoordinates.x - 1].get());
    }
    if(actualTileCoordinates.x + 1 != dimensions.first)
    {
        right = true;
        adjacentTiles.push_back(tiles[actualTileCoordinates.y][actualTileCoordinates.x + 1].get());
    }

    if(up && right)
    {
        adjacentTiles.push_back(tiles[actualTileCoordinates.y + 1][actualTileCoordinates.x + 1].get());
    }
    if(up && left)
    {
        adjacentTiles.push_back(tiles[actualTileCoordinates.y + 1][actualTileCoordinates.x - 1].get());
    }
    if(down && left)
    {
        adjacentTiles.push_back(tiles[actualTileCoordinates.y - 1][actualTileCoordinates.x - 1].get());
    }
    if(down && right)
    {
        adjacentTiles.push_back(tiles[actualTileCoordinates.y - 1][actualTileCoordinates.x + 1].get());
    }

    return adjacentTiles;
}

void Board::checkSettings() const
{
    if(simulationSettings.board.row <= 0 || simulationSettings.board.column <= 0)
    {
        throw std::runtime_error("The dimensions are invalid");
    }

    std::unordered_set<std::string> coloniesNames;
    std::set<std::pair<int, int>> anthillsCoordinates;
    for(const auto& colony : simulationSettings.colonies)
    {
        if(colony.xAnthill < 0 || colony.xAnthill >= dimensions.second || colony.yAnthill < 0 || colony.yAnthill >= dimensions.first)
        {
            throw std::runtime_error("An anthill cannot be set in the board");
        }
        if(colony.initialNumberOfAnts <= 0)
        {
            throw std::runtime_error("The initial number of ants is invalid");
        }
        if(!coloniesNames.insert(colony.name).second)
        {
            throw std::runtime_error("Two colonies cannot have the same name");
        }
        if(!anthillsCoordinates.insert(std::make_pair(colony.xAnthill, colony.yAnthill)).second)
        {
            throw std::runtime_error("Two anthills cannot be on the same tile");
        }
    }
}

void Board::createTiles() noexcept
{
    std::map<Tile::Coordinates, std::string> anthillOwner;
    for(const auto& colony : simulationSettings.colonies)
    {
        anthillOwner.insert(std::make_pair(Tile::Coordinates(colony.xAnthill, colony.yAnthill), colony.name));
    }

    for(auto c = 0; c < dimensions.first; ++c)
    {
        tiles.push_back({});
        for(auto r = 0; r < dimensions.second; ++r)
        {
            const Tile::Coordinates targetCoord{c, r};
            
            if(anthillOwner.contains(targetCoord))
            {
                auto anthill = std::make_unique<Anthill>(c, r);
                startingAnthills.insert({anthillOwner.at(targetCoord), anthill.get()});
                tiles.at(c).push_back(std::move(anthill));
            }
            else
            {
                tiles.at(c).push_back(std::make_unique<Tile>(c, r));
            }
        }
    }
}

void Board::initColonies() noexcept
{
    for(const auto& colony : simulationSettings.colonies)
    {
        colonies.push_back(std::make_unique<Colony>(colony.name, *startingAnthills.at(colony.name), colony.initialNumberOfAnts));
    }
}