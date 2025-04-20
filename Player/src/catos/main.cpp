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
    vector<Object> instances;

    Personality robert;

    instances.push_back({"Personality", &robert});
    Registry registry{};

    registry.init();

    auto type_info = registry.register_class<Personality>("Personality")
            .property("weight", &Personality::weight, "...")
            .property("type", &Personality::type, "...")
            .method("hello", &Personality::hello, "...");


    auto property = type_info.get_property("weight");

    spdlog::info("Current val: {}", *(float*) property->get_value(&robert));

    property->set_value(&robert, 1.6f);

    spdlog::info("Current val: {}", *(float*) property->get_value(&robert));


    type_info.get_method("hello")->invoke_function(&robert);
//
//
//    Serializer serializer{};
//
//    serializer.serializeInstances(instances);
//    serializer.deserializeInstances("../../../test.yaml");
//


    catos::Constructor constructor;
    constructor.initialize<Foo, int>("Foo", typeid(Foo).hash_code());

    Foo* foo = instance_cast<Foo>(constructor.construct(12));

    spdlog::info("foo {}", foo->t);

    delete foo;

    registry.clean_up();


    return 0;
}

