#pragma once

#include <map>
#include <utility>
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
        const std::pair<float, float> getCellCenter(const std::pair<int, int> &coords) const;

    private:
        void computeCells() noexcept;

        int height = 0;
        int width = 0;

        const unsigned int cols;
        const unsigned int rows;
        const float radius;
        std::vector<HexCell> cells;
        std::map<std::pair<int, int>, std::pair<float, float>> cells_center;
};