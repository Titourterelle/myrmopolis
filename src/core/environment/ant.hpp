#pragma once

#include "anthill_tile.hpp"
#include "tile.hpp"
#include "pheromones.hpp"

#include <vector>

namespace myrmo {

class Board;
class Colony;

class Ant {
    public:
        explicit Ant(Colony &colony, Tile &spawn_tile) noexcept;

        void act() noexcept;
        void pickFood();
        void dropFood() noexcept;
        
        bool isTransportingFood() const noexcept;
        const Tile::Coordinates getPosition() const noexcept;
        const Tile::Coordinates getPreviousPosition() const noexcept;

    private:
        void move(Tile &next_tile) noexcept;
        const std::vector<AnthillTile*> searchAnthills(const std::vector<Tile*> &tiles_list) const noexcept;
        void sortTilesByPheromones(std::vector<Tile*> &tiles_list, const PheromoneType pheromone) const noexcept;
        void removeTile(std::vector<Tile*> &tiles_list, const Tile &tile_to_remove) const noexcept;
        
        Tile *actual_tile = nullptr;
        Tile *previous_tile = nullptr;
        const Colony *colony;
        const Board *board;
        bool is_transporting_food = false;
        
        const double pheromone_sensitivity = 0.7;
};

}