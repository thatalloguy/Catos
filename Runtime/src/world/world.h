#pragma once


#include <unordered_map>
#include "stl/vector.h"
#include "math/vecs.h"

namespace catos {

        typedef unsigned int EntityID;
        typedef unsigned int WorldID;


        class Transform {

        public:

            math::Vector3 position{0, 0, 0};
            math::Vector3 size{0, 0, 0};
            math::Quaternion rotation{0, 0, 0};

        };


        class Entity {

        public:

            Entity();
            Entity(Entity&& entity);

            const EntityID  id;

            Transform getTransform() { return _transform; };
            void setTransform(Transform& transform) { _transform.position = transform.position; _transform.size = transform.size; _transform.rotation = transform.rotation;};

        private:

            Transform _transform{};


        };

        class World {


        public:

            World();
            World(World&& obj) noexcept ;
            World(const World& obj);

            ~World();

            Entity* getEntity(EntityID id);



            void spawnEntity();
            Entity* getLastEntity();


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