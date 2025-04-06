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
/// - Better way to convert an object to a string.


int main() {
    vector<Object> instances;

    Person robert;

    instances.push_back({"Person", &robert});
    Registry registry{};

    registry.init();

    registry.register_class<Person>("Person")
            .property("name", &Person::name, "...")
            .property("age", &Person::age, "...");


    std::string out_yaml;

    Serializer serializer{};

    serializer.serializeInstances(instances, out_yaml);




    return 0;
}

