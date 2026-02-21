#include "anthill.hpp"

#include <iostream>

Anthill::Anthill(const int x, const int y) noexcept : Tile(x, y)
{
    std::cout << "Cette tuile est une fourmilière" << std::endl;
}