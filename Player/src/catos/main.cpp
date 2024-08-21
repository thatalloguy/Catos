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





int main() {


    AppCreationInfo info{};



    App app{&info};



    // Register all classes for reflection


    WindowCreationInfo window_info = {
            .size = { 500, 500 }
    };

    Window window(window_info);


    while (!window.should_window_close()) {
        window.update();
    }


    return 0;
}