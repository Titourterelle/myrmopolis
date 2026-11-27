#pragma once

#include "settings.hpp"

#include <memory>
#include <string>

// Default Settings
#define DEFAULT_CONFIG_NUMBER_OF_BOARDS 1
#define DEFAULT_CONFIG_FOOD_ABUNDANCE 0.25
#define DEFAULT_CONFIG_NUMBER_OF_COLONIES 1
#define DEFAULT_CONFIG_FIRST_COLONY_NAME 1
#define DEFAULT_CONFIG_NUMBER_OF_ANTS 20

namespace myrmo {

class ConfigManager {
    public:
        explicit ConfigManager(const std::string& filename);
        virtual ~ConfigManager();
        
        [[nodiscard]] virtual const SimulationSettings& getSimulationSettings() const noexcept;

    protected:
        [[nodiscard]] std::ifstream& getConfigFileStream() const noexcept;
        
    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
};

}