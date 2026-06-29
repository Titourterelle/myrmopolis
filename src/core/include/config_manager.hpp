#pragma once

#include "settings.hpp"

#include <memory>
#include <string>

namespace myrmo {

class ConfigManager {
    public:
        explicit ConfigManager(const std::string& filename);
        virtual ~ConfigManager();
        
        virtual const SimulationSettings& getSimulationSettings() const noexcept;

    protected:
        std::ifstream& getConfigFileStream() const noexcept;
        
    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
};

}