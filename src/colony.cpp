#include "../include/colony.hpp"

#include <stdexcept>
#include <iostream>

Colony::Colony(const std::string name, Anthill &initialAnthill, const int initialNumberOfAnts) :
    name(name)
{
    anthills.push_back(&initialAnthill);

    if(initialNumberOfAnts <= 0)
    {
        throw std::runtime_error("The initial number of ants is invalid");
    }
    
    addAnts(initialNumberOfAnts);
    std::cout << "Création d'une colonie" <<std::endl;
}

const std::vector<Anthill*>& Colony::getAnthills() const noexcept
{
    return anthills;
}

void Colony::addAnts(const int numberOfAnts) noexcept
{
    for(auto i = 0; i < numberOfAnts; ++i)
    {
        ants.push_back(std::make_unique<Ant>(*this));
    }
}