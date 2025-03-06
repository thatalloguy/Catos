// engine includes
#pragma once
#include <core/registry.h>
#include "spdlog/spdlog.h"

#include <ryml.hpp>



struct BaseNode {
    int baseNodeID = 0;
};


struct DummyNode: public BaseNode {
    float data = 2.3f;

    catos::vector<float> vector{};
};

struct Object {
    std::string name;
    void* data;
};

//todo use names or something instead of hashes of classes
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
        auto& instance_property = registry.get_type(property->get_type_hash());

        out += "instance: ";
        out += instance_property.name + "\n";

        Object instance_object{
                .name = instance_property.name,
                .data = property->get_value(object.data)
        };

        for (auto properties: instance_property.properties) {
            //out += " ";
            write_property_to_string(properties.second, registry, instance_object, out);
        }

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
                out += "UNKNOWN\n";
                break;
        }


        out += "\n";
    }



}

int main() {

    vector<Object> instances;

    DummyNode foo{};


    instances.push_back({"DummyNode", &foo});

    Registry registry{};

    registry.init();

    registry.register_class<BaseNode>("BaseNode")
            .property("baseNodeId", &BaseNode::baseNodeID, "...");

    registry.register_class<DummyNode>("DummyNode")
            .inherits("BaseNode")
            .property("data", &DummyNode::data, "...")
            .property("vector", &DummyNode::vector, "...");

    std::string out_yaml;


    for (auto object: instances) {

        TypeInfo type = registry.get_type(object.name);

        out_yaml += "- class: ";
        out_yaml += type.name;
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

