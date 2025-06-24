//
// Created by allos on 5/16/2024.
//
#pragma once

#include <functional>
#include <SDL3/SDL.h>

#include "math/vecs.h"
#include "types.h"
#include "stl/vector.h"

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

        Window() {};
        bool initialize(const WindowCreationInfo& creationInfo);
        ~Window();


        math::Vector2 getSize();

        bool should_window_close();

        void update();

        void* get_raw_window_ptr();

        void add_callback(std::function<void(SDL_Event* event)> callback);
        void* get_gl_context() { return &_context; };

    private:
        SDL_Window* _raw_window{nullptr};
        SDL_GLContext _context{};
        catos::vector<std::function<void(SDL_Event* event)>> _callbacks;

        bool _should_close = false;
        SDL_Event event;
    };

}
