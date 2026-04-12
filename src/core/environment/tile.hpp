#pragma once

#include "pheromones.hpp"

#include "string"

namespace myrmo {

class Ant;

class Tile
{
    public:
        struct Coordinates
        {
            int x;
            int y;
            bool operator==(const Coordinates &other) const noexcept
            {
                return (x == other.x && y == other.y);
            }
            bool operator<(const Coordinates &other) const noexcept
            {
                return (x < other.x || (x == other.x && y < other.y));
            }
        };
        
        explicit Tile(const int x, const int y) noexcept;
        virtual ~Tile() = default;

        const Coordinates& getCoordinates() const noexcept;
        const Pheromones& getPheromones() const noexcept;
        virtual std::string getType() const noexcept = 0;
        virtual void interact(Ant &ant) noexcept = 0;

        bool operator==(const Tile &other_tile) const noexcept;

    protected:
        Pheromones pheromones{0, 0};

    private:
        const Coordinates position;
};

}