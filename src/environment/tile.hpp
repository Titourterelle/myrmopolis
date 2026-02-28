#pragma once

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
        virtual void interact(Ant &ant) noexcept = 0;

        bool operator==(const Tile &otherTile) const noexcept; 

    private:
        const Coordinates position;
};