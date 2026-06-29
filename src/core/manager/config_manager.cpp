#include "include/config_manager.hpp"

#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <stdexcept>
#include <string>
#include <fstream>

#include <nlohmann/json.hpp>

using namespace myrmo;

struct ConfigManager::Impl {
    void importSettings();

    const std::string config_filename;
    std::ifstream config_stream;
    SimulationSettings settings;
    
    Impl(const std::string filename) : config_filename(filename) {}
};

// Public

ConfigManager::ConfigManager(const std::string& filename) : impl_(std::make_unique<Impl>(filename)) {
    impl_->config_stream.open(impl_->config_filename);
    if (!impl_->config_stream) {
        throw std::runtime_error("Cannot open the config file");
    }
    impl_->importSettings();
}

ConfigManager::~ConfigManager() = default;

const SimulationSettings& ConfigManager::getSimulationSettings() const noexcept {
    return impl_->settings;
}

// Protected

std::ifstream& ConfigManager::getConfigFileStream() const noexcept {
    return impl_->config_stream;
}

// Private

void ConfigManager::Impl::importSettings() {
    nlohmann::json config_json;

    try {
        config_stream >> config_json;

        const nlohmann::json &simulation_config = config_json.at("simulation");

        settings.number_of_boards = simulation_config.at("number_of_boards").get<int>();

        settings.board.row = simulation_config.at("board").at("row").get<int>();
        settings.board.column = simulation_config.at("board").at("column").get<int>();

        for (const auto& colony : simulation_config.at("colonies")) {
            ColonySettings colony_settings;
            colony_settings.name = colony.at("name").get<std::string>();
            colony_settings.x_anthill = colony.at("anthill").at(0);
            colony_settings.y_anthill = colony.at("anthill").at(1);
            colony_settings.initial_number_of_ants = colony.at("initial_ants");

            settings.board.colonies.push_back(colony_settings);
        }
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