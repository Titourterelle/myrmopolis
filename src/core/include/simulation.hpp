#pragma once

#include "settings.hpp"

#include <memory>

namespace myrmo {

class Simulation
{
    public:
        explicit Simulation(const SimulationSettings &settings);
        ~Simulation();

        void nextStep();
        bool isOver() const noexcept;

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
};

}