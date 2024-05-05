//
// Created by allos on 4/30/2024.
//

#include "game.h"


namespace catos {

    ///////GAME=
    std::shared_ptr<Scene> catos::Game::get_scene(cstr  Game) {

        auto it = sceneTable.find(Game);

        if (it != sceneTable.end()) {
            return it->second;
        } else {
            return nullptr;
        }
    }

    std::shared_ptr<Scene> catos::Game::create_scene(cstr  Game) {

        auto newScene = std::make_shared<Scene>(Game);

        sceneTable.emplace(Game, newScene);

        return newScene;
    }

    std::shared_ptr<Scene> Game::change_scene_name(cstr oldGame, cstr newGame) {
        auto oldN = sceneTable.find(oldGame);
        auto newN = sceneTable.find(newGame);

        if (oldN != sceneTable.end() && newN == sceneTable.end()) { // Both names are valid
            sceneTable.emplace(newGame, oldN->second); // move the value to the new name
            sceneTable.erase(oldGame); // remove the value of the old name
        }

        return get_scene(newGame);
    }


    ////////////// SCENE
    Scene::Scene(cstr  name) : _name(name) {

    }

    cstr Scene::get_name() {
        return _name;
    }

    std::shared_ptr<Entity> Scene::get_entity(cstr  Name) {
        auto it = entityTable.find(Name);

        if (it != entityTable.end()) {
            return it->second;
        } else {
            return nullptr;
        }
    }

    std::shared_ptr<Entity> Scene::new_entity(cstr  Name) {

        str nam = std::string_view(Name);
        auto newEntity = std::make_shared<Entity>();

        entityTable.emplace(Name, newEntity);

        return newEntity;
    }

    std::shared_ptr<Entity> Scene::change_entity_name(cstr  oldGame, cstr newGame) {
        auto oldN = entityTable.find(oldGame);
        auto newN = entityTable.find(newGame);

        if (oldN != entityTable.end() && newN == entityTable.end()) { // Both names are valid
            entityTable.emplace(newGame, oldN->second); // move the value to the new name
            entityTable.erase(oldGame); // remove the value of the old name
        }

        return get_entity(newGame);
    }
}