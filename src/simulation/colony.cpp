#include "colony.hpp"
#include "environment/board.hpp"

#include <stdexcept>
#include <iostream>

Colony::Colony(const std::string name, Board &board, AnthillTile &initialAnthill, const int initialNumberOfAnts) :
    name(name),
    board(&board)
{
    anthills.push_back(&initialAnthill);

    if(initialNumberOfAnts <= 0)
    {
        throw std::runtime_error("The initial number of ants is invalid");
    }
    
    addAnts(initialNumberOfAnts);
    std::cout << "Création d'une colonie" <<std::endl;
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

void Colony::addAnts(const int numberOfAnts) noexcept
{
    for(auto i = 0; i < numberOfAnts; ++i)
    {
        ants.push_back(std::make_unique<Ant>(*this, *anthills.at(0)));
    }
}