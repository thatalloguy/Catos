// engine includes
#pragma once
#include <core/registry.h>
#include "spdlog/spdlog.h"

#include <ryml.hpp>

template<int T>
struct RawString {
    char str[T];
};

struct SubFoo {
    const char* msg = "Hello";
    double b = 1;
};



struct Foo {
    float a = 0;
    catos::string msg = "Hello";
};

struct Object {
    size_t  hash;
    void* data;
};

const size_t float_hash = 12638226781420530164;
const size_t int_hash = 12638232278978672507;
const size_t uint_hash = 12638231179467044040;
const size_t double_hash = 12638230079955414429;
const size_t string_hash = 1292088526669925081;

void write_property_to_string(Property* property, Registry& registry, Object& object, std::string& out) {

    out += "  ";
    out += property->get_name();
    out += ": ";

    if (registry.is_type_registered(property->get_type_hash())) {
        out += "instance\n";
        // Write that object info to the file.
    } else {

        switch (property->get_type_hash()) {

            case float_hash:
                out += std::to_string(*static_cast<float*>(property->get_value(object.data)));
                break;

            case int_hash:
                out += std::to_string(*static_cast<int*>(property->get_value(object.data)));
                break;

            case uint_hash:
                out += std::to_string(*static_cast<unsigned int*>(property->get_value(object.data)));
                break;

            case double_hash:
                out += std::to_string(*static_cast<double*>(property->get_value(object.data)));
                break;

            case string_hash:
                out += R"(")";
                out += static_cast<catos::string*>(property->get_value(object.data))->c_str();
                out += R"(")";
                break;

            default:
                spdlog::warn("Unknown Propertype HASH of name: {}", property->get_type_name());
                break;
        }


        out += "\n";
    }



}

int main() {

    vector<Object> instances;

    Foo foo{2};

    instances.push_back({type_utils::get_type_hash<Foo>(), &foo});

    Registry registry{};

    registry.register_class<Foo>()
            .property("a", &Foo::a, "a variable")
            .property("msg", &Foo::msg, "a variable");

    std::string out_yaml;


    for (auto object: instances) {

        TypeInfo type = registry.get_type(object.hash);

        out_yaml += "- class: ";
        out_yaml += std::to_string(type.type_hash);
        out_yaml += "\n";

        for (auto property_entry : type.properties) {

            auto property = property_entry.second;

            write_property_to_string(property, registry, object, out_yaml);

        }

    }
//
    FILE* file = fopen("../../../test.yaml", "w");

    ryml::csubstr yml = R"(
                - a: "hello"
    )";

    auto tree = ryml::parse_in_arena(out_yaml.c_str());

    ryml::emit_yaml(tree, tree.root_id(), file);

    fclose(file);

}

