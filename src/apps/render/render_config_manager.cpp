#include "render_config_manager.hpp"
#include "config_manager.hpp"
#include "render_utils.hpp"

#include <fstream>
#include <string>

#include <nlohmann/json.hpp>

// Public

RenderConfigManager::RenderConfigManager(const std::string& filename) : ConfigManager(filename) {
    importRenderSettings();
}

std::vector<RenderSettings> RenderConfigManager::getRenderSettings() const noexcept {
    return render_settings_;
}

// Private

const std::unordered_map<std::string, RenderQuality> RenderConfigManager::STR_TO_QUALITY {
    {"low", RenderQuality::Low},
    {"medium", RenderQuality::Medium},
    {"high", RenderQuality::High},
};

RenderQuality RenderConfigManager::convertStrToQuality(const std::string& input) {
    const auto it = STR_TO_QUALITY.find(input);
    if (it == STR_TO_QUALITY.end()) {
        throw std::invalid_argument("Unknown render quality: " + input);
    }
    return it->second;
}

void RenderConfigManager::importRenderSettings() {
    std::ifstream& config_stream = getConfigFileStream();
    config_stream.clear();
    config_stream.seekg(0);

    try {
        nlohmann::json config_json;
        config_stream >> config_json;

        for (const auto& render : config_json.at("rendering"))
        {
            RenderSettings settings;

            settings.fps = render.at("fps").get<unsigned int>();
            settings.frames_per_step = render.at("frames-per-step").get<unsigned int>();
            settings.output_dir = render.at("output-directory").get<std::string>();

            settings.quality = convertStrToQuality(render.at("quality").get<std::string>());

            render_settings_.push_back(settings);

        }
    }
    catch (const nlohmann::json::parse_error) {
        throw std::runtime_error("Invalid JSON format");
    }
    catch (const nlohmann::json::out_of_range) {
        throw std::runtime_error("Missing required configuration field");
    }
    catch (const nlohmann::json::type_error) {
        throw std::runtime_error("Invalid type in the configuration file");
    }
}
