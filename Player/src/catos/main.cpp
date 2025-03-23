// engine includes
#pragma once
#include <core/registry.h>
#include "spdlog/spdlog.h"
#include "io/serializer.h"

#include <ryml.hpp>



struct BaseNode {
public:
    int baseNodeID = 0;
};

struct Foo {
    float i = 0;
    double z = 2.0;
};


struct DummyNode: public BaseNode {
public:
    float data = 2.3f;

    catos::vector<Foo> vector{};

};


//todo:
/// - Better way to convert an object to a string.


int main() {
    vector<Object> instances;

    DummyNode foo{};

    foo.vector.push_back(Foo{2, 3});
    foo.vector.push_back(Foo{2, 5});
    foo.vector.push_back(Foo{2, 6});

    instances.push_back({"DummyNode", &foo});

    Registry registry{};

    registry.init();

    registry.register_class<BaseNode>("BaseNode")
            .property("baseNodeId", &BaseNode::baseNodeID, "...");


    registry.register_class<Foo>("Foo")
            .property("i", &Foo::i, "...")
            .property("z", &Foo::z, "...");

    auto info = registry.register_class<DummyNode>("DummyNode")
            .inherits("BaseNode")
            .property("data", &DummyNode::data, "...")
            .property("vector", &DummyNode::vector, "...");


    std::string out_yaml;

    Serializer serializer{};

    serializer.serializeInstances(instances, out_yaml);

    FILE* file = fopen("../../../test.yaml", "w");

    auto tree = ryml::parse_in_arena(out_yaml.c_str());

    ryml::emit_yaml(tree, tree.root_id(), file);

    fclose(file);


}

