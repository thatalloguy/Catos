//
// Created by allos on 24/06/2025.
//

#include "Game.h"

catos::Game::Game(const GameCreationInfo &info) {

}

catos::Game::~Game() {

}

void catos::Game::initializeSystems() {
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

void catos::Game::loadProject() {

}

bool catos::Game::is_alive() {
    return !_window.should_window_close();
}

void catos::Game::update() {
    _window.update();
}

void catos::Game::render() {

}

void catos::Game::destroySystems() {

}
