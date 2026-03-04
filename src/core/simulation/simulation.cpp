#include "settings.hpp"
#include "simulation.hpp"

#include "environment/board.hpp"

#include <memory>
#include <stdexcept>
#include <vector>

struct Simulation::Impl
{
    const SimulationSettings simulation_settings;
    std::vector<std::unique_ptr<Board>> boards;
    const int max_round = 50;
    int current_round = 0;

    void step() noexcept;
    void initBoards();

    Impl(SimulationSettings sim_settings) : simulation_settings(sim_settings) {}
};

Simulation::Simulation(const SimulationSettings &settings) : impl_(std::make_unique<Impl>(settings))
{
    if(impl_->simulation_settings.number_of_boards <= 0)
    {
        throw std::runtime_error("The number of boards can't be null or negative");
    }
    impl_->initBoards();
}

Simulation::~Simulation() = default;

bool Simulation::isOver() const noexcept
{
    return (impl_->current_round >= impl_->max_round);
}

void Simulation::run() noexcept
{
    while (!isOver())
    {
        impl_->step();
    }
}

void Simulation::Impl::step() noexcept
{
    for(const auto& board : boards)
    {
        board->step();
    }
    ++current_round;
}

void Simulation::Impl::initBoards()
{
    for(auto i = 0; i < simulation_settings.number_of_boards; ++i)
    {
        boards.push_back(std::make_unique<Board>(simulation_settings.board));
    }
}