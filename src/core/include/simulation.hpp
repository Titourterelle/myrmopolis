#pragma once

#include "observer.hpp"
#include "settings.hpp"

#include <memory>

namespace myrmo {

class Simulation {
    public:
        explicit Simulation(const SimulationSettings &settings);
        ~Simulation();

        void run() const;
        void addObserver(Observer &observer) const noexcept;

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
};

}