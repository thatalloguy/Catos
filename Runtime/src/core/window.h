//
// Created by allos on 5/16/2024.
//
#pragma once

#include <SDL3/SDL.h>

#include "math/vecs.h"
#include "types.h"

namespace catos {

    class App;

    struct WindowCreationInfo {
        math::Vector2 size{800, 600};
        math::Vector2 position{ 50, 50};
        cstr title = "Catos Application";
        bool is_fullscreen = false;
        bool borderless = false;
        bool enable_darktheme = true; // NOTE: WINDOWS ONLY!!!!!
    };


    class Window {

    public:
        friend class App;

        Window(const WindowCreationInfo& creationInfo);
        ~Window();


        math::Vector2 getSize();

        bool should_window_close();

        void update();

        void* get_raw_window_ptr();


    private:
        SDL_Window* _raw_window{nullptr};
        SDL_GLContext _context{};
        const WindowCreationInfo& _createInfo;

        bool _should_close = false;
        SDL_Event event;
    };

}