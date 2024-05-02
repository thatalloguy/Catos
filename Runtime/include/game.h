///
/// Created by allos on 4/30/2024.
///
#pragma once

#include <pocketpy.h>

#include <string>
#include <unordered_map>
#include <iostream>
#include "types.h"
#include "entity.h"

using namespace pkpy;

namespace catos {

    /// The scene holds everything about the scene and entities.
    class Scene {

    public:
        Scene(cstr Name);
        ~Scene() = default;

        /// Returns the Name of the scene
        cstr getName();


        ///entity stuff

        /// Returns an entity via Game;
        std::shared_ptr<Entity> getEntity(cstr Name);

        /// Creates a new entity with a Game, returns the newly created entity
        std::shared_ptr<Entity>  newEntity(cstr Name);
        
        /// Changes the Game of the entity, returns the changed entity.
        std::shared_ptr<Entity> changeEntityName(cstr oldGame, cstr newGame);



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
        PY_CLASS(Game, catos, Game)
        Game() = default;
        ~Game() = default;

        void init() {
            std::cout << "INIT OF GAME OBJECT FROM CPP \n";
        };

        GameConfig& getConfig() { return config; };

        ///Scene handling
        /// Creates a scene via a Game, returns the newly created scene.
        std::shared_ptr<Scene> createScene(cstr Game);
        /// Changes the Game of a scene, returns the changed scene.
        std::shared_ptr<Scene> changeSceneName(cstr oldGame, cstr newGame);
        /// Returns the scene via the Game
        std::shared_ptr<Scene> getScene(cstr Game);
        
        // POCKETPY IMPL
        bool operator==(Game other) {
            return false; // bob is unique ;)
        }

        Game* _() {
            return this;
        }

        static void _register(VM* vm, PyObject* mod, PyObject* type){
            //PY_STRUCT_LIKE(Game)


            _bind(vm, type, "__init__(self)", &Game::init);


        }

    private:
        GameConfig config;


        std::unordered_map<str, std::shared_ptr<Scene>> sceneTable;

    };

}
