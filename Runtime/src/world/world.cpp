
#include "world.h"

catos::World::World() {

}

catos::World::World(World &&obj) noexcept {

}

catos::World::World(const World &obj) {

}

catos::World::~World() {
    cleanUp();
}

catos::Entity *catos::World::getEntity(EntityID id) {
    return nullptr;
}

void catos::World::cleanUp() {

    for (auto e : instances) {
        delete e;
    }
}

void catos::World::getNewWorldID() {

}

void catos::World::getNewEntityID() {

}

void catos::World::spawnEntity() {

    EntityCreationInfo info{

    };

    instances.push_back(new Entity(info));

}

catos::Entity::Entity(catos::EntityCreationInfo &info) : id(23) {

}

catos::Entity::Entity(catos::Entity &&entity) : id(23) {

}






