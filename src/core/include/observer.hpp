#pragma once

#include "snapshot.hpp"

#include <memory>

namespace myrmo {

class Observer {
    public:
        explicit Observer();
        virtual ~Observer();

        virtual void observe(const snapshot::Snapshot snapshot) noexcept = 0;

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
};

}