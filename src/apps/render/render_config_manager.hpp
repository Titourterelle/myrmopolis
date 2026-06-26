#pragma once

#include "config_manager.hpp"
#include "render_utils.hpp"

class RenderConfigManager : public myrmo::ConfigManager {
    public:
        explicit RenderConfigManager(const std::string filename);
        ~RenderConfigManager() = default;

        const RenderSettings& getRenderSettings() const noexcept;

    private:
        void importRenderSettings();

        RenderSettings render_settings;
};