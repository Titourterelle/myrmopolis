#include "../include/anthill.hpp"

#include <iostream>

Anthill::Anthill(const int row, const int column, const int initialNumberOfAnts) noexcept : Tile(row, column)
{
    addAnts(initialNumberOfAnts);
    std::cout << "Cette tuile est une fourmilière" << std::endl;
}

void Anthill::addAnts(const int numberOfAnts) noexcept
{
    for(auto i = 0; i < numberOfAnts; ++i)
    {
        ants.push_back(std::make_unique<Ant>());
    }
}