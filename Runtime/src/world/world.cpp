//
// Created by allos on 5/20/2024.
//

#include "world/world.h"

catos::EntityId catos::World::new_entity() {


    if (!free_entities.empty()) {
        EntityIndex new_index = free_entities.back();
        free_entities.pop_back();
        EntityId new_id = EntityUtils::create_entity_id(new_index, EntityUtils::get_entity_version(entities[new_index].id));
        entities[new_index].id = new_id;
        return entities[new_index].id;
    }
    entities.push_back({EntityUtils::create_entity_id(EntityIndex(entities.size()), 0), ComponentMask() });
    return entities.back().id;
}



