#include "hex_grid.hpp"

#include <cmath>
#include <stdexcept>

// Public

HexGrid::HexGrid(const unsigned int cols, const unsigned int rows, const float radius) : cols_(cols), rows_(rows), radius_(radius) {
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
    return height_;
}
    
unsigned int HexGrid::getWidth() const noexcept {
    return width_;
}

float HexGrid::getCellsRadius() const noexcept {
    return radius_;
}

std::vector<HexCell> HexGrid::getHexCells() const noexcept {
    return cells_;
}

sf::Vector2f HexGrid::getCellCenter(const sf::Vector2u& coords) const {
    return cells_center_.at(coords);
}

//Private

void HexGrid::computeCells() noexcept {
    cells_.clear();

    for (unsigned int col = 0; col < cols_; ++col) {
        for (unsigned int row = 0; row < rows_; ++row) {
            const auto x = static_cast<float>(
                static_cast<float>(col)*radius_*std::sqrt(3)
                + (row % 2 == 0 ? 0 : radius_*sqrt(3)/2) - radius_*(1-std::sqrt(3)/2));
            const auto y = static_cast<float>(row)*radius_*1.5f;

            HexCell cell{.px = {x, y}, .coords = {col, row}};
            cells_.push_back(cell);

            const float center_x = x + radius_;
            const float center_y = y + radius_;
            cells_center_.insert({{col, row}, {center_x, center_y}});
        }
    }

    width_ = static_cast<unsigned int>(
            (static_cast<float>(cols_) + 0.5f)*radius_*std::sqrt(3)
        );
    height_ = static_cast<unsigned int>(
            radius_*(static_cast<float>(rows_) + (static_cast<float>(rows_)+1)/2)
        );
}