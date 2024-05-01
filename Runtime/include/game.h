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
        Scene(str name);
        ~Scene() = default;

        str getName();


        //entity stuff
        std::shared_ptr<Entity> getEntity(str name);
        std::shared_ptr<Entity>  newEntity(str name);
        std::shared_ptr<Entity> changeEntityName(str oldName, str newName);



    private:
        std::unordered_map<str, std::shared_ptr<Entity>> entityTable;
        str _name;

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
        std::shared_ptr<Scene> createScene(str name);
        std::shared_ptr<Scene> changeSceneName(str oldName, str newName);
        std::shared_ptr<Scene> getScene(str name);

    private:
        GameConfig config;


        std::unordered_map<str , std::shared_ptr<Scene>> sceneTable;

    };

}
