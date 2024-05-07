//
// Created by allos on 4/30/2024.
//

#include "core/entity.h"

using namespace catos;


Component* Entity::get_component(str& name) {
    return componentTable[name];
}


void Entity::init() {
    for (auto comp : componentTable) {
        comp.second->init(*this);
    }
}

void Entity::update() {
    for (auto comp : componentTable) {
        comp.second->update(*this);
    }
}

void Entity::destroy() {
    for (auto comp : componentTable) {
        comp.second->destroy(*this);
    }
}