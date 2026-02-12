#pragma once

#include "ant.hpp"
#include "anthill.hpp"

#include <vector>
#include <memory>

class Colony
{
    public:
        explicit Colony(const int initialNumberOfAnts);
    private:
        void addAnts(const int numberOfAnts) noexcept;
        
        std::vector<Anthill*> anthills;
        std::vector<std::unique_ptr<Ant>> ants;
};