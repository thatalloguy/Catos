// engine includes
#pragma once

#include "spdlog/spdlog.h"
#include "scripting/ScriptingEngine.h"
#include "core/registry.h"

struct Foo {
    int data = 0;

    void test() {
        spdlog::info("Hello cpp func");
    }
};


int main() {

    catos::ScriptingEngine& engine = catos::ScriptingEngine::getInstance();
    catos::Registry registry{};

    engine.registerNewScript("../../../Resources/Catos/script_test.py");


    auto& foo = registry.register_class<Foo>()
            .property("data", &Foo::data, "Data")
            .method("test", &Foo::test, "test");

    foo.registerToPython<Foo>();

    registry.gen_python_bindings_file();

    try {

        engine.startScripts();

        engine.updateScripts();

        engine.endScripts();
    } catch (py::python_error& e) {

        spdlog::error("{}", e.what());
    }

    return 0;
}

