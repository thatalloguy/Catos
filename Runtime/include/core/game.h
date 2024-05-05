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
        Scene(cstr Name);
        ~Scene() = default;

        /// Returns the Name of the scene
        cstr get_name();


        ///entity stuff

        /// Returns an entity via Game;
        std::shared_ptr<Entity> get_entity(cstr Name);

        /// Creates a new entity with a Game, returns the newly created entity
        std::shared_ptr<Entity>  new_entity(cstr Name);
        
        /// Changes the Game of the entity, returns the changed entity.
        std::shared_ptr<Entity> change_entity_name(cstr oldGame, cstr newGame);



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

        GameConfig& get_config() { return config; };

        ///Scene handling
        /// Creates a scene via a Game, returns the newly created scene.
        std::shared_ptr<Scene> create_scene(cstr Game);
        /// Changes the Game of a scene, returns the changed scene.
        std::shared_ptr<Scene> change_scene_name(cstr oldGame, cstr newGame);
        /// Returns the scene via the Game
        std::shared_ptr<Scene> get_scene(cstr Game);

    private:
        GameConfig config;


        std::unordered_map<str, std::shared_ptr<Scene>> sceneTable;

    };

}
