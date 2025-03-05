
#include "core/registry.h"

Registry* registry = nullptr;

TypeInfo &TypeInfo::inherits(const std::string &class_name) {
    auto reg =  Registry::get();
    auto p = reg.get_type(class_name);

    for (auto prop : p.properties) {
        properties.insert(prop);
    }

    return *this;
}



Registry &Registry::get() {
    return *registry;
}

void Registry::init() {
    registry = this;
}
