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

Window::Window(const catos::WindowCreationInfo &creationInfo) : _createInfo(creationInfo) {


    SDL_Init(SDL_INIT_VIDEO);
//    if (!) {
//        spdlog::error("Could not initialize SDL3!");
//        exit(-11); // For the game to run we would need glfw
//    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // We do opengl 4.2
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


//
//    GLFWmonitor* monitor;
//
//    if (creationInfo.is_fullscreen) {
//        monitor = glfwGetPrimaryMonitor();
//    } else {
//        monitor = NULL;
//    }

    _raw_window = SDL_CreateWindow(creationInfo.title, creationInfo.size.x, creationInfo.size.y, SDL_WINDOW_OPENGL);

    if (!_raw_window) {
        spdlog::error("Could not create Window: {}", SDL_GetError());
    }
    _context = SDL_GL_CreateContext(_raw_window);

    gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress);
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
    }

    SDL_GL_SwapWindow(_raw_window);

}

void* Window::get_raw_window_ptr() {
    return _raw_window;
}
