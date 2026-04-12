#include "simulation.hpp"
#include "settings.hpp"
#include "observer.hpp"
#include "snapshot.hpp"

#include "environment/board.hpp"

#include <memory>
#include <stdexcept>
#include <vector>

using namespace myrmo;

struct Simulation::Impl {
    void step() noexcept;
    const snapshot::Snapshot takeSnapshot() const noexcept;

    void initBoards() noexcept;
    
    const SimulationSettings simulation_settings;
    
    std::vector<std::unique_ptr<Board>> boards;
    std::vector<Observer*> observers;
    
    Board* current_board = nullptr;
    int current_round = 0;
    const int max_round = 50;
    bool is_over = false;
    
    Impl(SimulationSettings sim_settings) : simulation_settings(sim_settings) {}
};

// Public

Simulation::Simulation(const SimulationSettings &settings) : impl_(std::make_unique<Impl>(settings)) {
    if (impl_->simulation_settings.number_of_boards <= 0)
    {
        throw std::runtime_error("The number of boards can't be null or negative");
    }
    impl_->initBoards();
}

Simulation::~Simulation() = default;


void Simulation::run() {
    while (!impl_->is_over) {
        impl_->step();

        const snapshot::Snapshot snapshot = impl_->takeSnapshot();

        for (auto observer : impl_->observers) {
            observer->observe(snapshot);
        }
    }
}

void Simulation::addObserver(Observer &observer) noexcept {
    impl_->observers.push_back(&observer);
}

// Private

void Simulation::Impl::step() noexcept
{
    static int index_board = 0;
    
    if (current_round >= max_round) {
        if (current_board != boards.back().get()) {
            current_board = boards.at(++index_board).get();
            current_round = 0;
        }
        else {
            is_over = true;
        }
    }

    current_board->step();
    ++current_round;
}

const snapshot::Snapshot Simulation::Impl::takeSnapshot() const noexcept {
    return current_board->createSnapshot();
}

void Simulation::Impl::initBoards() noexcept {
    for (auto i = 0; i < simulation_settings.number_of_boards; ++i) {
        boards.push_back(std::make_unique<Board>(simulation_settings.board));
    }

    current_board = boards.at(0).get();
}
