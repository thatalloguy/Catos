
#include "world.h"

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
    instances.push_back(new Entity{});
}

catos::Entity *catos::World::getLastEntity() {
    return instances[(int) instances.length() - 1];
}

catos::Entity::Entity() : id(23) {

}

catos::Entity::Entity(catos::Entity &&entity) : id(23) {

}






