#pragma once

#include <vector>

struct HexCell {
    float pixel_x, pixel_y;
    int coord_x, coord_y;
};

class HexGrid {
    public:
        explicit HexGrid(int cols, int rows, float radius);

        int getHeight() const noexcept;
        int getWidth() const noexcept;
        float getCellsRadius() const noexcept;
        const std::vector<HexCell> getHexCells() const noexcept;

    private:
        void computeCells() noexcept;

        int height = 0;
        int width = 0;

        const unsigned int cols;
        const unsigned int rows;
        const float radius;
        std::vector<HexCell> cells;
};