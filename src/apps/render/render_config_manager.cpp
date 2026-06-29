#include "render_config_manager.hpp"
#include "config_manager.hpp"
#include "render_utils.hpp"

#include <fstream>

#include <nlohmann/json.hpp>
#include <string>

// Public

RenderConfigManager::RenderConfigManager(const std::string& filename) : ConfigManager(filename) {
    importRenderSettings();
}

const RenderSettings& RenderConfigManager::getRenderSettings() const noexcept {
    return render_settings;
}

// Private

const std::unordered_map<std::string, RenderQuality> RenderConfigManager::str_to_quality {
    {"low", RenderQuality::Low},
    {"medium", RenderQuality::Medium},
    {"high", RenderQuality::High},
};

void RenderConfigManager::importRenderSettings() {
    std::ifstream& config_stream = getConfigFileStream();
    config_stream.clear();
    config_stream.seekg(0);

    try {
        nlohmann::json config_json;
        config_stream >> config_json;
        const nlohmann::json &rendering_config = config_json.at("rendering");
    
        render_settings.fps = rendering_config.at("fps").get<unsigned int>();
        render_settings.frames_per_step = rendering_config.at("frames_per_step").get<unsigned int>();
        render_settings.output_dir = rendering_config.at("output_directory").get<std::string>();

        render_settings.quality = convertStrToQuality(rendering_config.at("quality").get<std::string>());
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

RenderQuality RenderConfigManager::convertStrToQuality(const std::string& input) {
    const auto it = str_to_quality.find(input);
    if (it == str_to_quality.end()) {
        throw std::invalid_argument("Unknown render quality: " + input);
    }
    return it->second;
}