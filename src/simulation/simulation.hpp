#pragma once

#include "environment/board.hpp"
#include "manager/settings.hpp"

#include <memory>
#include <vector>

class Simulation
{
    public:
        explicit Simulation(const SimulationSettings& settings);
        bool isOver() const noexcept;

    private:
        void nextRound();
        void initBoards();

        const SimulationSettings simulationSettings;
        std::vector<std::unique_ptr<Board>> boards;
        const int maxRound = 50;
        int currentRound = 0;
};