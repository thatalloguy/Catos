//
// Created by allos on 5/16/2024.
//
#include <core/window.h>
#include "GLFW/glfw3native.h"

using namespace catos;


Window::Window(catos::WindowCreationInfo &creationInfo) : _createInfo(creationInfo) {



    if (!glfwInit()) {
        spdlog::error("Could not initialize GLFW!");
        exit(-11); // For the game to run we would need glfw
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);




    GLFWmonitor* monitor;

    if (creationInfo.is_fullscreen) {
        monitor = glfwGetPrimaryMonitor();
    } else {
        monitor = NULL;
    }

    _raw_window = glfwCreateWindow(creationInfo.size.x, creationInfo.size.y, creationInfo.title, monitor, NULL);

    if (!_raw_window) {
        spdlog::error("Could not create Window");
    }

    if (creationInfo.enable_darktheme || ON_WINDOWS) {
        enable_dark_theme();
    }

    glfwMakeContextCurrent(_raw_window);
}

Window::~Window() {

    glfwDestroyWindow(_raw_window);
    glfwTerminate();
}

void Window::enable_dark_theme() {

}


math::Vector2 Window::getMonitorSize() {

    auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    return math::Vector2{.x = (float) mode->width, .y = (float) mode->height};


}

bool Window::should_window_close() {
    return glfwWindowShouldClose(_raw_window);
}

void Window::update() {
    glfwPollEvents();
}
