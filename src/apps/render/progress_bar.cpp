#include "progress_bar.hpp"

#include <iostream>
#include <iomanip>
#include <stdexcept>

ProgressBar::ProgressBar(unsigned int total, unsigned int bar_width) :
    total(total),
    bar_width(bar_width)
{
    if (total == 0) {
        throw std::invalid_argument("Maximun value of the progress bar cannot be 0");
    }
    if (bar_width == 0) {
        throw std::invalid_argument("The bar width cannot be 0");
    }
    update(0);
}

void ProgressBar::update(unsigned int current) {
    if (current > total) {
        throw std::invalid_argument("The current value cannot exceed the maximun value");
    }


    float ratio = static_cast<float>(current) / total;
    unsigned int filled = static_cast<unsigned int>(ratio * bar_width);

    std::cout << "\r[";
    for (unsigned int i = 0; i < bar_width; ++i) {
        std::cout << (i < filled ? '#' : '-');
    }
    std::cout << "] " << std::setw(3) << static_cast<int>(ratio * 100) << "% " << "(" << current << "/" << total << ")" << std::flush;

    if (current >= total) {
        std::cout << '\n';
    }
}