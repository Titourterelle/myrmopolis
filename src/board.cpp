#include "../include/board.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

Board::Board(const std::unordered_map<Settings, int>& settings)
{
    try
    {
        row = settings.at(Settings::Row);
        column = settings.at(Settings::Column);
        const int ant = settings.at(Settings::nbAnts);

        setDimensions(row, column);
        createTiles();
        addAnts(ant);
        std::cout << "Création d'un board" << std::endl;
    }
    catch(const std::out_of_range &err)
    {
        std::cerr << "Erreur : Un paramètre est manquant dans le fichier de configuration" << std::endl;
    }
}

const std::vector<Tile> Board::getAdjacentTiles(const Tile& actualTile) const
{
    const Tile::Coordinates actualTileCoordinates = actualTile.getCoordinates();
    std::vector<Tile> adjacentTiles;

    bool up {false};
    bool down {false};
    bool right {false};
    bool left {false};

    if(actualTileCoordinates.rowNumber != 0)
    {
        down = true;
        adjacentTiles.push_back(tiles[actualTileCoordinates.rowNumber - 1][actualTileCoordinates.columnNumber]);
    }
    if(actualTileCoordinates.rowNumber != row)
    {
        up = true;
        adjacentTiles.push_back(tiles[actualTileCoordinates.rowNumber + 1][actualTileCoordinates.columnNumber]);
    }
    if(actualTileCoordinates.columnNumber != 0)
    {
        left = true;
        adjacentTiles.push_back(tiles[actualTileCoordinates.rowNumber][actualTileCoordinates.columnNumber - 1]);
    }
    if(actualTileCoordinates.columnNumber != column)
    {
        right = true;
        adjacentTiles.push_back(tiles[actualTileCoordinates.rowNumber][actualTileCoordinates.columnNumber + 1]);
    }

    if(up && right)
    {
        adjacentTiles.push_back(tiles[actualTileCoordinates.rowNumber + 1][actualTileCoordinates.columnNumber + 1]);
    }
    if(up && left)
    {
        adjacentTiles.push_back(tiles[actualTileCoordinates.rowNumber + 1][actualTileCoordinates.columnNumber - 1]);
    }
    if(down && left)
    {
        adjacentTiles.push_back(tiles[actualTileCoordinates.rowNumber - 1][actualTileCoordinates.columnNumber - 1]);
    }
    if(down && right)
    {
        adjacentTiles.push_back(tiles[actualTileCoordinates.rowNumber - 1][actualTileCoordinates.columnNumber + 1]);
    }

    return adjacentTiles;
}

void Board::setDimensions(const int row, const int column)
{
    if(row > 0)
    {
        this->row = row;
    }
    else
    {
        throw std::invalid_argument("The number of row can't be less than 1");
    }

    if(column > 0)
    {
        this->column = column;
    }
    else
    {
        throw std::invalid_argument("The number of column can't be less than 1");
    }
}

void Board::createTiles() noexcept
{
    for(auto r = 0; r < row; ++r)
    {
        tiles.push_back({});
        for(auto c = 0; c < column; ++c)
        {
            tiles.at(r).push_back(Tile(r, c));
        }
    }
}

void Board::addAnts(const int numberOfAnts) noexcept
{
    for(auto i = 0; i < numberOfAnts; ++i)
    {
        ants.push_back(Ant());
    }
}