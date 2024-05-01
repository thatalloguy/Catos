//
// Created by allos on 4/30/2024.
//

#include "entity.h"

using namespace catos;

template<class Comp>
Comp* Entity::getComponent() {

    auto it = componentTable.find(type_utils::get_type_name<Comp>().c_str());

    if (it != componentTable.end()) {
        return it->second;
    } else {
        return nullptr;
    }

}

Component* Entity::getComponent(str name) {
    return componentTable[name];
}

template<class Comp>
void Entity::addComponent(Component* component) {

    componentTable.insert(type_utils::get_type_name<Comp>().c_str(), component);

}

void Entity::init() {
    for (auto comp : componentTable) {
        comp.second->init();
    }
}

void Entity::update() {
    for (auto comp : componentTable) {
        comp.second->update();
    }
}

void Entity::destroy() {
    for (auto comp : componentTable) {
        comp.second->destroy();
    }
}