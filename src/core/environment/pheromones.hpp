#pragma once

namespace myrmo {

struct Pheromones
{
    int home = 0;
    int food = 0;
};

enum class PheromoneType
{
    Home,
    Food
};

}