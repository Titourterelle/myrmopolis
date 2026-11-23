#include <gtest/gtest.h>
#include <ranges>

#include "simulation/map_generator.hpp"
#include "simulation/map_utils.hpp"


class MapGeneratorTest : public ::testing::Test {
    protected:
        MapGeneratorTest() = default;

        const unsigned long seed{42};
        const unsigned long colonies{3};
        const double food_ab{0.25};
        myrmo::MapSettings basic_settings{.seed = seed, .number_of_colonies = colonies, .food_abundance = food_ab};

        const unsigned int width{26}, height{11};
        myrmo::TileMap basic_tile_map{width, height};

        myrmo::MapGenerator basic_gen{basic_settings};
};



TEST_F(MapGeneratorTest, RightTileMapSize) {
    const unsigned int old_width = basic_tile_map.width;
    const unsigned int old_height = basic_tile_map.height;

    auto result = basic_gen.createMap(basic_tile_map);

    EXPECT_EQ(basic_tile_map.width, old_width);
    EXPECT_EQ(basic_tile_map.height, old_height);
    ASSERT_EQ(basic_tile_map.width*basic_tile_map.height, basic_tile_map.tiles.size());
}

TEST_F(MapGeneratorTest, RightAnthillNumber) {
    const auto anthills = basic_gen.createMap(basic_tile_map);
    EXPECT_EQ(anthills.size(), basic_settings.number_of_colonies);
}

TEST_F(MapGeneratorTest, SameSettingsSameAnthills) {
    myrmo::MapGenerator map_generator_a{basic_settings};
    myrmo::TileMap tile_map_a{width, height};
    const auto anthills_a = map_generator_a.createMap(tile_map_a);

    myrmo::MapGenerator map_generator_b{basic_settings};
    myrmo::TileMap tile_map_b{width, height};
    const auto anthills_b = map_generator_b.createMap(tile_map_b);

    ASSERT_EQ(anthills_a.size(), anthills_b.size());
    for (const auto& [anthill_a, anthill_b]: std::ranges::views::zip(anthills_a, anthills_b)) {
        EXPECT_EQ(anthill_a->getCoordinates(), anthill_b->getCoordinates());
    }
}

TEST_F(MapGeneratorTest, ThrowWithNegFoodAbundance) {
    auto neg_fa_settings = basic_settings;
    neg_fa_settings.food_abundance = -0.5;
    ASSERT_THROW(myrmo::MapGenerator{neg_fa_settings}, std::logic_error);
}

TEST_F(MapGeneratorTest, ThrowWithOverFoodAbundance) {
    auto over_fa_settings = basic_settings;
    over_fa_settings.food_abundance = 1.5;
    ASSERT_THROW(myrmo::MapGenerator{over_fa_settings}, std::logic_error);
}

TEST_F(MapGeneratorTest, ThrowWithInvalidMapDimensions) {
    myrmo::TileMap tm_width_null{0, height};
    myrmo::TileMap tm_height_null{width, 0};
    myrmo::TileMap tm_both_null{0, 0};

    EXPECT_THROW(const auto r1 = basic_gen.createMap(tm_width_null), std::logic_error);
    EXPECT_THROW(const auto r2 = basic_gen.createMap(tm_height_null), std::logic_error);
    EXPECT_THROW(const auto r3 = basic_gen.createMap(tm_both_null), std::logic_error);
}