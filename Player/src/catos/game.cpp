//
// Created by allos on 24/06/2025.
//

#include "game.h"

catos::game::game(const GameCreationInfo &info) {

}

catos::game::~game() {

}

void catos::game::initializeSystems() {
    // First lets create a window

    ///todo create the window as described via a game.yaml or game.pack
    if (!_window.initialize({})) {
        spdlog::error("[Player] Could not create window!");
        exit(-201);
    }



    // Than create the renderer.
    if (_renderer.init({}) == RENDERER_ALREADY_INITIALIZED) {
        spdlog::warn("Renderer already initialized, unexpected behaviour.");
    }
}

void catos::game::loadProject() {

}

bool catos::game::is_alive() {
    return !_window.should_window_close();
}

void catos::game::update() {
    _window.update();
}

void catos::game::render() {

}

void catos::game::destroySystems() {

}
