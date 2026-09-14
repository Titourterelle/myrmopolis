#pragma once

#include "render_utils.hpp"

#include <map>
#include <vector>

#include <SFML/System/Vector2.hpp>

struct HexCell {
    sf::Vector2f px;
    sf::Vector2u coords;
};

class HexGrid {
    public:
        explicit HexGrid(unsigned int cols, unsigned int rows, float radius);

        [[nodiscard]] unsigned int getHeight() const noexcept;
        [[nodiscard]] unsigned int getWidth() const noexcept;
        [[nodiscard]] float getCellsRadius() const noexcept;
        [[nodiscard]] std::vector<HexCell> getHexCells() const noexcept;
        [[nodiscard]] sf::Vector2f getCellCenter(const sf::Vector2u &coords) const;

    private:
        void computeCells() noexcept;

        unsigned int height = 0;
        unsigned int width = 0;

        const unsigned int cols;
        const unsigned int rows;
        const float radius;
        std::vector<HexCell> cells;
        std::map<sf::Vector2u, sf::Vector2f, Vector2uCompare> cells_center;
};