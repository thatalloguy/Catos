#pragma once
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

#include <type_utils.h>
#include <TINYSTL/string.h>

#include "registry.h"
#include "game.h"
#include "application.h"


struct Foo {
    float data = 2;

    float get_data() {
        return data;
    }
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


        registry.register_class<Entity>()
                .method("init", &Entity::init, "init")
                .method("update", &Entity::update, "update the entity")
                .method("destroy", &Entity::destroy, "destroy");

        registry.register_class<Component>()
                .method("init", &Component::init, "Initializes")
                .method("update", &Component::init, "update")
                .method("destroy", &Component::init, "destroy");



        Property* test = field.get_property("data");
        Method* meth = field.get_method("get_data");


        auto* testFloat = (float*) (test->get_value(&foo));


        CHECK(*testFloat == meth->invoke_function<float>(&foo));

    }

    TEST_CASE("GAME::SCENES") {
        Game game;

        auto s1 = game.create_scene("test");

        CHECK(s1 == game.get_scene("test"));

        game.change_scene_name("test", "test2");

        CHECK(s1 == game.get_scene("test2"));
    }

    TEST_CASE("SCENES::ENTITIES") {
        Game game;

        auto scene = game.create_scene("test");

        auto bob = scene->new_entity("bob");

        CHECK(bob == scene->get_entity("bob"));

        scene->change_entity_name("bob", "henk");

        CHECK(bob == scene->get_entity("henk"));
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

}


int main(int argc, char** argv) {

    doctest::Context context;
    context.applyCommandLine(argc, argv);
    context.setOption("no-breaks", true);

    int res = context.run();


    return res;
}

