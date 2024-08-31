#pragma once


#include <unordered_map>
#include "stl/vector.h"
#include "math/vecs.h"

namespace catos {

        struct invalid_entity_id {
            const char* what() {
                return "The given Entity ID is invalid\n";
            }
        };

        typedef unsigned long long EntityID;
        typedef unsigned int EntityIndex;
        typedef unsigned int WorldID;

        /// A Script is an empty class that holds logic made in python.
        class Script {

        public:

            /// The constructors gets called at the start of the script.
            Script() {};

            /// the update function gets called every frame
            void update() {};

            /// this function is called when the game ends.
            void end() {};

        };


        /// An mathematical-object to represent an object in space.
        class Transform {

        public:

            math::Vector3 position{0, 0, 0};
            math::Vector3 size{0, 0, 0};
            math::Quaternion rotation{0, 0, 0};

        };

        /// An empty model for representing any object in the (game) world.
        class Entity {

        public:

            /// creates the entity.
            Entity(const EntityID& id);

            /// Destroys the entity and its allocated resources.
            ~Entity();

            /// Returns a REFERENCE to the private transform.
            Transform& getTransform() { return _transform; };
            EntityID& getID() { return _id; };

        private:
            EntityID _id;
            Transform _transform{};


        };

        /// A World is an object that holds entities. (Also known as level or scene).
        class World {


        public:

            /// Creates the world and allocates some data.
            World();

            /// Destroys the world.
            ~World();


            /// Returns the Entity with the corresponding ID.
            Entity& getEntity(EntityID id);

            /// Creates a new Entity.
            Entity& spawnEntity();

            /// Deletes the Entity of the given ID
            void deleteEntity(EntityID id);



        private:
            void cleanUp();


            EntityID getNewEntityID();

            catos::vector<Entity*> instances;
            catos::vector<unsigned int> freeSlots;
            unsigned int idCounter = 0;

        };


        /// Returns the current active world
        static World* getCurrentWorld();

        /// changes the world via ID.
        static World* setCurrentWorld(WorldID ID);

        /// Returns a world Via ID.
        static World* getWorldViaID(WorldID ID);
}