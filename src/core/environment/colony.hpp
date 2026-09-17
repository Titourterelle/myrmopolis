#pragma once

#include "ant.hpp"
#include "anthill_tile.hpp"

#include <memory>
#include <vector>

namespace myrmo {

class Board;

class Colony {
    public:
        explicit Colony(std::string name, const Board& board, AnthillTile& initialAnthill, int initial_number_of_ants);

        void step() const noexcept;
        
        [[nodiscard]] std::string getName() const noexcept {return name_;};
        [[nodiscard]] size_t getNumberOfAnts() const noexcept;
        [[nodiscard]] const Board& getBoard() const noexcept;
        [[nodiscard]] const std::vector<AnthillTile*>& getAnthills() const noexcept;
        [[nodiscard]] std::vector<const Ant*> getAnts() const noexcept;

    private:
        void addAnts(int number_of_ants) noexcept;
        
        std::string name_;
        const Board *board_ = nullptr;
        std::vector<AnthillTile*> anthills_;
        std::vector<std::unique_ptr<Ant>> ants_;
};

}