//
// Created by allos on 5/16/2024.
//
#pragma once
#include "Editor.h"
#include <../../Runtime/include/core/application.h>

namespace catos::Editor {


    // DO NOT TOUCH >:(
    bool _initialized;

    Window* _window;
    App* _app;

    VulkanEngine _renderer;

}

void catos::Editor::init() {

    AppCreationInfo appCreationInfo{
            .version = 1,
        .applicationTitle = "Catos Editor"
    };

    _app = new App(&appCreationInfo);

    WindowCreationInfo windowCreationInfo{
        .size = {1280, 720},
        .title = "Catos Editor",
    };

    _window = new Window(windowCreationInfo);

    _initialized = true;
}

void catos::Editor::run() {


    while (!_window->should_window_close()) {

        _window->update();

    }

}

void catos::Editor::cleanUp() {

    //_renderer.CleanUp();

    delete _app;
    delete _window;
}
