
#include "core/registry.h"

catos::Registry* registry = nullptr;



catos::Registry &catos::Registry::get() {
    return *registry;
}

void catos::Registry::init() {
    if (registry == nullptr)
        registry = this;
}

void catos::Registry::clean_up() {
    for (auto pair : _register) {
        pair.second.destroy();
    }
}
