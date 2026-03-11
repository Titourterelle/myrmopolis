#pragma once

#include <string>
#include <vector>

namespace myrmo {

struct ColonySettings
{
    std::string name;
    int x_anthill;
    int y_anthill;
    int initial_number_of_ants;
};

struct BoardSettings
{
    int row;
    int column;
    std::vector<ColonySettings> colonies;
};

struct SimulationSettings
{
    int number_of_boards;
    BoardSettings board;
};

}