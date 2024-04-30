//
// Created by allos on 4/30/2024.
//
#pragma once
#include <string>
#include <unordered_map>
#include <iostream>

#include "types.h"

using namespace std;

namespace catos {

    struct Entity;

    class Scene {

    public:
        Scene(cstr name);
        ~Scene() = default;

        cstr getName();


        //entity stuff
        shared_ptr<Entity> getEntity(cstr name);


    private:
        unordered_map<cstr, shared_ptr<Entity>> entityTable;

    };

    ///Holds any information about the game
    struct GameConfig {

    };

    /// The Game objects stores the scenes and other objects.
    class Game {

    public:
        Game() = default;
        ~Game() = default;

        GameConfig& getConfig() { return config; };

        //Scene handling
        void createScene(cstr name);
        void changeSceneName(cstr oldName, cstr newName);
        shared_ptr<Scene> getScene(const char* name);

    private:
        GameConfig config;


        unordered_map<cstr , shared_ptr<Scene>> sceneTable;

    };

}
