// engine includes
#pragma once
#include "core/registry.h"
#include "core/application.h"
#include "world/world.h"
#include <../Renderer/VkEngine.h>
#include <core/window.h>


#include <fstream>

using namespace catos;

struct Wrapped_world {


    /// Do I need to hanlde this?
    static void* new_instance() {
        return (void*) new World();
    }

    static EntityId new_entity(void* instance) {
        return static_cast<World*>(instance)->new_entity();
    }

    static void destroy_instance(void* instance) {
        delete static_cast<World*>(instance);
    }
};

class Console {

public:

    void log(MonoString* msg) {
        std::cout << "[Console log]: " << ScriptingEngine::mono_string_to_string(msg) << "\n";
    }
};

struct TransformComponent {
    float x,y,z;
};

int main() {


    AppCreationInfo info{};


    ScriptingEngine scriptingEngine;

    scriptingEngine.init();

    App app{&info};



    // Register all classes for reflection
    app.get<Registry>()->register_class<Console>()
            .method("log", &Console::log, "Testing :)");

    Component::get_id<TransformComponent>();

    ScriptingEngine::embed_function<Console, &Console::log, MonoString *>("log");
    ScriptingEngine::embed_static_function<int, Component::get_component_id_counter>("get_component_id_Counter");


    mono_add_internal_call("catos.LibNative::world_new_entity_native", &Wrapped_world::new_entity);
    mono_add_internal_call("catos.LibNative::world_new_instance_native", &Wrapped_world::new_instance);
    mono_add_internal_call("catos.LibNative::world_destroy_instance_native", &Wrapped_world::destroy_instance);



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