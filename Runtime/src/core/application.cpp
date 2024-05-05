//
// Created by allos on 5/5/2024.
//

#include "core/application.h"
#include "core/game.h"
#include "core/registry.h"

catos::App::App(AppCreationInfo* creationInfo) {

    _info = creationInfo;

    init_registry();

    _is_alive = true;
}

catos::App::~App() {

}

void catos::App::init_registry() {

    Registry registry{};

    bind<Registry>(&registry);

    // Register all classes for reflection
    registry.register_class<GameConfig>();

    registry.register_class<Game>()
            .method("get_config", &Game::get_config, "Returns the game config")
            .method("create_scene", &Game::create_scene, "creates a new scene")
            .method("get_scene", &Game::get_scene, "creates a new scene");

    registry.register_class<Scene>()
            .method("get_name", &Scene::get_entity, "Gets the name of the scene")
            .method("get_entity", &Scene::get_entity, "Gets an entity")
            .method("new_entity", &Scene::new_entity, "new entity")
            .method("change_entity_name", &Scene::change_entity_name, "changes the name of an entity");

    registry.register_class<Component>()
            .method("init", &Component::init, "init")
            .method("update", &Component::update, "update")
            .method("destroy", &Component::destroy, "destroy");

    registry.register_class<Entity>()
            .method("setup", &Entity::setup, "Initializes the entity")
            .method("get_name", &Entity::get_name, "returns the name of the entity")
            .method("get_component", &Entity::get_component, "Returns a component")
            .method("add_component", &Entity::add_component, "Adds a component to the entity")
            .method("init", &Entity::init, "Runs Component.init() on every registered component.")
            .method("update", &Entity::update, "Runs Component.update() on every registered component.")
            .method("destroy", &Entity::destroy, "Runs Component.destroy() on every registered component.");

}


bool catos::App::is_alive() {
    return _is_alive;
}

catos::AppCreationInfo *catos::App::getAppInfo() {
    return _info;
}


