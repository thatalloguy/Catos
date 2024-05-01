//
// Created by allos on 4/30/2024.
//
#pragma once
#include <string>
#include <unordered_map>
#include <iostream>

#include "types.h"
#include "entity.h"


namespace catos {


    class Scene {

    public:
        Scene(cstr name);
        ~Scene() = default;

        cstr getName();


        //entity stuff
        std::shared_ptr<Entity> getEntity(cstr name);
        std::shared_ptr<Entity>  newEntity(cstr name);
        std::shared_ptr<Entity> changeEntityName(cstr oldName, cstr newName);



    private:
        std::unordered_map<str, std::shared_ptr<Entity>> entityTable;
        cstr _name;

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
        std::shared_ptr<Scene> createScene(cstr name);
        std::shared_ptr<Scene> changeSceneName(cstr oldName, cstr newName);
        std::shared_ptr<Scene> getScene(cstr name);

    private:
        GameConfig config;


        std::unordered_map<str, std::shared_ptr<Scene>> sceneTable;

    };

}
