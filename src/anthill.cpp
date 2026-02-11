#include "../include/anthill.hpp"

#include <iostream>

Anthill::Anthill(const int row, const int column) noexcept : Tile(row, column)
{
    std::cout << "Une fourmilière est créée" << std::endl;
}