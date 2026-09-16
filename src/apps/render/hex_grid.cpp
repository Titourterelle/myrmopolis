#include "hex_grid.hpp"

#include <cmath>
#include <stdexcept>

// Public

HexGrid::HexGrid(const unsigned int cols, const unsigned int rows, const float radius) : cols(cols), rows(rows), radius(radius) {
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

unsigned int HexGrid::getHeight() const noexcept {
    return height;
}
    
unsigned int HexGrid::getWidth() const noexcept {
    return width;
}

float HexGrid::getCellsRadius() const noexcept {
    return radius;
}

std::vector<HexCell> HexGrid::getHexCells() const noexcept {
    return cells;
}

sf::Vector2f HexGrid::getCellCenter(const sf::Vector2u &coords) const {
    return cells_center.at(coords);
}

//Private

void HexGrid::computeCells() noexcept {
    cells.clear();

    for (unsigned int col = 0; col < cols; ++col) {
        for (unsigned int row = 0; row < rows; ++row) {
            const auto x = static_cast<float>(
                static_cast<float>(col)*radius*std::sqrt(3)
                + (row % 2 == 0 ? 0 : radius*sqrt(3)/2) - radius*(1-std::sqrt(3)/2));
            const auto y = static_cast<float>(row)*radius*1.5f;

            HexCell cell{.px = {x, y}, .coords = {col, row}};
            cells.push_back(cell);

            const float center_x = x + radius;
            const float center_y = y + radius;
            cells_center.insert({{col, row}, {center_x, center_y}});
        }
    }

    width = static_cast<unsigned int>(
            (static_cast<float>(cols) + 0.5f)*radius*std::sqrt(3)
        );
    height = static_cast<unsigned int>(
            radius*(static_cast<float>(rows) + (static_cast<float>(rows)+1)/2)
        );
}