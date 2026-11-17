#include "progress_bar.hpp"

#include <iomanip>
#include <iostream>
#include <stdexcept>

ProgressBar::ProgressBar(const unsigned int total, const unsigned int bar_width) :
    total_(total),
    bar_width_(bar_width)
{
    if (total == 0) {
        throw std::invalid_argument("Maximum value of the progress bar cannot be 0");
    }
    if (bar_width == 0) {
        throw std::invalid_argument("The bar width cannot be 0");
    }
    update(0);
}

void ProgressBar::update(const unsigned int current) const {
    if (current > total_) {
        throw std::invalid_argument("The current value cannot exceed the maximum value");
    }


    const float ratio = static_cast<float>(current) / static_cast<float>(total_);
    const auto filled = static_cast<unsigned int>(ratio * static_cast<float>(bar_width_));

    std::cout << "\r[";
    for (unsigned int i = 0; i < bar_width_; ++i) {
        std::cout << (i < filled ? '#' : '-');
    }
    std::cout << "] " << std::setw(3) << static_cast<int>(ratio * 100) << "% " << "(" << current << "/" << total_ << ")" << std::flush;

    if (current >= total_) {
        std::cout << '\n';
    }
}