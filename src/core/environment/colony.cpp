#include "colony.hpp"
#include "board.hpp"

#include <stdexcept>
#include <utility>

using namespace myrmo;

// Public

Colony::Colony(std::string name, const Board& board, AnthillTile& initialAnthill, const int initial_number_of_ants) :
    name_(std::move(name)),
    board_(&board)
{
    anthills_.push_back(&initialAnthill);
    
    if (initial_number_of_ants <= 0) {
        throw std::runtime_error("The initial number of ants is invalid");
    }
    
    addAnts(initial_number_of_ants);
}

void Colony::step() const noexcept {
    for (const auto& ant : ants_) {
        ant->act();
    }
}

size_t Colony::getNumberOfAnts() const noexcept {
    return ants_.size();
}

const Board& Colony::getBoard() const noexcept {
    return *board_;
}

const std::vector<AnthillTile*>& Colony::getAnthills() const noexcept {
    return anthills_;
}

std::vector<const Ant*> Colony::getAnts() const noexcept {
    std::vector<const Ant*> return_ants;
    for (const auto& ant : ants_) {
        return_ants.push_back(ant.get());
    }
    return return_ants;
}

// Private

void Colony::addAnts(const int number_of_ants) noexcept {
    for (auto i = 0; i < number_of_ants; ++i) {
        ants_.push_back(std::make_unique<Ant>(*this, *anthills_.at(0)));
    }
}