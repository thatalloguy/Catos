// engine includes
#pragma once
#include <core/application.h>
#include <core/window.h>
#include "world/world.h"


using namespace catos;





int main() {


    AppCreationInfo info{};



    App app{&info};



    // Register all classes for reflection


    WindowCreationInfo window_info = {
            .size = { 500, 500 }
    };

    Window window(window_info);

    catos::World world{};

    world.spawnEntity();
    world.spawnEntity();

    Entity& ent = *world.getLastEntity();

    spdlog::info("Entity.info {}", ent.getTransform().position.x);



    while (!window.should_window_close()) {
        window.update();
    }


    return 0;
}