//
// Created by allos on 5/20/2024.
//

// use marco's here so that the user can change the limit if desired.
#ifndef MAX_COMPONENTS
#define MAX_COMPONENTS 32
#endif

#ifndef MAX_ENTITIES
#define MAX_ENTITIES 100
#endif

#ifndef CATOS_WORLD_H
#define CATOS_WORLD_H




#include <vector>
#include <unordered_map>
#include <bitset>
#include <chrono>
#include <iostream>

namespace catos {

    typedef unsigned int EntityIndex;
    typedef unsigned int EntityVersion;
    typedef unsigned long long EntityId;

    typedef std::bitset<MAX_COMPONENTS> ComponentMask;

    struct EntityInfo {
        EntityId id{};
        ComponentMask mask;
    };

    namespace EntityUtils {

        //NOTE: you *could* exceed the 32bit number.
        inline EntityId create_entity_id(EntityIndex index, EntityVersion version) {
            return ((EntityIndex)index << 32 | ((EntityId) version));
        }

        inline EntityIndex get_entity_index(EntityId id) {
            return id >> 32;
        }

        inline EntityVersion get_entity_version(EntityId id) {
            return (EntityVersion)id;
        }

        inline bool is_entity_valid(EntityId id) {
            return (id >> 32) != EntityIndex(-1);
        }

        #define INVALID_ENTITY create_entity_id(EntityIndex(-1), 0)

    }

    namespace Component {
        static int c_componentCounter = 0;

        template<class T>
        static int get_id() {
            static int componentId = c_componentCounter++;
            return componentId;
        }

        static int get_component_id_counter() {
            return c_componentCounter;
        }
    }

    struct ComponentPool
    {
        ComponentPool(size_t elementsize)
        {
            // We'll allocate enough memory to hold MAX_ENTITIES, each with element size
            elementSize = elementsize;
            pData = new char[elementSize * MAX_ENTITIES];
        }

        ~ComponentPool()
        {
            delete[] pData;
        }

        inline void* get(size_t index)
        {
            // looking up the component at the desired index
            return pData + index * elementSize;
        }

        char* pData{ nullptr };
        size_t elementSize{ 0 };
    };


    class World {

    public:

        EntityId new_entity();


        template<class T>
        T* assign(EntityId id) {
            int component_id = Component::get_id<T>();

            // check if the entity is not deleted


            if (component_pools.size() <= component_id) { // not enough component pool
                component_pools.resize(component_pools.size() + 1, nullptr);
            }
            if (component_pools[component_id] == nullptr) {
                component_pools[component_id] = new ComponentPool(sizeof(T));
            }

            T* pComponent = new (component_pools[component_id]->get(id)) T();


            entities[id].mask.set(component_id);
            return pComponent;
        }

        template<class T>
        bool has_component(EntityId id) {
            int component_id = Component::get_id<T>();
            return entities[id].mask.test(component_id);
        }

        template<typename T>
        T* get(EntityId id) {
            int component_id = Component::get_id<T>();

            // check if the entity is not deleted

            if (!entities[id].mask.test(component_id))
                return nullptr;

            T* p_component = static_cast<T*>(component_pools[component_id]->get(id));
            return p_component;
        }

/*        template<typename T>
        T* get_unchecked(EntityId id) {
            return static_cast<T*>(component_pools[Component::get_id<T>()]->get(id));
        }*/

        template<typename T>
        void remove(EntityId id) {


            int componentId =  Component::get_id<T>();
            entities[EntityUtils::get_entity_index(id)].mask.reset(componentId);
        }


        void destroy_entity(EntityId id) {
            EntityId new_id = EntityUtils::create_entity_id(EntityIndex(-1), EntityUtils::get_entity_version(id) + 1);
            entities[EntityUtils::get_entity_index(id)].id = new_id;
            entities[EntityUtils::get_entity_index(id)].mask.reset();
            free_entities.push_back(EntityUtils::get_entity_index(id));
        }


        /// WRAPPED METHODS USAGE IN CPP IS UNTESTED!

        void assign_(EntityId entityId, int component_id, int component_type_size) {

            // check if the entity is not deleted


            if (component_pools.size() <= component_id) { // not enough component pool
                component_pools.resize(component_pools.size() + 1, nullptr);
            }
            if (component_pools[component_id] == nullptr) {
                component_pools[component_id] = new ComponentPool(component_type_size);
            }

            //void* pComponent = new (component_pools[component_id]->get(id)) T();


            entities[entityId].mask.set(component_id);
        }

        bool has_component_(EntityId id, int component_id) {
            return entities[id].mask.test(component_id);
        }


        std::vector<EntityInfo> entities;


    private:
        std::vector<EntityIndex> free_entities;
        std::vector<ComponentPool*> component_pools;

    };





}

#endif //CATOS_WORLD_H
