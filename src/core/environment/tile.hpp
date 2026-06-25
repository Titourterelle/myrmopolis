#pragma once

#include "pheromones.hpp"
#include "snapshot.hpp"

#include "string"

namespace myrmo {

class Ant;

class Tile {
    public:
        struct Coordinates {
            unsigned int x;
            unsigned int y;
            bool operator==(const Coordinates &other) const noexcept {
                return (x == other.x && y == other.y);
            }
            bool operator<(const Coordinates &other) const noexcept {
                return (x < other.x || (x == other.x && y < other.y));
            }
        };
        
        explicit Tile(const unsigned int x, const unsigned int y) noexcept;
        virtual ~Tile() = default;

        virtual void interact(Ant &ant) noexcept = 0;
        virtual snapshot::Tile takeTileSnapshot() const noexcept;
        
        virtual std::string getType() const noexcept;
        const Coordinates& getCoordinates() const noexcept;
        const Pheromones& getPheromones() const noexcept;

        bool operator==(const Tile &other_tile) const noexcept;

    protected:
        Pheromones pheromones{0, 0};

    private:
        const Coordinates position;
};

}