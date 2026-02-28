#include "simulation/simulation.hpp"
#include "manager/config_manager.hpp"

#include <string>

int main()
{
    std::string filename{"../../config.json"};
    ConfigManager config_manager{filename};

    Simulation simulation{config_manager.getSettings()};

    simulation.run();

    return 0;
}