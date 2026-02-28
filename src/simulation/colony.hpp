#pragma once

#include "ant.hpp"
#include "environment/anthillTile.hpp"

#include <vector>
#include <memory>

class Board;

class Colony
{
    public:
        explicit Colony(const std::string name, Board &board, AnthillTile &initialAnthill, const int initialNumberOfAnts);
        const std::vector<AnthillTile*>& getAnthills() const noexcept;
        const Board& getBoard() const noexcept;
        void step() const noexcept;

    private:
        void addAnts(const int numberOfAnts) noexcept;
        
        std::string name;
        const Board *board = nullptr;
        std::vector<AnthillTile*> anthills;
        std::vector<std::unique_ptr<Ant>> ants;
};