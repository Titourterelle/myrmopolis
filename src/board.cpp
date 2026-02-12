#include "../include/board.hpp"
#include "../include/anthill.hpp"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

Board::Board(const std::unordered_map<Settings, int>& settings) :
    row(settings.at(Settings::Row)),
    column(settings.at(Settings::Column)),
    anthillCoordinates(Tile::Coordinates(settings.at(Settings::anthillRow), settings.at(Settings::anthillColumn))),
    initialNumberOfAnts(settings.at(Settings::nbAnts))
{
    checkSettings();
    createTiles();
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

    if(actualTileCoordinates.rowNumber != 0)
    {
        down = true;
        adjacentTiles.push_back(tiles[actualTileCoordinates.rowNumber - 1][actualTileCoordinates.columnNumber].get());
    }
    if(actualTileCoordinates.rowNumber != row)
    {
        up = true;
        adjacentTiles.push_back(tiles[actualTileCoordinates.rowNumber + 1][actualTileCoordinates.columnNumber].get());
    }
    if(actualTileCoordinates.columnNumber != 0)
    {
        left = true;
        adjacentTiles.push_back(tiles[actualTileCoordinates.rowNumber][actualTileCoordinates.columnNumber - 1].get());
    }
    if(actualTileCoordinates.columnNumber != column)
    {
        right = true;
        adjacentTiles.push_back(tiles[actualTileCoordinates.rowNumber][actualTileCoordinates.columnNumber + 1].get());
    }

    if(up && right)
    {
        adjacentTiles.push_back(tiles[actualTileCoordinates.rowNumber + 1][actualTileCoordinates.columnNumber + 1].get());
    }
    if(up && left)
    {
        adjacentTiles.push_back(tiles[actualTileCoordinates.rowNumber + 1][actualTileCoordinates.columnNumber - 1].get());
    }
    if(down && left)
    {
        adjacentTiles.push_back(tiles[actualTileCoordinates.rowNumber - 1][actualTileCoordinates.columnNumber - 1].get());
    }
    if(down && right)
    {
        adjacentTiles.push_back(tiles[actualTileCoordinates.rowNumber - 1][actualTileCoordinates.columnNumber + 1].get());
    }

    return adjacentTiles;
}

void Board::checkSettings() const
{
    if(row <= 0 || column <= 0)
    {
        throw std::runtime_error("The dimensions are invalid");
    }
    if(anthillCoordinates.rowNumber < 0 || anthillCoordinates.rowNumber >= row || anthillCoordinates.columnNumber < 0 || anthillCoordinates.columnNumber >= column)
    {
        throw std::runtime_error("The anthill cannot be set in the board");
    }
    if(initialNumberOfAnts <= 0)
    {
        throw std::runtime_error("The initial number of ants is invalid");
    }
}

void Board::createTiles() noexcept
{
    for(auto r = 0; r < row; ++r)
    {
        tiles.push_back({});
        for(auto c = 0; c < column; ++c)
        {
            if(anthillCoordinates.rowNumber == r && anthillCoordinates.columnNumber == c)
            {
                tiles.at(r).push_back(std::make_unique<Anthill>(r, c, initialNumberOfAnts));
            }
            else
            {
                tiles.at(r).push_back(std::make_unique<Tile>(r, c));
            }
        }
    }
}