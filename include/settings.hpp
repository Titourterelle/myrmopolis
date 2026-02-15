#pragma once

#include <string>
#include <vector>

struct BoardSettings
{
    int row;
    int column;
};

struct ColonySettings
{
    std::string name;
    int xAnthill;
    int yAnthill;
    int initialNumberOfAnts;
};

struct SimulationSettings
{
    BoardSettings board;
    std::vector<ColonySettings> colonies;
};