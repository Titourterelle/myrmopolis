#include "simulation.hpp"
#include "environment/board.hpp"
#include "manager/settings.hpp"

#include <iostream>
#include <memory>
#include <stdexcept>

Simulation::Simulation(const SimulationSettings& settings) : simulationSettings(settings)
{
    if(simulationSettings.numberOfBoards <= 0)
    {
        throw std::runtime_error("The number of boards can't be null or negative");
    }

    std::cout << "Initialisation de la simulation" << std::endl;
    initBoards();
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

void Simulation::initBoards()
{
    for(auto i = 0; i < simulationSettings.numberOfBoards; ++i)
    {
        boards.push_back(std::make_unique<Board>(simulationSettings.board));
    }
}