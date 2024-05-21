//
// Created by allos on 5/20/2024.
//

#include "world/world.h"

catos::EntityId catos::World::new_entity() {
    entities.push_back({entities.size(), ComponentMask() });
    return entities.back().id;
}



















catos::ComponentPool::ComponentPool(size_t element_size) {
    this->element_size = element_size;
    p_data = new char[element_size * MAX_ENTITIES];
}

catos::ComponentPool::~ComponentPool() {
    delete[] p_data;
}

void *catos::ComponentPool::get(size_t index) {
    return p_data + index * element_size;
}
