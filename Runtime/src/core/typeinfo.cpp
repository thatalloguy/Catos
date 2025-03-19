//
// Created by allos on 3/19/2025.
//

#include "typeinfo.h"
#include "registry.h"


catos::TypeInfo &catos::TypeInfo::inherits(const std::string &class_name) {
    auto reg =  Registry::get();
    auto p = reg.get_type(class_name);

    for (auto prop : p.properties) {
        properties.insert(prop);
    }

    return *this;
}
