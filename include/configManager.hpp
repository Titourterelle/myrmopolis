#ifndef CONFIG_MANAGER
#define CONFIG_MANAGER

#include "settings.hpp"

#include <unordered_map>
#include <string>
#include <fstream>

class ConfigManager
{
    public:
        explicit ConfigManager(const std::string fileName);
        const std::unordered_map<Settings, int>& getSettings() const noexcept;
        
    private:
        void importSettings() noexcept;
        void createSelectedSettings() noexcept;

        const std::string configFileName;
        std::ifstream configStream;
        std::unordered_map<Settings, int> selectedSettings;
};

#endif