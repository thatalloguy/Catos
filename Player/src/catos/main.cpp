// engine includes
#pragma once

#include <core/registry.h>
#include "io/serializer.h"
#include "stl/string.h"
#include "stl/rawvector.h"

struct Personality {
    float weight = 0.5f;
    catos::string type = "happy";
};

struct Person {
    catos::string name = "Robert";
    int age = 20;
    Personality personality;

    catos::vector<float> list{1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
};


//todo:
/// - hashmaps
/// - vectors


int main() {
    vector<Object> instances;

    Person robert;

    instances.push_back({"Person", &robert});
    Registry registry{};

    registry.init();

    registry.register_class<Personality>("Personality")
            .property("weight", &Personality::weight, "...")
            .property("type", &Personality::type, "...");

    registry.register_class<Person>("Person")
            .property("name", &Person::name, "...")
            .property("age", &Person::age, "...")
            .property("personality", &Person::personality, "...")
            .property("list", &Person::list, "...");


    Serializer serializer{};

    serializer.serializeInstances(instances);


    raw_vector rawVector{&robert.list};

    for (void* ptr : rawVector) {

        float val = *(float*) ptr;
        std::cout << "VAL:  " << val  << "\n";
    }


    return 0;
}

