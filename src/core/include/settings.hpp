#pragma once

#include <string>
#include <vector>

namespace myrmo {

struct ColonySettings {
    std::string name;
    unsigned int initial_number_of_ants;
};

struct BoardSettings {
    unsigned int row;
    unsigned int column;
    unsigned long seed;
    double food_abundance;
    std::vector<ColonySettings> colonies;
};

struct SimulationSettings {
    unsigned int number_of_boards;
    BoardSettings board;
};

}