#include "simulation.hpp"
#include "observer.hpp"
#include "settings.hpp"
#include "snapshot.hpp"
#include "environment/board.hpp"

#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

namespace myrmo {
struct Simulation::Impl {
    void step() noexcept;
    void giveSnapshotToObservers(const snapshot::Snapshot& snapshot) const noexcept;

    [[nodiscard]] snapshot::Snapshot takeSnapshot() const noexcept;

    void initBoards() noexcept;
    
    const SimulationSettings simulation_settings_;
    
    std::vector<std::unique_ptr<Board>> boards_;
    std::vector<Observer*> observers_;
    
    Board* current_board_ = nullptr;
    int index_board_ = 0;
    int current_round_ = 0;
    const int max_round_ = 10;
    bool is_over_ = false;

    explicit Impl(SimulationSettings sim_settings) : simulation_settings_(std::move(sim_settings)) {}
};

// Public

Simulation::Simulation(const SimulationSettings& settings) : impl_(std::make_unique<Impl>(settings)) {
    if (impl_->simulation_settings_.number_of_boards <= 0)
    {
        throw std::runtime_error("The number of boards can't be null or negative");
    }
    impl_->initBoards();
}

Simulation::~Simulation() = default;


void Simulation::run() const {
    impl_->giveSnapshotToObservers(impl_->takeSnapshot()); // First Snapshot of the first board (t = 0)

    while (!impl_->is_over_) {
        impl_->step();
        impl_->giveSnapshotToObservers(impl_->takeSnapshot());
    }
}

void Simulation::addObserver(Observer& observer) const noexcept {
    impl_->observers_.push_back(&observer);
}

// Private

void Simulation::Impl::step() noexcept
{
    current_board_->step();
    ++current_round_;

    if (current_round_ >= max_round_) {
        if (current_board_ != boards_.back().get()) {
            giveSnapshotToObservers(takeSnapshot()); // Last Snapshot before next board
            current_board_ = boards_.at(++index_board_).get();
            current_round_ = 0;
        }
        else {
            is_over_ = true;
        }
    }
}

void Simulation::Impl::giveSnapshotToObservers(const snapshot::Snapshot& snapshot) const noexcept {
    for (const auto observer : observers_) {
        observer->observe(snapshot);
    }
}

snapshot::Snapshot Simulation::Impl::takeSnapshot() const noexcept {
    snapshot::Snapshot snapshot = current_board_->createSnapshot();

    snapshot.board_id = index_board_;
    snapshot.step = current_round_;

    return snapshot;
}

void Simulation::Impl::initBoards() noexcept {
    for (auto i = 0; i < simulation_settings_.number_of_boards; ++i) {
        boards_.push_back(std::make_unique<Board>(simulation_settings_.board));
    }

    current_board_ = boards_.at(0).get();
}
}