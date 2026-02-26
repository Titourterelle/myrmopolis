#include "simulation.hpp"
#include "environment/board.hpp"
#include "manager/settings.hpp"
#include "simulation/colony.hpp"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

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

void Simulation::run() noexcept
{
    while (!isOver())
    {
        step();
    }
}

void Simulation::step() noexcept
{
    for(const auto& boardColonies : colonies)
    {
        for(const auto& colony : boardColonies)
        {
            colony->step();
        }
    }
    ++currentRound;
}

void Simulation::initBoards()
{
    for(auto i = 0; i < simulationSettings.numberOfBoards; ++i)
    {
        boards.push_back(std::make_unique<Board>(simulationSettings.board));
    }
    for(const auto& board : boards)
    {
        colonies.push_back(board->getColonies());
    }
}