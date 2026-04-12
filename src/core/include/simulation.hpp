#pragma once

#include "settings.hpp"
#include "observer.hpp"

#include <memory>

namespace myrmo {

class Simulation {
    public:
        explicit Simulation(const SimulationSettings &settings);
        ~Simulation();

        void run();
        void addObserver(Observer &observer) noexcept;

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
};

}