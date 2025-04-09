
#include "core/registry.h"

Registry* registry = nullptr;



Registry &Registry::get() {
    return *registry;
}

void Registry::init() {
    if (registry == nullptr)
        registry = this;
}

void Registry::clean_up() {
    for (auto pair : _register) {
        pair.second.destroy();
    }
}
