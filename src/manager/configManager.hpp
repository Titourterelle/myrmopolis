#pragma once

#include "settings.hpp"

#include <nlohmann/json.hpp>
#include <string>
#include <fstream>

class ConfigManager
{
    public:
        explicit ConfigManager(const std::string fileName);
        const SimulationSettings& getSettings() const noexcept;
        
    private:
        void importSettings();

        const std::string configFilename;
        std::ifstream configStream;
        nlohmann::json configJSON;
        SimulationSettings settings;
};