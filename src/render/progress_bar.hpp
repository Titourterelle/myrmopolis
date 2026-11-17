#pragma once

class ProgressBar {
    public:
        explicit ProgressBar(unsigned int total, unsigned int bar_width = 20);

        void update(unsigned int current) const;

    private:
        unsigned int total_;
        unsigned int bar_width_;
};