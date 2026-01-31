#include "../include/board.hpp"

#include <iostream>

Board::Board(const int row, const int column)
{
    setDimensions(row, column);
    createTiles();
    std::cout << "Création d'un board, this -> " << this << std::endl;
    
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
            tiles.at(r).push_back(Tile());
        }
    }
}