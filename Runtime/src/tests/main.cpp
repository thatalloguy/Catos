#pragma once
#define DOCTEST_CONFIG_IMPLEMENT
#include "../doctest/doctest/doctest.h"

#include "core/type_utils.h"

#include "core/registry.h"
#include "core/application.h"
#include "world/world.h"
#include "spdlog/spdlog.h"
#include "stl/vector.h"
#include "stl/string.h"


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

    TEST_CASE("REGISTRY::GET_TYPE_NAME") {
        CHECK((std::string) "int" == catos::type_utils::get_type_name<int>());
    }

    TEST_CASE("REGISTRY::FIELDS") {

        Registry registry;

        Foo foo;


        foo.data = 4;

        auto& field = registry.register_class<Foo>().property("data", &Foo::data, "dummy");


        Property* test = field.get_property("data");

        auto* testFloat = (float*) (test->get_value(&foo));


        CHECK(foo.data == *testFloat);
    }



    TEST_CASE("REGISTRY::METHODS") {

        Registry registry;

        Foo foo;


        foo.data = 4;

        auto& field = registry.register_class<Foo>()
                .property("data", &Foo::data, "dummy variable")
                .method("get_data", &Foo::get_data, "Returns the data of Foo");



        Property* test = field.get_property("data");
        Method* meth = field.get_method("get_data");


        auto* testFloat = (float*) (test->get_value(&foo));


        CHECK(*testFloat == meth->invoke_function<float>(&foo));

    }


    TEST_CASE("Application::INSTANCES") {

        AppCreationInfo appinfo{};


        App app{&appinfo};


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

        for (int obj : test) {
            spdlog::info("Element = {}", obj);
        }

    }

}


int main(int argc, char** argv) {

    doctest::Context context;
    context.applyCommandLine(argc, argv);
    context.setOption("no-breaks", true);

    int res = context.run();


    return res;
}

