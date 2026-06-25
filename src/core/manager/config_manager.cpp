#include "include/config_manager.hpp"

#include <memory>
#include <stdexcept>
#include <string>
#include <fstream>

#include <nlohmann/json.hpp>

using namespace myrmo;

struct ConfigManager::Impl {
    void importSettings();

    void importSimulationSettings(const nlohmann::json &config_json);
    void importBoardsSettings(const nlohmann::json &config_json);
    void importColoniesSettings(const nlohmann::json &config_json);

    const std::string config_filename;
    std::ifstream config_stream;
    SimulationSettings settings;
    
    Impl(const std::string filename) : config_filename(filename) {}
};

// Public

ConfigManager::ConfigManager(const std::string filename) : impl_(std::make_unique<Impl>(filename)) {
    impl_->config_stream.open(impl_->config_filename);
    if (!impl_->config_stream) {
        throw std::runtime_error("Cannot open the config file");
    }
    impl_->importSettings();
}

ConfigManager::~ConfigManager() = default;

const SimulationSettings& ConfigManager::getSettings() const noexcept {
    return impl_->settings;
}

// Private

void ConfigManager::Impl::importSettings() {
    nlohmann::json config_json;

    try {
        config_stream >> config_json;

        importSimulationSettings(config_json);
        importBoardsSettings(config_json);
        importColoniesSettings(config_json);
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

void ConfigManager::Impl::importSimulationSettings(const nlohmann::json &config_json) {
    settings.number_of_boards = config_json.at("simulation").at("number_of_boards").get<unsigned int>();
}


void ConfigManager::Impl::importBoardsSettings(const nlohmann::json &config_json) {
    settings.board.row = config_json.at("board").at("row").get<unsigned int>();
    settings.board.column = config_json.at("board").at("column").get<unsigned int>();
}


void ConfigManager::Impl::importColoniesSettings(const nlohmann::json &config_json) {
    for (const auto& colony : config_json.at("colonies")) {
        ColonySettings colony_settings;
        
        colony_settings.name = colony.at("name").get<std::string>();
        colony_settings.x_anthill = colony.at("anthill").at(0);
        colony_settings.y_anthill = colony.at("anthill").at(1);
        colony_settings.initial_number_of_ants = colony.at("initial_ants");

        settings.board.colonies.push_back(colony_settings);
    }
}