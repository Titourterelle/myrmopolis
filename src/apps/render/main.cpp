#include "simulation.hpp"
#include "config_manager.hpp"

#include <SFML/Graphics.hpp>

int main()
{
    myrmo::ConfigManager cm{"../../config.json"};
    myrmo::Simulation sim{cm.getSettings()};

    return 0;
}