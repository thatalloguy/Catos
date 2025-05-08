// engine includes
#pragma once

#include <core/registry.h>
#include <core/constructor.h>
#include <io/serializer.h>
#include "stl/rawvector.h"





class Foo {
public:


    int t = -2;

};

class Personality {
public:

    Foo test = Foo{5};
    float weight = 0.5f;
//    Foo type{2};
    catos::vector<Foo> type;

    void hello() {
        spdlog::info("HEllo world");
    }
};


//todo:
/// - hashmaps
/// - vectors


int main() {


    catos::vector<catos::Object> instances;

    Personality robert{
        .type = {Foo{1}, Foo{2}, Foo{3}}
    };

    Foo robert2{
            .t = 64
    };

    instances.push_back({"Personality", &robert});
    instances.push_back({"Foo", &robert2});
    catos::Registry registry{};

    registry.init();

    registry.register_class<Foo>("Foo")
            .property("t", &Foo::t, "...");

    auto type_info = registry.register_class<Personality>("Personality")
            .property("weight", &Personality::weight, "...")
            .property("test", &Personality::test, "...")
            .property("type", &Personality::type, "...")
            .method("hello", &Personality::hello, "...");


    spdlog::info("BEFORE {}", robert.test.t);
    auto prop_test = type_info.get_property("test");
    auto prop_t = registry.get_type(prop_test->get_type_hash()).get_property("t");
    prop_t->set_value(prop_test->get_value(&robert), 6);


    spdlog::info("AFTER {}", robert.test.t);



    catos::Serializer serializer{};

    serializer.serializeInstances(instances);

    catos::vector<catos::Instance*> instances_in;

    serializer.deserializeInstances("../../../test.yaml", catos::Mode::YAML, instances_in);

    for (auto instance: instances_in) {

        spdlog::info("INSTANCE: {}", instance->get_name().c_str());

        if (instance->hash() == typeid(Personality).hash_code()) {
            Personality* personality = instance_cast<Personality>(instance);

            spdlog::info("weight: {}", personality->weight);
            spdlog::info("foo.t: {}", personality->test.t);

            for (auto v : personality->type) {
                spdlog::info("FOO: {}", v.t);
            }

            delete personality;
        } else {
            Foo* foo = instance_cast<Foo>(instance);

            spdlog::info("foo.t: {}", foo->t);


            delete foo;
        }

    }



    registry.clean_up();
    return 0;
}

