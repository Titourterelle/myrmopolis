#pragma once

#include <string>
#include <vector>


struct ColonySettings
{
    std::string name;
    int xAnthill;
    int yAnthill;
    int initialNumberOfAnts;
};

struct BoardSettings
{
    int row;
    int column;
    std::vector<ColonySettings> colonies;
};

struct SimulationSettings
{
    int numberOfBoards;
    BoardSettings board;
};