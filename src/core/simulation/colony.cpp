#include "colony.hpp"
#include "environment/board.hpp"

#include <stdexcept>

using namespace myrmo;

Colony::Colony(const std::string name, Board &board, AnthillTile &initialAnthill, const int initial_number_of_ants) :
    name(name),
    board(&board)
{
    anthills.push_back(&initialAnthill);

    if(initial_number_of_ants <= 0)
    {
        throw std::runtime_error("The initial number of ants is invalid");
    }
    
    addAnts(initial_number_of_ants);
}

const std::vector<AnthillTile*>& Colony::getAnthills() const noexcept
{
    return anthills;
}

const Board& Colony::getBoard() const noexcept
{
    return *board;
}

void Colony::step() const noexcept
{
    for(const auto& ant : ants)
    {
        ant->act();
    }
}

void Colony::addAnts(const int number_of_ants) noexcept
{
    for(auto i = 0; i < number_of_ants; ++i)
    {
        ants.push_back(std::make_unique<Ant>(*this, *anthills.at(0)));
    }
}