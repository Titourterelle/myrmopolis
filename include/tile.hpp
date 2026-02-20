#pragma once

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

        bool operator==(const Tile& otherTile) const noexcept; 

    private:
        const Coordinates position;
};