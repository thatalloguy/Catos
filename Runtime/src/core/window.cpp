//
// Created by allos on 5/16/2024.
//

#include "window.h"
#include <glad/glad.h>


#include "spdlog/spdlog.h"

using namespace catos;

static bool resized = false;
//
//void on_window_resized(GLFWwindow* window, int w, int h){
//    resized = true;
//}

bool Window::initialize(const catos::WindowCreationInfo &creationInfo) {


    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // We do opengl 4.2
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


    _raw_window = SDL_CreateWindow(creationInfo.title, creationInfo.size.x, creationInfo.size.y, SDL_WINDOW_OPENGL);

    if (!_raw_window) {
        spdlog::error("Could not create Window: {}", SDL_GetError());
        return false;
    }
    _context = SDL_GL_CreateContext(_raw_window);
    SDL_GL_MakeCurrent(_raw_window, _context);
    SDL_GL_SetSwapInterval(1);

    gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress);

    return true;
}

Window::~Window() {
    SDL_GL_DestroyContext(_context);
    SDL_DestroyWindow(_raw_window);
    SDL_Quit();
}


math::Vector2 Window::getSize(){
    int w, h;
    SDL_GetWindowSize(_raw_window, &w, &h);

    return {(float) w, (float) h};
}

bool Window::should_window_close() {
    return _should_close;
}

void Window::update() {

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            _should_close = true;
        }

        for (const auto& callback : _callbacks) {
            callback(&event);
        }
    }

    SDL_GL_SwapWindow(_raw_window);

}

void* Window::get_raw_window_ptr() {
    return _raw_window;
}

void Window::add_callback(std::function<void(SDL_Event *event)> callback) {
    _callbacks.push_back(callback);
}
