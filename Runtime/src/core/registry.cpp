
#include "core/registry.h"


catos::Registry &catos::Registry::get() {
    static Registry registry{};

    return registry;
}

void catos::Registry::clean_up() {
    for (auto pair : _register) {
        pair.second.destroy();
    }
}
