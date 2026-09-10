#pragma once

#include <string>
#include <vector>

namespace myrmo {

struct ColonySettings {
    std::string name;
    unsigned int x_anthill;
    unsigned int y_anthill;
    unsigned int initial_number_of_ants;
};

struct BoardSettings {
    unsigned int row;
    unsigned int column;
    std::vector<ColonySettings> colonies;
};

struct SimulationSettings {
    unsigned int number_of_boards;
    BoardSettings board;
};

}