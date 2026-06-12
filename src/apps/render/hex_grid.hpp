#pragma once

#include "render_utils.hpp"

#include <map>
#include <vector>

#include <SFML/System/Vector2.hpp>

struct HexCell {
    sf::Vector2f px;
    sf::Vector2i coords;
};

class HexGrid {
    public:
        explicit HexGrid(int cols, int rows, float radius);

        int getHeight() const noexcept;
        int getWidth() const noexcept;
        float getCellsRadius() const noexcept;
        const std::vector<HexCell> getHexCells() const noexcept;
        const sf::Vector2f getCellCenter(const sf::Vector2i &coords) const;

    private:
        void computeCells() noexcept;

        int height = 0;
        int width = 0;

        const unsigned int cols;
        const unsigned int rows;
        const float radius;
        std::vector<HexCell> cells;
        std::map<sf::Vector2i, sf::Vector2f, Vector2iCompare> cells_center;
};