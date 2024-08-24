#pragma once


#include <unordered_map>
#include "stl/vector.h"

namespace catos {

        typedef unsigned int EntityID;
        typedef unsigned int WorldID;



        struct EntityCreationInfo {

        };

        class Entity {

        public:

            Entity(EntityCreationInfo& info);
            Entity(Entity&& entity);

            const EntityID  id;

        };

        class World {


        public:

            World();
            World(World&& obj) noexcept ;
            World(const World& obj);

            ~World();

            Entity* getEntity(EntityID id);



            void spawnEntity();


        private:
            void cleanUp();

            void getNewWorldID();
            void getNewEntityID();

            catos::vector<Entity*> instances;

        };


        static World* getCurrentWorld();
        static World* setCurrentWorld(WorldID ID);
        static World* getWorldViaID(WorldID ID);
}