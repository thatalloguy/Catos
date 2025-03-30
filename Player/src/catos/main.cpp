// engine includes
#pragma once
#include <core/registry.h>
#include "spdlog/spdlog.h"
#include "io/serializer.h"

#include <ryml.hpp>



struct Foo {
    float z = 0.2f;
};

struct Moo {
    float a = 0.1f;
    Foo* foo = nullptr;
};


//todo:
/// - Better way to convert an object to a string.


int main() {
    vector<Object> instances;

    Foo foo{};

    Moo moo{
        0.1f,
        &foo
    };

    Moo moo2{
            1.2f,
            &foo
    };


    instances.push_back({"Moo", &moo});
    instances.push_back({"Moo", &moo2});

    Registry registry{};

    registry.init();

    registry.register_class<Foo>("Foo")
            .property("z", &Foo::z, "...");

    registry.register_class<Moo>("Moo")
            .property("a", &Moo::a, "...")
            .property("foo", &Moo::foo, "...");

    std::string out_yaml;

    Serializer serializer{};

    serializer.serializeInstances(instances, out_yaml);

    FILE* file = fopen("../../../test.yaml", "w");

    auto tree = ryml::parse_in_arena(out_yaml.c_str());

    ryml::emit_yaml(tree, tree.root_id(), file);

    fclose(file);

}

