//
// Created by allos on 5/5/2024.
//

#include "core/application.h"
#include "core/game.h"
#include "core/registry.h"


class Console {

public:

    void log(MonoString* msg) {
        std::cout << "[Console log]: " << ScriptingEngine::mono_string_to_string(msg) << "\n";
    }
};

catos::App::App(AppCreationInfo* creationInfo) {

    _info = creationInfo;

    init_registry();

    _is_alive = true;
}

catos::App::~App() {
    auto registry = get<Registry>();

    delete registry;

}

void catos::App::init_registry() {



    bind<Registry>(new Registry);

    auto registry = *get<Registry>();

    // Register all classes for reflection
    registry.register_class<Console>()
            .method("log", &Console::log, "Testing :)");



    ScriptingEngine::embed_function<Console, &Console::log, MonoString *>("log");


    registry.gen_cs_bindings_file();
}


bool catos::App::is_alive() {
    return _is_alive;
}

catos::AppCreationInfo *catos::App::getAppInfo() {
    return _info;
}


