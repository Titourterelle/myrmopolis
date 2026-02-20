#pragma once

#include "ant.hpp"
#include "anthill.hpp"

#include <vector>
#include <memory>

class Colony
{
    public:
        explicit Colony(const std::string name, Anthill &initialAnthill, const int initialNumberOfAnts);
        const std::vector<Anthill*>& getAnthills() const noexcept;
    private:
        void addAnts(const int numberOfAnts) noexcept;
        
        std::string name;
        std::vector<Anthill*> anthills;
        std::vector<std::unique_ptr<Ant>> ants;
};