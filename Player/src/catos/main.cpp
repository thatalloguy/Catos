// engine includes
#pragma once

#include <core/registry.h>
#include "io/serializer.h"
#include "stl/string.h"
#include "stl/rawvector.h"

#include <ryml.hpp>

class Personality {
public:

    float weight = 0.5f;
    catos::string type = "happy";
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
            .property("type", &Personality::type, "...");


    auto property = type_info.get_property("weight");

    spdlog::info("Current val: {}", *(float*) property->get_value(&robert));

    property->set_value(&robert, 1.6f);

    spdlog::info("Current val: {}", *(float*) property->get_value(&robert));


//
//
//    Serializer serializer{};
//
//    serializer.serializeInstances(instances);
//    serializer.deserializeInstances("../../../test.yaml");
//

    registry.clean_up();


    return 0;
}

