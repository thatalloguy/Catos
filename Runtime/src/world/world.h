#pragma once


#include <unordered_map>
#include "stl/vector.h"
#include "math/vecs.h"

namespace catos {

        typedef unsigned int EntityID;
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
            Entity();

            /// Destroys the entity and its allocated resources.
            Entity(Entity&& entity);

            /// its ID represented by an uint
            const EntityID  id;

            /// Returns a REFERENCE to the private transform.
            Transform& getTransform() { return _transform; };

        private:

            Transform _transform{};


        };

        /// A World is an object that holds entities. (Also known as level or scene).
        class World {


        public:

            /// Creates the world and allocates some data.
            World();

            /// move constructor
            World(World&& obj) noexcept ;

            /// copy constructor.
            World(const World& obj);

            /// Destroys the world.
            ~World();

            /// Returns the Entity with the corresponding ID.
            Entity* getEntity(EntityID id);


            /// Creates a new Entity.
            void spawnEntity();

            /// returns the last created Entity.
            Entity* getLastEntity();


        private:
            void cleanUp();

            void getNewWorldID();
            void getNewEntityID();

            catos::vector<Entity*> instances;

        };


        /// Returns the current active world
        static World* getCurrentWorld();

        /// changes the world via ID.
        static World* setCurrentWorld(WorldID ID);

        /// Returns a world Via ID.
        static World* getWorldViaID(WorldID ID);
}