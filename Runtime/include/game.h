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

    struct Scene{};

    ///Holds any information about the game
    struct GameConfig {

    };

    /// The Game objects stores the scenes and other objects.
    class Game {

    public:
        Game() {};
        ~Game() {};

        GameConfig& getConfig() { return config; };

        //Scene handling
        void createScene(string name);
        shared_ptr<Scene> getScene(const char* name);

    private:
        GameConfig config;


        unordered_map<cstr , shared_ptr<Scene>> sceneTable;

    };

}
