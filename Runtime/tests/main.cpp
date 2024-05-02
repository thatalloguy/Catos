#pragma once
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

#include <type_utils.h>
#include <TINYSTL/string.h>

#include "registry.h"
#include "game.h"

using namespace pkpy;


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

    TEST_CASE("REGISTRY::INSTANCES") {

        Registry registry;

        Foo foo;


        foo.data = 4;

        registry.bind<Foo>(&foo);


        auto* test = registry.get<Foo>();

        CHECK(test->data == foo.data);
    }

    TEST_CASE("REGISTRY::METHODS") {

        Registry registry;

        Foo foo;


        foo.data = 4;

        auto& field = registry.register_class<Foo>()
                .property("data", &Foo::data, "dummy variable")
                .method("get_data", &Foo::get_data, "Returns the data of Foo");

        registry.register_class<Game>()
                .method("init", &Game::init, "Initializes the game");

        registry.register_class<ScriptComponent>()
                .method("init", &ScriptComponent::init, "Initializes the Object, gets ran at the beginning")
                .method("update", &ScriptComponent::update, "update function gets called every tick")
                .method("destroy", &ScriptComponent::destroy, "Gets called when the object is destroyed");




        Property* test = field.get_property("data");
        Method* meth = field.get_method("get_data");


        auto* testFloat = (float*) (test->get_value(&foo));


        CHECK(*testFloat == meth->invoke_function<float>(&foo));

        registry.gen_python_bindings_file();
    }

    TEST_CASE("GAME::SCENES") {
        Game game;

        auto s1 = game.createScene("test");

        CHECK(s1 == game.getScene("test"));

        game.changeSceneName("test", "test2");

        CHECK(s1 == game.getScene("test2"));
    }

    TEST_CASE("SCENES::ENTITIES") {
        Game game;

        auto scene = game.createScene("test");

        auto bob = scene->newEntity("bob");

        CHECK(bob == scene->getEntity("bob"));

        scene->changeEntityName("bob", "henk");

        CHECK(bob == scene->getEntity("henk"));
    }


    TEST_CASE("SCRIPTING::COMPONENT") {
/*
        pkpy::VM* vm = new VM();
        PyObject* mod = vm->new_module("catos");
        //////std::ifstream inputFile("../../test.py");
        std::string str("import catos\n"
                        "\n"
                        "test = catos.Game()\n"
                        "\n"
                        "class TestComponent(catos.ScriptComponent):\n"
                        "    def __init__(self):\n"
                        "        print(\"init from PYTHON\")\n"
                        "\n"
                        "    def update(self):\n"
                        "        print(\"update!\")\n"
                        "\n"
                        "    def destroy(self):\n"
                        "        print(\"Destroy!\")\n"
                        "\n"
                        "\n"
                        "");

        Game::register_class(vm, mod);
        vm->register_user_class<ScriptComponent>(mod, "ScriptComponent", true);
        vm->exec(str);


        Script testScript;
        testScript.attachScript(str, vm);

        Component& comp = testScript;

        comp.init();
        comp.update();
        comp.destroy();

        delete vm;*/
    }

    TEST_CASE("SCRIPTING::TEST") {

        pkpy::VM* vm = new VM();
        PyObject* mod = vm->new_module("catos");
        std::ifstream inputFile("../../test.py");
        std::string str((std::istreambuf_iterator<char>(inputFile)),
                        std::istreambuf_iterator<char>());

        Game::register_class(vm, mod);
        vm->register_user_class<ScriptComponent>(mod, "ScriptComponent", true);
        vm->register_user_class<Entity>(mod, "Entity", true);

        vm->exec(str);

        Entity test;

        Script testScript;

        testScript.attachScript(str, vm);

        testScript.init(test);
        //testScript.update(test);

        std::cout << "CPP: " << test.test << "\n";

        delete vm;
    }

}


int main(int argc, char** argv) {

    doctest::Context context;
    context.applyCommandLine(argc, argv);
    context.setOption("no-breaks", true);

    int res = context.run();


    return res;
}

