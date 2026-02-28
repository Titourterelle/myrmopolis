#pragma once

#include "settings.hpp"

#include <nlohmann/json.hpp>
#include <string>
#include <fstream>

class ConfigManager
{
    public:
        explicit ConfigManager(const std::string filename);
        const SimulationSettings& getSettings() const noexcept;
        
    private:
        void importSettings();

        const std::string config_filename;
        std::ifstream config_stream;
        nlohmann::json config_json;
        SimulationSettings settings;
};