#include "simulation.hpp"
#include "render_config_manager.hpp"
#include "render_observer.hpp"

int main() {
    RenderConfigManager cm{"../../config.json"};
    myrmo::Simulation sim{cm.getSimulationSettings()};

    RenderObserver observer{};

    sim.addObserver(observer);

    sim.run();

    observer.generateVideo(cm.getRenderSettings());

    return 0;
}