// engine includes
#pragma once
#include <core/registry.h>
#include "spdlog/spdlog.h"
#include "io/serializer.h"

#include <ryml.hpp>



struct BaseNode {
    int baseNodeID = 0;
};


struct DummyNode: public BaseNode {
    float data = 2.3f;

    catos::vector<float> vector{};
};


//todo use names or something instead of hashes of classes


int main() {

 /*   vector<Object> instances;

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

    Serializer serializer{};

    serializer.serializeInstances(instances, out_yaml);

//
    FILE* file = fopen("../../../test.yaml", "w");

    ryml::csubstr yml = R"(
                - a: "hello"
    )";

    auto tree = ryml::parse_in_arena(out_yaml.c_str());

    ryml::emit_yaml(tree, tree.root_id(), file);

    fclose(file);*/


    hashmap<int, float> map;

    map.put(0, 2.0f);
    map.put(4, 2.0f);
    map.put(2, 2.6f);
    map.put(6, 2.1f);
    map.put(1, 2.2f);

    for (auto pair: map.all()) {
        spdlog::info("pair {} {}", pair.first, pair.second);
    }
}

