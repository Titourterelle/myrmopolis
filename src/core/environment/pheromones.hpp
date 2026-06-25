#pragma once

namespace myrmo {

struct Pheromones {
    unsigned int home = 0;
    unsigned int food = 0;
};

enum class PheromoneType {
    Home,
    Food
};

}