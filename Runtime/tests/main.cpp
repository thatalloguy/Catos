#pragma once
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

#include "core/type_utils.h"
#include <TINYSTL/string.h>

#include "core/registry.h"
#include "core/application.h"
#include "scripting/scriptingEngine.h"
#include "world/world.h"
#include "spdlog/spdlog.h"


struct Foo {
    float data = 2;

    float get_data() {
        return data;
    }
};

struct TransformComponent {
    float x, y, z;
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


    TEST_CASE("ScriptingEngine::Init") {

        ScriptingEngine scriptingEngine;

        scriptingEngine.init();


        scriptingEngine.clean_up();
    }

    TEST_CASE("ECS::componentId") {

        spdlog::info("Unique id: {}", catos::Component::get_id<TransformComponent>());

       CHECK(catos::Component::get_id<TransformComponent>() != catos::Component::get_id<Foo>());

    }

    TEST_CASE("ECS::Entity_creation") {

        World world;

        EntityId e1 = world.new_entity();
        EntityId e2 = world.new_entity();

        CHECK(e1 != e2);
    }

    TEST_CASE("ECS::Entity_Components") {

        World world;

        EntityId e1 = world.new_entity();

        world.assign<TransformComponent>(e1);

        CHECK(world.has_component<TransformComponent>(e1));
    }



}


int main(int argc, char** argv) {

    doctest::Context context;
    context.applyCommandLine(argc, argv);
    context.setOption("no-breaks", true);

    int res = context.run();


    return res;
}

