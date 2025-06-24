//
// Created by allos on 24/06/2025.
//
#pragma once

#ifndef CATOS_VERSION
#define CATOS_VERSION "0.0.1"
#include "core/registry.h"
#include "core/window.h"
#include "renderer/renderer.h"
#endif

#include "core/application.h"
#include "stl/string.h"

namespace catos {

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
        Game(const GameCreationInfo& info);
        virtual ~Game();

        virtual void initializeSystems();
        virtual void loadProject();

        virtual bool is_alive();

        virtual void update();
        virtual void render();

        virtual void destroySystems();

    protected:
        Window _window{};
        Renderer& _renderer{Renderer::getInstance()};


    };


    static void registerTypes() {

    }
}
