//
// Created by allos on 4/30/2024.
//

#include "game.h"


namespace catos {

    ///////GAME=
    shared_ptr<Scene> catos::Game::getScene(cstr name) {

        auto it = sceneTable.find(name);

        if (it != sceneTable.end()) {
            return it->second;
        } else {
            return nullptr;
        }
    }

    void catos::Game::createScene(cstr name) {
        //TODO
    }



    ////////////// SCENE
    Scene::Scene(cstr name) {

    }
}