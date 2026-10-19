#include "config_manager.hpp"
#include "simulation.hpp"

#include <filesystem>
#include <print>

int main(int argc, char* argv[]) {

    std::filesystem::path config_path = "../../config.json";

    if (argc > 2) {
        std::printf("Too many arguments\n");
        return 1;
    }
    if (argc == 2) {
        config_path = argv[1];
    }

    const myrmo::ConfigManager cm{config_path};
    const myrmo::Simulation sim{cm.getSimulationSettings()};

    sim.run();

    return 0;
}