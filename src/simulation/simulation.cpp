#include "simulation.hpp"

#include <iostream>
#include <stdexcept>

Simulation::Simulation() noexcept
{
    std::cout << "Initialisation de la simulation" << std::endl;
}

bool Simulation::isOver() const noexcept
{
    return (currentRound >= maxRound);
}

void Simulation::nextRound()
{
    if(isOver())
    {
        throw std::runtime_error("The simulation is over, it can't simulate the next round");
    }

    ++currentRound;
}