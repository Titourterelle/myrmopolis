#include "config_manager.hpp"
#include "simulation.hpp"

int main() {
    const myrmo::ConfigManager cm{"../config.json"};
    const myrmo::Simulation sim{cm.getSimulationSettings()};

    sim.run();

    return 0;
}