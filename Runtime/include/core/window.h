//
// Created by allos on 5/16/2024.
//
#pragma once



#include "../math/vecs.h"
#include "../../Renderer/VkEngine.h"
#include "types.h"

namespace catos {

    class App;

    struct WindowCreationInfo {
        math::Vector2 size{100, 100};
        math::Vector2 position{ 50, 50};
        cstr title = "Catos Application ";
        bool is_fullscreen = false;
    };


    class Window {

    public:
        friend class App;


    private:
        GLFWwindow* _raw_window;


    };

}