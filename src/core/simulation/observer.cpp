#include "observer.hpp"

namespace myrmo {

struct Observer::Impl {
    Impl() {}
};

// Public

Observer::Observer() : impl_() {}
    
}