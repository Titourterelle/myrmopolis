#include "render_config_manager.hpp"
#include "config_manager.hpp"

#include <fstream>

#include <nlohmann/json.hpp>

// Public

RenderConfigManager::RenderConfigManager(const std::string filename) : myrmo::ConfigManager(filename) {}

const RenderSettings& RenderConfigManager::getRenderSettings() const noexcept {
    return render_settings;
}

// Private

void RenderConfigManager::importRenderSettings() {
    nlohmann::json config_json;

    std::ifstream& config_stream = getConfigFileStream();

    try {
        config_stream >> config_json;
        // TODO : Import the settings
    }
    catch (const nlohmann::json::parse_error &e) {
        throw std::runtime_error("Invalid JSON format");
    }
    catch (const nlohmann::json::out_of_range &e) {
        throw std::runtime_error("Missing required configuration field");
    }
    catch (const nlohmann::json::type_error &e) {
        throw std::runtime_error("Invalid type in the configuration file");
    }
}