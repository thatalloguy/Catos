//
// Created by allos on 3/19/2025.
//

#include "typeinfo.h"
#include "registry.h"


catos::TypeInfo &catos::TypeInfo::inherits(const std::string &class_name) {
    Registry& reg =  Registry::get();

    if (!reg.is_type_registered(class_name)) {
        spdlog::error(
            "Could not inherit {} from {} , because the class isnt registered/found",
            this->name.c_str(),
            class_name.c_str()
        );

        return *this;
    }
    TypeInfo& p = reg.get_type(class_name);

    for (auto& prop : p.properties) {
        properties.insert(prop);
    }

    for (auto& meths : p.methods) {
        methods.insert(meths);
    }

    p.children.push_back(this);
    spdlog::info("INHERITED: {}", p.children.length());


    return *this;
}
