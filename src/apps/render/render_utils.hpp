#pragma once

#include <SFML/System/Vector2.hpp>
#include <stdexcept>
#include <string>

struct Vector2uCompare {
    bool operator()(const sf::Vector2u& a, const sf::Vector2u& b) const {
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

enum class RenderQuality {
    Low,
    Medium,
    High
};

struct RenderSettings {
    unsigned int fps;
    unsigned int frames_per_step;

    RenderQuality quality;

    std::string output_dir;
};