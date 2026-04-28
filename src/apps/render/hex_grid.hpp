#pragma once

#include <vector>

struct HexCell {
    float pixel_x, pixel_y;
    int coord_x, coord_y;
};

class HexGrid {
    public:
        explicit HexGrid(int cols, int rows, float radius);

        const std::vector<HexCell> getHexCells() const noexcept;

    private:
        void computeCells() noexcept;

        const unsigned int cols;
        const unsigned int rows;
        const float radius;
        std::vector<HexCell> cells;
};