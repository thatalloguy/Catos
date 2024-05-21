//
// Created by allos on 5/20/2024.
//

#include "world/world.h"

catos::EntityId catos::World::new_entity() {
    entities.push_back({entities.size(), ComponentMask() });
    return entities.back().id;
}



