#pragma once

#include "anthill_tile.hpp"
#include "pheromones.hpp"
#include "tile.hpp"

#include <vector>

namespace myrmo {

class Board;
class Colony;

class Ant {
    public:
        explicit Ant(const Colony& colony, Tile& spawn_tile) noexcept;

        void act() noexcept;
        void pickFood();
        void dropFood() noexcept;
        
        [[nodiscard]] unsigned int getId() const noexcept;
        [[nodiscard]] bool isTransportingFood() const noexcept;
        [[nodiscard]] Tile::Coordinates getPosition() const noexcept;

    private:
        void move(Tile &next_tile) noexcept;
        [[nodiscard]] std::vector<AnthillTile*> searchAnthills(const std::vector<Tile*>& tiles_list) const noexcept;
        static void sortTilesByPheromones(std::vector<Tile*>& tiles_list, const PheromoneType& pheromone) noexcept;
        static void removeTile(std::vector<Tile*>& tiles_list, const Tile& tile_to_remove) noexcept;

        static unsigned int id_count_;

        const unsigned int id_;
        Tile *actual_tile_ = nullptr;
        Tile *previous_tile_ = nullptr;
        const Colony *colony_;
        const Board *board_;
        bool is_transporting_food_ = false;
        
        const double pheromone_sensitivity_ = 0.7;
};

}