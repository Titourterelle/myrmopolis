#pragma once

#include <memory>

class Observer
{
    public:
        explicit Observer();
        virtual ~Observer();

        virtual void observe() noexcept = 0;

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
};