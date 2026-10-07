#include "map_generator.hpp"
#include "map_utils.hpp"
#include "environment/anthill_tile.hpp"
#include "environment/land_tile.hpp"

#include <algorithm>
#include <random>

namespace {

template <typename T, typename URBG>
void partialFisherYatesShuffle(std::vector<T>& vec, URBG&& gen, const size_t iteration) {
    using distrib_t = std::uniform_int_distribution<size_t>;
    using param_t = distrib_t::param_type;

    distrib_t distr;
    const size_t iter = std::min(iteration, vec.size());
    for (size_t i = 0; i < iter; ++i)
    {
        std::swap(vec[i], vec[distr(gen, param_t(i, vec.size() - 1))]);
    }
}

}

namespace myrmo {

// Public

MapGenerator::MapGenerator(const MapSettings settings) :
    settings_(settings),
    random_engine_(settings_.seed),
    is_containing_food_distrib_(0.3),
    quantity_food_distrib_(1, 10) {}

std::vector<AnthillTile*> MapGenerator::createMap(TileMap& map) {
    std::vector<AnthillTile*> anthills;
    const std::set<Tile::Coordinates> anthills_coords = chooseAnthillsCoords(map.height, map.width);

    for (auto x = 0; x < map.width; x++) {
        for (auto y = 0; y < map.height; y++) {
            Tile::Coordinates coords(x, y);

            if (anthills_coords.contains(coords)) {
                map.tiles.push_back(std::make_unique<AnthillTile>(coords));             // No need to check the cast
                anthills.push_back(dynamic_cast<AnthillTile*>(map.tiles.back().get()));   // unless changes
                continue;
            }

            map.tiles.push_back(std::make_unique<LandTile>(coords));
        }
    }
    return anthills;
}

// Private

std::set<Tile::Coordinates> MapGenerator::chooseAnthillsCoords(const unsigned int height, const unsigned int width) {
    std::vector<unsigned int> existing_coords;
    std::set<Tile::Coordinates> anthills_coords;

    for (unsigned int i = 0; i < height*width; i++) {
        existing_coords.push_back(i);
    }

    const size_t count = std::min(settings_.number_of_colonies, existing_coords.size());
    partialFisherYatesShuffle(existing_coords, random_engine_, count);

    for (auto i = 0; i < count; i++) {
        anthills_coords.insert(Tile::Coordinates(existing_coords[i]/height, existing_coords[i]%height));
    }

    return anthills_coords;
}
}
