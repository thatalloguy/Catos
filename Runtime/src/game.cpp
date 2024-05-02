//
// Created by allos on 4/30/2024.
//

#include "game.h"


namespace catos {

    ///////GAME=
    std::shared_ptr<Scene> catos::Game::getScene(cstr  name) {

        auto it = sceneTable.find(name);

        if (it != sceneTable.end()) {
            return it->second;
        } else {
            return nullptr;
        }
    }

    std::shared_ptr<Scene> catos::Game::createScene(cstr  name) {

        auto newScene = std::make_shared<Scene>(name);

        sceneTable.emplace(name, newScene);

        return newScene;
    }

    std::shared_ptr<Scene> Game::changeSceneName(cstr oldName,cstr newName) {
        auto oldN = sceneTable.find(oldName);
        auto newN = sceneTable.find(newName);

        if (oldN != sceneTable.end() && newN == sceneTable.end()) { // Both names are valid
            sceneTable.emplace(newName, oldN->second); // move the value to the new name
            sceneTable.erase(oldName); // remove the value of the old name
        }

        return getScene(newName);
    }


    ////////////// SCENE
    Scene::Scene(cstr  name) : _name(name) {

    }

    cstr Scene::getName() {
        return _name;
    }

    std::shared_ptr<Entity> Scene::getEntity(cstr  name) {
        auto it = entityTable.find(name);

        if (it != entityTable.end()) {
            return it->second;
        } else {
            return nullptr;
        }
    }

    std::shared_ptr<Entity> Scene::newEntity(cstr  name) {

        str nam = std::string_view(name);
        auto newEntity = std::make_shared<Entity>();

        entityTable.emplace(name, newEntity);

        return newEntity;
    }

    std::shared_ptr<Entity> Scene::changeEntityName(cstr  oldName, cstr newName) {
        auto oldN = entityTable.find(oldName);
        auto newN = entityTable.find(newName);

        if (oldN != entityTable.end() && newN == entityTable.end()) { // Both names are valid
            entityTable.emplace(newName, oldN->second); // move the value to the new name
            entityTable.erase(oldName); // remove the value of the old name
        }

        return getEntity(newName);
    }
}