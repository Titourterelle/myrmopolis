#include "simulation.hpp"
#include "config_manager.hpp"
#include "render_observer.hpp"

int main() {
    myrmo::ConfigManager cm{"../../config.json"};
    myrmo::Simulation sim{cm.getSettings()};

    RenderObserver observer{};

    sim.addObserver(observer);

    sim.run();

    observer.generateVideo();

    return 0;
}