#include "configManager.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

ConfigManager::ConfigManager(const std::string filename) : configFilename(filename)
{
    configStream.open(configFilename);
    if(!configStream)
    {
        throw std::runtime_error("Cannot open the config file");
    }

    std::cout << "The file is open" << std::endl;
    importSettings();
}

const SimulationSettings& ConfigManager::getSettings() const noexcept
{
    return settings;
}

void ConfigManager::importSettings()
{
    try
    {
        configStream >> configJSON;

        settings.board.row = configJSON.at("board").at("row").get<int>();
        settings.board.column = configJSON.at("board").at("column").get<int>();

        for(const auto& colony : configJSON.at("colonies"))
        {
            ColonySettings colonySettings;
            colonySettings.name = colony.at("name").get<std::string>();
            colonySettings.xAnthill = colony.at("anthill").at(0);
            colonySettings.yAnthill = colony.at("anthill").at(1);
            colonySettings.initialNumberOfAnts = colony.at("initialAnts");

            settings.colonies.push_back(colonySettings);
        }
    }
    catch(const nlohmann::json::parse_error &e)
    {
        throw std::runtime_error("Invalid JSON format");
    }
    catch(const nlohmann::json::out_of_range &e)
    {
        throw std::runtime_error("Missing required configuration field");
    }
    catch(const nlohmann::json::type_error &e)
    {
        throw std::runtime_error("Invalid type in the configuration file");
    }
}