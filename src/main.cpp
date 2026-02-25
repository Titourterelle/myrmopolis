#include "simulation/simulation.hpp"
#include "manager/configManager.hpp"

#include <string>

int main()
{
    std::string filename{"../../config.json"};
    ConfigManager CM{filename};

    Simulation simulation{CM.getSettings()};

    return 0;
}