#include "settings.hpp"
#include "simulation.hpp"

#include "environment/board.hpp"

#include <memory>
#include <stdexcept>
#include <vector>

using namespace myrmo;

struct Simulation::Impl
{
    const SimulationSettings simulation_settings;
    std::vector<std::unique_ptr<Board>> boards;
    Board* current_board = nullptr;
    const int max_round = 50;
    int current_round = 0;
    bool is_over = false;

    void step() noexcept;
    void initBoards() noexcept;

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


void Simulation::nextStep()
{
    if(!isOver())
    {
        impl_->step();
    }
    else
    {
        throw std::runtime_error("The simulation is over, can't simulate the next step");
    }
}

bool Simulation::isOver() const noexcept
{
    return (impl_->is_over);
}

void Simulation::Impl::step() noexcept
{
    static int index_board = 0;
    
    if(current_round >= max_round)
    {
        if(current_board != boards.back().get())
        {
            current_board = boards.at(++index_board).get();
            current_round = 0;
        }
        else
        {
            is_over = true;
        }
    }

    current_board->step();
    ++current_round;
}

void Simulation::Impl::initBoards() noexcept
{
    for(auto i = 0; i < simulation_settings.number_of_boards; ++i)
    {
        boards.push_back(std::make_unique<Board>(simulation_settings.board));
    }

    current_board = boards.at(0).get();
}
