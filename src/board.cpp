#include "../include/board.hpp"

#include <iostream>

Board::Board(const int row, const int column) noexcept : row(row), column(column)
{
    std::cout << "Création d'un board, this -> " << this << std::endl;
}