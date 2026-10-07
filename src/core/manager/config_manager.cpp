#include "config_manager.hpp"

#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

namespace myrmo {
struct ConfigManager::Impl {
    void importSettings();

    void importSimulationSettings(const nlohmann::json& config_json);
    void importBoardsSettings(const nlohmann::json& config_json);
    void importColoniesSettings(const nlohmann::json& config_json);

    const std::string config_filename_;
    std::ifstream config_stream_;
    SimulationSettings settings_;
    
    Impl(std::string  filename) : config_filename_(std::move(filename)) {}
};

// Public

ConfigManager::ConfigManager(const std::string& filename) : impl_(std::make_unique<Impl>(filename)) {
    impl_->config_stream_.open(impl_->config_filename_);
    if (!impl_->config_stream_) {
        throw std::runtime_error("Cannot open the config file");
    }
    impl_->importSettings();
}

ConfigManager::~ConfigManager() = default;

const SimulationSettings& ConfigManager::getSimulationSettings() const noexcept {
    return impl_->settings_;
}

// Protected

std::ifstream& ConfigManager::getConfigFileStream() const noexcept {
    return impl_->config_stream_;
}

// Private

void ConfigManager::Impl::importSettings() {
    try {
        nlohmann::json config_json;
        config_stream_ >> config_json;
        config_json = config_json.at("simulation");

        importSimulationSettings(config_json);
        importBoardsSettings(config_json);
        importColoniesSettings(config_json);
    }
    catch (const nlohmann::json::parse_error& e) {
        throw std::runtime_error("Invalid JSON format");
    }
    catch (const nlohmann::json::out_of_range& e) {
        throw std::runtime_error("Missing required configuration field");
    }
    catch (const nlohmann::json::type_error& e) {
        throw std::runtime_error("Invalid type in the configuration file");
    }
}

void ConfigManager::Impl::importSimulationSettings(const nlohmann::json& config_json) {
    settings_.number_of_boards = config_json.at("number_of_boards").get<unsigned int>();
}


void ConfigManager::Impl::importBoardsSettings(const nlohmann::json& config_json) {
    settings_.board.row = config_json.at("board").at("row").get<unsigned int>();
    settings_.board.column = config_json.at("board").at("column").get<unsigned int>();
}


void ConfigManager::Impl::importColoniesSettings(const nlohmann::json& config_json) {
    for (const auto& colony : config_json.at("colonies")) {
        ColonySettings colony_settings;
        
        colony_settings.name = colony.at("name").get<std::string>();
        colony_settings.initial_number_of_ants = colony.at("initial_ants");

        settings_.board.colonies.push_back(colony_settings);
    }
}
}