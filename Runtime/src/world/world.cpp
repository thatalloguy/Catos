
#include "world.h"

unsigned int getIndex(catos::EntityID id) {
    return id >> 32;
}


// Contructors
catos::World::World() {
    instances.reserve(8);
}

catos::World::World(World &&obj) noexcept {

}

catos::World::World(const World &obj) {

}

catos::World::~World() {
    cleanUp();
}

void catos::World::cleanUp() {
    for (auto item : instances) {
        if (item != nullptr) {
            delete item;
        }
    }
}



// Entity handling
catos::EntityID catos::World::getNewEntityID() {

    unsigned int index = 0;

    EntityID id = ((EntityID) index << 32 | (EntityID) idCounter);

    idCounter++;

    return id;
}

catos::Entity& catos::World::spawnEntity() {

    //first check if we have any free spots.
    if (!freeSlots.empty()) {

        instances[freeSlots.back()] = new Entity(getNewEntityID());
        freeSlots.pop_back();

    } else { // if we dont have any just use push_back.

        instances.push_back(new Entity(getNewEntityID()));
    }

    return *instances.back();
}

void catos::World::deleteEntity(catos::EntityID id) {

    auto index = getIndex(id);

    if (instances[index] != nullptr) {
        delete instances[index];
        freeSlots.push_back(index);
    }

}

catos::Entity& catos::World::getEntity(catos::EntityID id) {

    int index = (int) getIndex(id);

    if (instances.length() < index) {
        throw catos::invalid_entity_id{};
    }

    auto ent = instances[index];

    return *ent;
}


catos::Entity::Entity(const catos::EntityID &id) {

}

catos::Entity::~Entity() {

}




