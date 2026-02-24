#pragma once

#include "pheromones.hpp"

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
        const Coordinates& getCoordinates() const noexcept;

        int getFoodQuantity() const noexcept;
        void addFood(const int quantity = 1);
        void removeFood(const int quantity = 1);

        const Pheromones& getPheromones() const noexcept;
        void addPheromones(const PheromoneType type) noexcept;

        bool operator==(const Tile& otherTile) const noexcept; 

    private:
        const Coordinates position;
        Pheromones pheromones{0, 0};
        int food{0};
};