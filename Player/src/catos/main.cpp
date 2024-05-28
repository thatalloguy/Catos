// engine includes
#pragma once
#include "core/registry.h"
#include "core/application.h"
#include <../Renderer/VkEngine.h>
#include <core/window.h>

#include "../tinystl/include/TINYSTL/unordered_map.h"
#include "TINYSTL/vector.h"


#include <fstream>

using namespace catos;

struct Component {
   virtual void init()  {

   };
};

struct TransformComponent{
    float x = 1,y = 2,z = 5;
};

struct Entity {
    tinystl::unordered_map<size_t, void*> components;

    void* getComponent(size_t hash) {
        return static_cast<void*>(components.find(hash)->second);
    };

    bool hasComponent(size_t hash) {
        return components.find(hash) != components.end();
    }


    template<typename T>
    void addComponent(void* new_) {
        addComponent_(new_, std::hash<std::string>{}(typeid(T).name()));
    }

    void addComponent_(void* component, size_t hash) {
        components.insert(tinystl::pair(hash, component));
    }
};

struct Wrapped_Entity {

    static void* new_instance() {
        auto in = new Entity();
        in->addComponent<TransformComponent>(new TransformComponent());
        return static_cast<void*>(in);
    };

    static void destroy_instance(void* instance) {
        delete static_cast<Entity*>(instance);
    }

    static bool has_component(void* instance, MonoString* name) {
        return static_cast<Entity*>(instance)->hasComponent(std::hash<std::string>{}(ScriptingEngine::mono_string_to_string(name)));
    }

    static void* get_component(void* instance, MonoString* name) {
        Entity* ent = static_cast<Entity*>(instance);

        return ent->getComponent(std::hash<std::string>{}(ScriptingEngine::mono_string_to_string(name)));
    }
};



struct Level {
    tinystl::vector<Entity> entities;
};




struct Wrapped_level {

    static void run_func(Component comp) {
        comp.init();
    };


};


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

    //Component::get_id<TransformComponent>();

    ScriptingEngine::embed_function<Console, &Console::log, MonoString *>("log");

    mono_add_internal_call("catos.LibNative::run_component", &Wrapped_level::run_func);

    mono_add_internal_call("catos.LibNative::entity_get_new_instance", &Wrapped_Entity::new_instance);
    mono_add_internal_call("catos.LibNative::entity_destroy_instance", &Wrapped_Entity::destroy_instance);
    mono_add_internal_call("catos.LibNative::entity_has_component_native", &Wrapped_Entity::has_component);
    mono_add_internal_call("catos.LibNative::entity_get_component", &Wrapped_Entity::get_component);

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