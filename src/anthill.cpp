#include "../include/anthill.hpp"

#include <iostream>

Anthill::Anthill(const int row, const int column) noexcept : Tile(row, column)
{
    std::cout << "Cette tuile est une fourmilière" << std::endl;
}