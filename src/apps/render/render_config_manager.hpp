#pragma once

#include "config_manager.hpp"
#include "render_utils.hpp"

#include <unordered_map>

class RenderConfigManager : public myrmo::ConfigManager {
    public:
        explicit RenderConfigManager(const std::string& filename);
        ~RenderConfigManager() override = default;

        [[nodiscard]] std::vector<RenderSettings> getRenderSettings() const noexcept;

    private:
        static const std::unordered_map<std::string, RenderQuality> STR_TO_QUALITY;

        static RenderQuality convertStrToQuality(const std::string& input);

        void importRenderSettings();

        std::vector<RenderSettings> render_settings_;
};