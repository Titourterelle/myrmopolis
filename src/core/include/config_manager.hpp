#pragma once

#include "settings.hpp"

#include <memory>
#include <string>

class ConfigManager
{
    public:
        explicit ConfigManager(const std::string filename);
        ~ConfigManager();
        const SimulationSettings& getSettings() const noexcept;
        
    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
};