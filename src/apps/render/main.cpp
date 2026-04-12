#include "simulation.hpp"
#include "config_manager.hpp"

int main() {
    myrmo::ConfigManager cm{"../../config.json"};
    myrmo::Simulation sim{cm.getSettings()};

    sim.run();

    return 0;
}