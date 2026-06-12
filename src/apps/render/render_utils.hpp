#pragma once

#include <SFML/System/Vector2.hpp>
#include <stdexcept>

struct Vector2iCompare {
    bool operator()(const sf::Vector2i& a, const sf::Vector2i& b) const {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    }
};

inline float easeInOut(float t) {
    if (0 > t || t > 1) {
        throw std::invalid_argument("The argument must be between 0 and 1");
    }
    return t < 0.5 ? 2*t*t : (4 - 2*t)*t - 1;
}