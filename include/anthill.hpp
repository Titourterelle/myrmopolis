#ifndef ANTHILL
#define ANTHILL

#include "tile.hpp"
#include "ant.hpp"

#include <vector>
#include <memory>

class Anthill : public Tile
{
    public:
        explicit Anthill(const int row, const int column, const int initialNumberOfAnts) noexcept;

    private:
        void addAnts(const int numberOfAnts) noexcept;
        std::vector<std::unique_ptr<Ant>> ants;
};

#endif