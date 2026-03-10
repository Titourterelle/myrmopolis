#pragma once

#include "settings.hpp"

#include <memory>

class Simulation
{
    public:
        explicit Simulation(const SimulationSettings &settings);
        ~Simulation();

        void nextStep();
        bool isOver() const noexcept;
        void getCurrentBoardState() const noexcept;

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
};