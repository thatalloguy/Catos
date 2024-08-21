#pragma once
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

#include "core/type_utils.h"
#include <TINYSTL/string.h>

#include "core/registry.h"
#include "core/application.h"
#include "world/world.h"
#include "spdlog/spdlog.h"
#include "world/query.h"


struct Foo {
    float data = 2;

    float get_data() {
        return data;
    }
};

struct TransformComponent {
    float x, y, z;
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
        CHECK(!world.has_component<Foo>(e1));
        CHECK(!world.has_component<ComponentTest>(e1));

        spdlog::info("ID COMP: {}", Component::c_componentCounter);
    }

    TEST_CASE("ECS::Get_component") {

        World world;

        EntityId e1 = world.new_entity();

        world.assign<TransformComponent>(e1);

        CHECK(world.has_component<TransformComponent>(e1));


        world.get<TransformComponent>(e1)->x = 2;

        CHECK(world.get<TransformComponent>(e1)->x == 2);
    }

    TEST_CASE("ECS::Query") {


        World world;

        EntityId e1 = world.new_entity();
        EntityId e2 = world.new_entity();

        world.assign<TransformComponent>(e1);
        world.assign<TransformComponent>(e2);

        TransformComponent* tr1 = world.get<TransformComponent>(e1);

        TransformComponent* tr2 = world.get<TransformComponent>(e2);



        tr1->x = 1;
        tr1->y = 4;
        tr1->z = 3;

        tr2->x = 5;
        tr2->y = 7;
        tr2->z = 2;

        CHECK(world.has_component<TransformComponent>(e1));
        CHECK(world.has_component<TransformComponent>(e2));

        for (EntityId ent : catos::Query<TransformComponent>(world)) {
            TransformComponent* t = world.get<TransformComponent>(ent);

            spdlog::info("TRANSFORM: {}, {}, {}", t->x, t->y, t->z);
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

