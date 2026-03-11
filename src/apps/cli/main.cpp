#include "simulation.hpp"
#include "config_manager.hpp"

int main()
{
    std::string filename{"../../config.json"};
    myrmo::ConfigManager config_manager{filename};

    myrmo::Simulation simulation{config_manager.getSettings()};

    while(!simulation.isOver())
    {
        simulation.nextStep();
    }

    return 0;
}