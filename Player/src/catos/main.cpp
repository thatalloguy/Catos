// engine includes
#pragma once
#include <core/registry.h>
#include "spdlog/spdlog.h"
#include "io/serializer.h"
#include "stl/string.h"

#include <ryml.hpp>

struct Person {
    catos::string name = "Robert";
    int age = 20;
};


//todo:
/// - custom types
/// - hashmaps
/// - vectors


int main() {
    vector<Object> instances;

    Person robert;

    instances.push_back({"Person", &robert});
    Registry registry{};

    registry.init();

    registry.register_class<Person>("Person")
            .property("name", &Person::name, "...")
            .property("age", &Person::age, "...");


    Serializer serializer{};

    serializer.serializeInstances(instances);




    return 0;
}

