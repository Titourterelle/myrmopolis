#pragma once

#include "snapshot.hpp"

namespace myrmo {

class Observer {
    public:
        explicit Observer() = default;
        virtual ~Observer() = default;

        virtual void observe(const snapshot::Snapshot &snapshot) = 0;
};

}