#pragma once


#include "stl/vector.h"

namespace Catos {

        typedef unsigned int EntityID;
        typedef unsigned int WorldID;



        struct EntityCreationInfo {

        };

        class Entity {

        public:

            Entity(EntityCreationInfo& info);
            Entity(Entity&& entity);

        };

        class World {


        public:

            World();
            World(World&& obj);
            World(const World& obj);

            ~World();

            Entity* getEntity(EntityID id);

        private:
            void cleanUp();

            void getNewWorldID();
            void getNewEntityID();

            Catos::vector<Entity*> instances;

        };



        static World* getCurrentWorld();
        static World* setCurrentWorld(WorldID ID);
        static World* getWorldViaID(WorldID ID);
}