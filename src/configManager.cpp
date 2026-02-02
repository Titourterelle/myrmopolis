#include "../include/configManager.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

ConfigManager::ConfigManager(const std::string fileName) : configFileName(fileName)
{
    createSelectedSettings();

    configStream.open(configFileName);
    if(configStream)
    {
        std::cout << "Le fichier est ouvert" << std::endl;
        getSettings();
    }
    else
    {
        throw std::runtime_error("Impossible d'ouvrir le fichier");
    }
}

void ConfigManager::getSettings() noexcept
{
    std::string line;

    while(std::getline(configStream, line))
    {
        std::string option;
        std::string value;
        std::istringstream iss(line);
        iss >> option >> value;
        std::cout << option << " | " << value << std::endl;

        try
        {
        selectedSettings.at(stringToSettings.at(option)) = std::stoi(value);
        }
        catch (const std::out_of_range &err)
        {
            std::cerr << "Option invalide, ligne ignorée" << std::endl;
        }
        catch (const std::invalid_argument &err)
        {
            std::cerr << "Valeur invalide, ligne ignorée" << std::endl;
        }
    }
}

void ConfigManager::createSelectedSettings() noexcept
{
    for(const auto& setting : stringToSettings)
    {
        selectedSettings.insert({setting.second, NULL});
    }
}