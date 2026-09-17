#include "ant.hpp"
#include "anthill_tile.hpp"
#include "board.hpp"
#include "colony.hpp"
#include "pheromones.hpp"
#include "tile.hpp"

#include <algorithm>
#include <cstddef>
#include <map>
#include <random>
#include <stdexcept>
#include <vector>

using namespace myrmo;

// Public

Ant::Ant(const Colony& colony, Tile& spawn_tile) noexcept :
    id_(++id_count),
    actual_tile_(&spawn_tile),
    previous_tile_(actual_tile_),
    colony_(&colony),
    board_(&colony.getBoard())
{}

void Ant::act() noexcept {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    Tile* next_tile = nullptr;
    
    std::vector<Tile*> adjacent_tiles = board_->getAdjacentTiles(*actual_tile_);
    
    if (isTransportingFood()) {
        std::vector<AnthillTile*> nearby_anthills = searchAnthills(adjacent_tiles);

        if (!nearby_anthills.empty()) {
            std::uniform_int_distribution<size_t> uni_dist(0, nearby_anthills.size() - 1);
            next_tile = nearby_anthills.at(uni_dist(gen));
        }
        else {
            removeTile(adjacent_tiles, *actual_tile_);
            sortTilesByPheromones(adjacent_tiles, PheromoneType::Home);
            next_tile = adjacent_tiles[0];
        }
    }
    else {
        removeTile(adjacent_tiles, *previous_tile_);
        sortTilesByPheromones(adjacent_tiles, PheromoneType::Food);
        
        std::geometric_distribution<> geo_dist(pheromone_sensitivity_);
        unsigned long index = geo_dist(gen);
        
        if (index >= adjacent_tiles.size()) {
            std::uniform_int_distribution<size_t> uni_dist(0, adjacent_tiles.size() - 1);
            index = uni_dist(gen);
        }
        
        next_tile = adjacent_tiles.at(index);
    }
    
    move(*next_tile);
    actual_tile_->interact(*this);
}

void Ant::pickFood() {
    if (isTransportingFood()) {
        throw std::runtime_error("The ant is already transporting food");
    }
    
    is_transporting_food_ = true;
}

void Ant::dropFood() noexcept {
    is_transporting_food_ = false;
}

unsigned int Ant::getId() const noexcept {
    return id_;
}

bool Ant::isTransportingFood() const noexcept {
    return is_transporting_food_;
}

Tile::Coordinates Ant::getPosition() const noexcept {
    return actual_tile_->getCoordinates();
}

// Private

void Ant::move(Tile& next_tile) noexcept {
    previous_tile_ = actual_tile_;
    actual_tile_ = &next_tile;
}

std::vector<AnthillTile*> Ant::searchAnthills(const std::vector<Tile*>& tiles_list) const noexcept {
    std::vector<AnthillTile*> anthills_found;

    std::map<const Tile::Coordinates*, AnthillTile*> coordinates_anthills;
    for (const auto& anthill : colony_->getAnthills()) {
        coordinates_anthills[&anthill->getCoordinates()] = anthill;
    }

    for (const auto& tile : tiles_list) {
        if (coordinates_anthills.contains(&tile->getCoordinates())) {
            anthills_found.push_back(coordinates_anthills.at(&tile->getCoordinates()));
        }
    }

    return anthills_found;
}

void Ant::sortTilesByPheromones(std::vector<Tile*>& tiles_list, const PheromoneType& pheromone) noexcept {
    std::ranges::sort(tiles_list,
                      [&pheromone](const Tile *left_tile, const Tile *right_tile) {
                          if (pheromone == PheromoneType::Home) { return (left_tile->getPheromones().home > right_tile->getPheromones().home); }
                          if (pheromone == PheromoneType::Food) { return (left_tile->getPheromones().food > right_tile->getPheromones().food); }
                          return true;
                      }
    );
}

void Ant::removeTile(std::vector<Tile*>& tiles_list, const Tile& tile_to_remove) noexcept {
    for (auto i = 0; i < tiles_list.size(); ++i) {
        if (*tiles_list.at(i) == tile_to_remove) {
            tiles_list.erase(tiles_list.begin() + i);
        }
    }
}

unsigned int Ant::id_count = 0;
