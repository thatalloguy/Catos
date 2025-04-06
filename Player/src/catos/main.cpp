// engine includes
#pragma once

#include <core/registry.h>
#include "io/serializer.h"
#include "stl/string.h"

struct Personality {
    float weight = 0.5f;
    catos::string type = "happy";
};

struct Person {
    catos::string name = "Robert";
    int age = 20;
    Personality personality;
};


//todo:
/// - hashmaps
/// - vectors
/// - pointers


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
            .property("personality", &Person::personality, "...");


    Serializer serializer{};

    serializer.serializeInstances(instances);




    return 0;
}

