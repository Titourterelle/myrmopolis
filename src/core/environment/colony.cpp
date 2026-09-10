#include "colony.hpp"
#include "board.hpp"

#include <stdexcept>
#include <utility>

using namespace myrmo;

// Public

Colony::Colony(std::string name, const Board &board, AnthillTile &initialAnthill, const int initial_number_of_ants) :
    name(std::move(name)),
    board(&board)
{
    anthills.push_back(&initialAnthill);
    
    if (initial_number_of_ants <= 0) {
        throw std::runtime_error("The initial number of ants is invalid");
    }
    
    addAnts(initial_number_of_ants);
}

void Colony::step() const noexcept {
    for (const auto& ant : ants) {
        ant->act();
    }
}

size_t Colony::getNumberOfAnts() const noexcept {
    return ants.size();
}

const Board& Colony::getBoard() const noexcept {
    return *board;
}

const std::vector<AnthillTile*>& Colony::getAnthills() const noexcept {
    return anthills;
}

std::vector<const Ant*> Colony::getAnts() const noexcept {
    std::vector<const Ant*> return_ants;
    for (const auto& ant : ants) {
        return_ants.push_back(ant.get());
    }
    return return_ants;
}

// Private

void Colony::addAnts(const int number_of_ants) noexcept {
    for (auto i = 0; i < number_of_ants; ++i) {
        ants.push_back(std::make_unique<Ant>(*this, *anthills.at(0)));
    }
}