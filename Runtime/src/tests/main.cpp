#pragma once
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>



#include "core/registry.h"
#include "core/application.h"
#include "objects/node.h"
#include "stl/vector.h"
#include "stl/hashmap.h"


struct Foo {
    float data = 2;

    float get_data() {
        return data;
    }
};

struct TransformComponent {
    float x, y, z;

    bool operator!=(TransformComponent& b) {
        return true;
    }
};

struct ComponentTest {
    float d;
};

namespace catos::tests {


    TEST_CASE("REGISTRY::FIELDS") {

        Registry registry;

        Foo foo;


        foo.data = 4;

        auto& field = registry.register_class<Foo>("Foo").property("data", &Foo::data, "dummy");


        Property* test = field.get_property("data");

        auto* testFloat = (float*) (test->get_value(&foo));


        CHECK(foo.data == *testFloat);
    }



    TEST_CASE("REGISTRY::METHODS") {

        Registry registry;

        Foo foo;


        foo.data = 4;

        auto& field = registry.register_class<Foo>("Foo")
                .property("data", &Foo::data, "dummy variable")
                .method("get_data", &Foo::get_data, "Returns the data of Foo");



        Property* test = field.get_property("data");
        Method* meth = field.get_method("get_data");


        auto* testFloat = (float*) (test->get_value(&foo));


        CHECK(*testFloat == meth->invoke_function<float>(&foo));

    }


    TEST_CASE("Application::INSTANCES") {


        App app{};


        CHECK(app.is_alive());

        Foo foo;

        foo.data = 3.4f;

        app.bind<Foo>(&foo);


        auto test = app.get<Foo>();

        CHECK(foo.data == test->data);

    }


    TEST_CASE("STL::VECTORS") {


        catos::vector<int> test;

        test.reserve(7);

        for (int i=0; i < 7; i++)
            test.push_back(i);

        int i = 0;
        for (int obj : test) {
            CHECK(obj == test[i]);
            i++;
        }

    }

    TEST_CASE("STL::HASHMAPS") {

        catos::hashmap<int, int> map;

        for (int i=0; i<100; i++) {
            map.put(i, i + 60);
        }

        CHECK(map.get(40) == 100);
    }

    TEST_CASE("NODES::CHILDREN") {

        catos::Node root{false};
        catos::Node parent{false};
        catos::Node child{false};

        root.initialize("root");

        parent.initialize("parent");
        parent.set_parent(&root);

        child.initialize("child");
        child.set_parent(&parent);

        spdlog::info("path: {} | {}", root.name.c_str(), root.path().c_str());
        spdlog::info("path: {} | {}", parent.name.c_str(), parent.path().c_str());
        spdlog::info("path: {} | {}", child.name.c_str(), child.path().c_str());

        child.name = "child2";

        spdlog::info("---------------------");

        spdlog::info("path: {} | {}", root.name.c_str(), root.path().c_str());
        spdlog::info("path: {} | {}", parent.name.c_str(), parent.path().c_str());
        spdlog::info("path: {} | {}", child.name.c_str(), child.path().c_str());

        spdlog::info("---------------------");

        spdlog::info("parent has child2: {}", parent.has_child("child2"));
        spdlog::info("parent has child3: {}", parent.has_child("child3"));
        spdlog::info("parent has child: {}", parent.has_child("child"));

        spdlog::info("---------------------");

        catos::Node* found_child = parent.find_node("child2");
        spdlog::info("found child via find_node: {}", found_child != nullptr);

        found_child = parent.get_child("child2");
        spdlog::info("found child via get_child: {}", found_child != nullptr);

        found_child = root.find_node("child2");
        spdlog::info("found child via the root: {}", found_child != nullptr);
    }

}


int main(int argc, char** argv) {

    doctest::Context context;
    context.applyCommandLine(argc, argv);
    context.setOption("no-breaks", true);

    int res = context.run();


    return res;
}

