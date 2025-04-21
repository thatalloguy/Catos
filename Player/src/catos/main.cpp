// engine includes
#pragma once

#include <core/registry.h>
#include <core/constructor.h>
#include "io/serializer.h"
#include "stl/string.h"
#include "stl/rawvector.h"

#include <ryml.hpp>

class Foo {
public:
    Foo(int d) {
        spdlog::info("HELLO {}", d);
        t = d;
    }

    int t = 0;

};

class Personality {
public:


    float weight = 0.5f;
    catos::string type = "happy";

    void hello() {
        spdlog::info("HEllo world");
    }
};



//todo:
/// - hashmaps
/// - vectors


int main() {
    catos::vector<catos::Object> instances;

    Personality robert;

    instances.push_back({"Personality", &robert});
    catos::Registry registry{};

    registry.init();

    auto type_info = registry.register_class<Personality>("Personality")
            .property("weight", &Personality::weight, "...")
            .property("type", &Personality::type, "...")
            .method("hello", &Personality::hello, "...");

    catos::Serializer serializer{};

    serializer.serializeInstances(instances);
    serializer.deserializeInstances("../../../test.yaml");



    registry.clean_up();


    return 0;
}

