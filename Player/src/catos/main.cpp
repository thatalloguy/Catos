// engine includes
#pragma once

#include <core/registry.h>
#include "io/serializer.h"
#include "stl/string.h"
#include "stl/rawvector.h"

struct Foo {
    catos::string a = "hello";
    int b = 4;
};

class Personality {
public:

    float weight = 0.5f;
    catos::string type = "happy";
};

struct Person {
    catos::string name = "Robert";
    int age = 20;
    Personality personality;

    catos::vector<Foo> list{Foo{}, Foo{}, Foo{}};
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

    registry.register_class<Foo>("Foo")
            .property("a", &Foo::a, "...")
            .property("b", &Foo::b, "...");

    registry.register_class<Person>("Person")
            .property("name", &Person::name, "...")
            .property("age", &Person::age, "...")
            .property("personality", &Person::personality, "...")
            .property("list", &Person::list, "...");



    Serializer serializer{};

    serializer.serializeInstances(instances);


    registry.clean_up();

    return 0;
}

