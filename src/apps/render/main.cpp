#include "simulation.hpp"
#include "render_config_manager.hpp"
#include "render_observer.hpp"

int main() {
    const RenderConfigManager cm{"../config.json"};
    const myrmo::Simulation sim{cm.getSimulationSettings()};

    RenderObserver observer{};

    sim.addObserver(observer);

    sim.run();

    observer.generateVideo(cm.getRenderSettings());

    return 0;
}