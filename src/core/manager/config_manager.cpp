#include "include/config_manager.hpp"

#include <memory>
#include <stdexcept>
#include <string>
#include <fstream>

#include <nlohmann/json.hpp>

using namespace myrmo;

struct ConfigManager::Impl
{
    const std::string config_filename;
    std::ifstream config_stream;
    nlohmann::json config_json;
    SimulationSettings settings;

    void importSettings();

    Impl(const std::string filename) : config_filename(filename) {}
};

ConfigManager::ConfigManager(const std::string filename) : impl_(std::make_unique<Impl>(filename))
{
    impl_->config_stream.open(impl_->config_filename);
    if(!impl_->config_stream)
    {
        throw std::runtime_error("Cannot open the config file");
    }
    impl_->importSettings();
}

ConfigManager::~ConfigManager() = default;

const SimulationSettings& ConfigManager::getSettings() const noexcept
{
    return impl_->settings;
}

void ConfigManager::Impl::importSettings()
{
    try
    {
        config_stream >> config_json;

        settings.number_of_boards = config_json.at("simulation").at("number_of_boards").get<int>();

        settings.board.row = config_json.at("board").at("row").get<int>();
        settings.board.column = config_json.at("board").at("column").get<int>();

        for(const auto& colony : config_json.at("colonies"))
        {
            ColonySettings colony_settings;
            colony_settings.name = colony.at("name").get<std::string>();
            colony_settings.x_anthill = colony.at("anthill").at(0);
            colony_settings.y_anthill = colony.at("anthill").at(1);
            colony_settings.initial_number_of_ants = colony.at("initial_ants");

            settings.board.colonies.push_back(colony_settings);
        }
    }
    catch(const nlohmann::json::parse_error &e)
    {
        throw std::runtime_error("Invalid JSON format");
    }
    catch(const nlohmann::json::out_of_range &e)
    {
        throw std::runtime_error("Missing required configuration field");
    }
    catch(const nlohmann::json::type_error &e)
    {
        throw std::runtime_error("Invalid type in the configuration file");
    }
}