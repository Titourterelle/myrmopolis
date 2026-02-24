#pragma once

class Simulation
{
    public:
        explicit Simulation() noexcept;
        bool isOver() const noexcept;

    private:
        void nextRound();

        const int maxRound = 50;
        int currentRound = 0;
};