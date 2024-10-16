//
// Created by allos on 5/16/2024.
//
#pragma once

#ifdef _WIN32
#define ON_WINDOWS
#endif


#include "math/vecs.h"
#include <GLFW/glfw3.h>
#include "types.h"

namespace catos {

    class App;

    struct WindowCreationInfo {
        math::Vector2 size{800, 600};
        math::Vector2 position{ 50, 50};
        cstr title = "Catos Application ";
        bool is_fullscreen = false;
        bool borderless = false;
        bool enable_darktheme = true; // NOTE: WINDOWS ONLY!!!!!
    };


    class Window {

    public:
        friend class App;

        Window(WindowCreationInfo& creationInfo);
        ~Window();

        static math::Vector2 getMonitorSize();

        bool should_window_close();

        void update();

        GLFWwindow* get_glfw_window();


    private:
        GLFWwindow* _raw_window;
        WindowCreationInfo& _createInfo;

        void enable_dark_theme();

    };

}