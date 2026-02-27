#pragma once

#include "environment/board.hpp"
#include "manager/settings.hpp"

#include <memory>
#include <vector>

class Simulation
{
    public:
        explicit Simulation(const SimulationSettings& settings);
        void run() noexcept;
        bool isOver() const noexcept;

    private:
        void step() noexcept;
        void initBoards();

        const SimulationSettings simulationSettings;
        std::vector<std::unique_ptr<Board>> boards;
        const int maxRound = 50;
        int currentRound = 0;
};