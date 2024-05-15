// engine includes
#pragma once
#include "core/registry.h"
#include "core/application.h"
#include <fstream>

using namespace catos;


class Console {

public:

    void log(MonoString* msg) {



        std::cout << "[Console log]: " << ScriptingEngine::mono_string_to_string(msg) << "\n";
    }
};

int main() {


    AppCreationInfo info{};


    ScriptingEngine scriptingEngine;

    scriptingEngine.init();

    App app{&info};



    // Register all classes for reflection
    app.get<Registry>()->register_class<Console>()
            .method("log", &Console::log, "Testing :)");

    ScriptingEngine::embed_function<Console, &Console::log, MonoString *>("log");


    scriptingEngine.run();

    scriptingEngine.clean_up();


    return 0;
}