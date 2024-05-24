// engine includes
#pragma once
#include "core/registry.h"
#include "core/application.h"
#include <../Renderer/VkEngine.h>
#include <core/window.h>


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
    ScriptingEngine::embed_function<>()


    scriptingEngine.run();

    scriptingEngine.clean_up();


    WindowCreationInfo window_info = {
            .size = { 500, 500 }
    };

    Window window(window_info);


    while (!window.should_window_close()) {
        window.update();
    }


    return 0;
}