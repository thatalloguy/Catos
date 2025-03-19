
#include "core/registry.h"

Registry* registry = nullptr;



Registry &Registry::get() {
    return *registry;
}

void Registry::init() {
    if (registry == nullptr)
        registry = this;
}
