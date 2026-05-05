#include "hex_grid.hpp"

#include <cmath>
#include <stdexcept>
#include <utility>

// Public

HexGrid::HexGrid(int cols, int rows, float radius) : cols(cols), rows(rows), radius(radius) {
    if (cols == 0) {
        throw std::runtime_error("Columns number can't be null");
    }
    if (rows == 0) {
        throw std::runtime_error("Rows number can't be null");
    }
    if (radius == 0) {
        throw std::runtime_error("Radius can't be null");
    }

    computeCells();
}

int HexGrid::getHeight() const noexcept {
    return height;
}
    
int HexGrid::getWidth() const noexcept {
    return width;
}

float HexGrid::getCellsRadius() const noexcept {
    return radius;
}

const std::vector<HexCell> HexGrid::getHexCells() const noexcept {
    return cells;
}

const std::pair<float, float> HexGrid::getCellCenter(const std::pair<int, int> &coords) const {
    return cells_center.at(coords);
}

//Private

void HexGrid::computeCells() noexcept {
    cells.clear();

    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows; ++row) {
            const float x = col*radius*std::sqrt(3) + (row % 2 == 0 ? 0 : radius*sqrt(3)/2) - radius*(1-std::sqrt(3)/2);
            const float y = row*radius*1.5f;

            HexCell cell{x, y, col, row};
            cells.push_back(cell);

            const float center_x = x + radius;
            const float center_y = y + radius;
            cells_center.insert({{col, row}, {center_x, center_y}});
        }
    }

    width = (cols + 0.5f)*radius*std::sqrt(3);
    height = radius*(rows + (rows+1)/2); // NOLINT(bugprone-integer-division)
}