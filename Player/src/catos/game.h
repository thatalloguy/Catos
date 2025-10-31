//
// Created by allos on 24/06/2025.
//
#pragma once

#ifndef CATOS_VERSION
#define CATOS_VERSION "0.0.1"
#endif


#include <core/timer.h>
#include <core/platform.h>
#include <core/window.h>
#include <renderer/renderer.h>

#include <core/application.h>
#include <stl/string.h>

namespace catos {

    class Registry;

    namespace player_utils {

    }

    struct GameCreationInfo {
        /// The path to the folder in which game.yaml or game.pack is located
        string project_path;

        /// The engine version could be seperate from the engine version the project was made in.
        string engine_version{CATOS_VERSION};
    };

    class Game: public App {

    public:
        Game(const GameCreationInfo& info, Registry& registry);
        ~Game();

        virtual void initializeSystems();
        virtual void loadProject();

        virtual bool is_alive();

        virtual void update();
        virtual void render();

        virtual void destroySystems();

    protected:
        Registry& _registry;
        Timer _frame_timer{};
        Window _window{};
        Renderer& _renderer{Renderer::getInstance()};

        string _lib_path;
        Platform _platform{};
        void* _lib = nullptr;

        PluginEntryPointFn _entry_func{nullptr};
        PluginUpdatePointFn _update_func{nullptr};
        PluginRenderPointFn _render_func{nullptr};


    };


}
