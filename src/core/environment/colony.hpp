#pragma once

#include "ant.hpp"
#include "anthill_tile.hpp"

#include <vector>
#include <memory>

namespace myrmo {

class Board;

class Colony
{
    public:
        explicit Colony(const std::string name, Board &board, AnthillTile &initialAnthill, const int initial_number_of_ants);

        std::string getName() const noexcept {return name;};
        int getNumberOfAnts() const noexcept;
        const std::vector<const Ant*> getAnts() const noexcept;
        const std::vector<AnthillTile*>& getAnthills() const noexcept;
        const Board& getBoard() const noexcept;

        void step() const noexcept;

    private:
        void addAnts(const int number_of_ants) noexcept;
        
        std::string name;
        const Board *board = nullptr;
        std::vector<AnthillTile*> anthills;
        std::vector<std::unique_ptr<Ant>> ants;
};

}