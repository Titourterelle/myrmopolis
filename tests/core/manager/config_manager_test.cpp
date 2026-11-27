#include <gtest/gtest.h>

#include <string>

#include "config_manager.hpp"

class ConfigManagerTest : public ::testing::Test {
    protected:
        ConfigManagerTest() = default;

        // Test File Paths
        const std::string minimal_file{"minimal_config_test.json"};

        // Config Managers
        const myrmo::ConfigManager minimal_config_manager{minimal_file};

        // Settings
        const myrmo::SimulationSettings default_settings = minimal_config_manager.getSimulationSettings();
};



TEST_F(ConfigManagerTest, FillEmptyFieldWithDefaultValue) {
    EXPECT_EQ(default_settings.number_of_boards, DEFAULT_CONFIG_NUMBER_OF_BOARDS);
    EXPECT_EQ(default_settings.board.food_abundance, DEFAULT_CONFIG_FOOD_ABUNDANCE);
    EXPECT_EQ(default_settings.board.colonies.size(), DEFAULT_CONFIG_NUMBER_OF_COLONIES);
    for (int i = DEFAULT_CONFIG_FIRST_COLONY_NAME; const auto& [name, initial_number_of_ants] : default_settings.board.colonies) {
        EXPECT_EQ(name, std::to_string(i));
        EXPECT_EQ(initial_number_of_ants, DEFAULT_CONFIG_NUMBER_OF_ANTS);
        i++;
    }
}