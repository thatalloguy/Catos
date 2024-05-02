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

        auto& field = registry.register_class<Foo>().property("data", &Foo::data);


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
                .property("data", &Foo::data)
                .method("get_data", &Foo::get_data);

        registry.register_class<Game>()
                .method("init", &Game::init);

        registry.register_class<ScriptComponent>()
                .method("init", &ScriptComponent::init)
                .method("update", &ScriptComponent::update)
                .method("destroy", &ScriptComponent::destroy);




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

    TEST_CASE("POCKETPY") {

        pkpy::VM* vm = new VM();
        PyObject* mod = vm->new_module("catos");
        std::ifstream inputFile("../../test.py");
        std::string str((std::istreambuf_iterator<char>(inputFile)),
                        std::istreambuf_iterator<char>());

        Game::register_class(vm, mod);
        //ScriptComponent::register_class(vm, mod);
        vm->register_user_class<ScriptComponent>(mod, "ScriptComponent", true);
        vm->exec(str);
/*        PyObject* obj = vm->getattr(vm->_main, "TestComponent");
        PyObject* inst = vm->call(obj);
        vm->call_method(inst, "update");*/


        delete vm;
    }

    TEST_CASE("SCRIPT") {

        pkpy::VM* vm = new VM();
        PyObject* mod = vm->new_module("catos");
        std::ifstream inputFile("../../test.py");
        std::string str((std::istreambuf_iterator<char>(inputFile)),
                        std::istreambuf_iterator<char>());

        Game::register_class(vm, mod);
        vm->register_user_class<ScriptComponent>(mod, "ScriptComponent", true);
        vm->exec(str);


        Script testScript;
        testScript.attachScript(str, vm);

        Component& comp = testScript;

        comp.init();
        comp.update();
        comp.destroy();

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

