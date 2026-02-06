#ifndef TILE
#define TILE

class Tile
{
    public:
        struct Coordinates
        {
            int rowNumber;
            int columnNumber;

            bool operator==(const Coordinates& otherCoordinates) const noexcept
            {
                if(rowNumber == otherCoordinates.rowNumber && columnNumber == otherCoordinates.columnNumber)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        };

        Tile(const int row, const int column) noexcept;
        const Coordinates& getCoordinates() const noexcept;

        bool operator==(const Tile& otherTile) const noexcept;

        

    private:
        const Coordinates position;
};

#endif