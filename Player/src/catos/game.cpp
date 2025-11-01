//
// Created by allos on 24/06/2025.
//

#include "game.h"

#include <direct.h>
#include <core/registry.h>


catos::Game::Game(const GameCreationInfo &info, Registry& registry): _registry(registry) {
    _lib_path = info.project_path;
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

    _lib = _platform.load_shared_library(_lib_path);

    if (_lib) {
        _entry_func = (PluginEntryPointFn) _platform.get_proc_adress(_lib, "catos_entry_point");
        _update_func = (PluginUpdatePointFn) _platform.get_proc_adress(_lib, "catos_update");
        _render_func = (PluginRenderPointFn) _platform.get_proc_adress(_lib, "catos_render");
        if (_entry_func && _update_func && _render_func) {
            _entry_func(&_registry);

            spdlog::info("Successfully loaded project: [{}]", _lib_path.c_str());
            return;
        }
        spdlog::error("Failed to load functions");
        _platform.free_shared_library(_lib);
    }


    spdlog::error("Could not load project [{}]: {} {} {} {}", _lib_path.c_str(),
        _lib != nullptr,
        _entry_func != nullptr,
        _update_func != nullptr,
        _render_func != nullptr
        );

}

bool catos::Game::is_alive() {
    return !_window.should_window_close();
}

void catos::Game::update() {
    float delta_time = _frame_timer.elapsed() * 10;
    _frame_timer.reset();
     if (_lib)  _render_func();
    _window.update();

    if (_lib) _update_func(delta_time);
}

void catos::Game::render() {

}

void catos::Game::destroySystems() {
    if (_lib) _platform.free_shared_library(_lib);
}
