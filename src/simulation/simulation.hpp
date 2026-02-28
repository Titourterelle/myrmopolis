#pragma once

#include "environment/board.hpp"
#include "manager/settings.hpp"

#include <memory>
#include <vector>

class Simulation
{
    public:
        explicit Simulation(const SimulationSettings &settings);
        void run() noexcept;
        bool isOver() const noexcept;

    private:
        void step() noexcept;
        void initBoards();

        const SimulationSettings simulation_settings;
        std::vector<std::unique_ptr<Board>> boards;
        const int max_round = 50;
        int current_round = 0;
};