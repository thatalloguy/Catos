///
/// Created by allos on 4/30/2024.
///
#pragma once
#include <string>
#include <unordered_map>
#include <iostream>

#include "types.h"
#include "entity.h"


namespace catos {

    /// The scene holds everything about the scene and entities.
    class Scene {

    public:
        Scene(cstr name);
        ~Scene() = default;

        /// Returns the name of the scene
        cstr getName();


        ///entity stuff

        /// Returns an entity via name;
        std::shared_ptr<Entity> getEntity(cstr name);

        /// Creates a new entity with a name, returns the newly created entity
        std::shared_ptr<Entity>  newEntity(cstr name);
        
        /// Changes the name of the entity, returns the changed entity.
        std::shared_ptr<Entity> changeEntityName(cstr oldName, cstr newName);



    private:
        std::unordered_map<str, std::shared_ptr<Entity>> entityTable;
        cstr _name;

    };

    /// Holds any information about the game
    struct GameConfig {

    };

    /// The Game objects stores the scenes and other objects.
    class Game {

    public:
        Game() = default;
        ~Game() = default;

        GameConfig& getConfig() { return config; };

        ///Scene handling
        /// Creates a scene via a name, returns the newly created scene.
        std::shared_ptr<Scene> createScene(cstr name);
        /// Changes the name of a scene, returns the changed scene.
        std::shared_ptr<Scene> changeSceneName(cstr oldName, cstr newName);
        /// Returns the scene via the name
        std::shared_ptr<Scene> getScene(cstr name);

    private:
        GameConfig config;


        std::unordered_map<str, std::shared_ptr<Scene>> sceneTable;

    };

}
