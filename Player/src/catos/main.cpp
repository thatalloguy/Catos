// engine includes
#pragma once
#include <core/registry.h>
#include "spdlog/spdlog.h"


struct Foo {
    int a = 0;
};


int main() {

    Foo foo{};

    Registry registry{};

    registry.register_class<Foo>()
            .property("a", &Foo::a, "a variable");

    for (auto entry: registry.entries()) {

        TypeInfo type = entry.second;

        spdlog::info("Type Info for -> {}", type.name);

        spdlog::info("Registered properties: ");

        for (auto property_entry : type.properties) {
            spdlog::info("property.name -> {}", property_entry.second->get_name());
        }

    }
}

