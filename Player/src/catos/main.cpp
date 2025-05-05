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


    int t = 0;

};

class Personality {
public:


    float weight = 0.5f;
//    Foo type{2};
    catos::vector<float> type;

    void hello() {
        spdlog::info("HEllo world");
    }
};



//todo:
/// - hashmaps
/// - vectors


int main() {
    catos::vector<catos::Object> instances;

    Personality robert{
        .type = {0.1f, 0.2f, 0.3f}
    };

    instances.push_back({"Personality", &robert});
    catos::Registry registry{};

    registry.init();

    registry.register_class<Foo>("Foo")
            .property("t", &Foo::t, "...");

    auto type_info = registry.register_class<Personality>("Personality")
            .property("weight", &Personality::weight, "...")
            .property("type", &Personality::type, "...")
            .method("hello", &Personality::hello, "...");

    catos::Serializer serializer{};

    serializer.serializeInstances(instances);

    catos::vector<catos::Instance*> instances_in;

    serializer.deserializeInstances("../../../test.yaml", catos::Mode::YAML, instances_in);

    spdlog::info("INSTANCE: {}", instances_in[0]->get_name().c_str());

    Personality* personality = instance_cast<Personality>(instances_in[0]);

    spdlog::info("weight: {}", personality->weight);
//    spdlog::info("foo.t: {}", personality->type.t);

    for (auto v : personality->type) {
        spdlog::info("FOO: {}", v);
    }

    delete personality;



    registry.clean_up();


    return 0;
}

