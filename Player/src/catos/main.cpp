// engine includes
#pragma once
#include <core/registry.h>
#include "spdlog/spdlog.h"

#include <ryml.hpp>


struct Foo {
    int a = 0;
};

struct Object {
    size_t  hash;
    void* data;
};

int main() {

    vector<Object> instances;

    Foo foo{2};

    instances.push_back({type_utils::get_type_hash<Foo>(), &foo});

    Registry registry{};

    registry.register_class<Foo>()
            .property("a", &Foo::a, "a variable");

    std::string out_yaml;


    for (auto object: instances) {

        TypeInfo type = registry.get_type(object.hash);

        out_yaml += "- class: ";
        out_yaml += std::to_string(type.type_hash);
        out_yaml += "\n";

        for (auto property_entry : type.properties) {

            auto property = property_entry.second;

            out_yaml += "  ";
            out_yaml += property->get_name();
            out_yaml += ": ";
            out_yaml += std::to_string(*reinterpret_cast<int*>(property->get_value(object.data)));
            out_yaml += "\n";
        }

    }

    FILE* file = fopen("../../../test.yaml", "w");

    ryml::csubstr yml = R"(
                - a: "hello"
    )";

    auto tree = ryml::parse_in_arena(out_yaml.c_str());

    ryml::emit_yaml(tree, tree.root_id(), file);

    fclose(file);
}

