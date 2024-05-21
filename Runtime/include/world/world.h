//
// Created by allos on 5/20/2024.
//

// use marco's here so that the user can change the limit if desired.
#ifndef MAX_COMPONENTS

#define MAX_COMPONENTS 32

#endif

#ifndef CATOS_WORLD_H
#define CATOS_WORLD_H


#include <vector>
#include <unordered_map>
#include <bitset>

namespace catos {


    typedef unsigned long long EntityId;
    typedef std::bitset<MAX_COMPONENTS> ComponentMask;

    struct EntityInfo {
        EntityId id{};
        ComponentMask mask;
    };

    namespace Component {
        static int c_componentCounter = 0;

        template<class T>
        static int get_id() {
            static int componentId = c_componentCounter++;
            return componentId;
        }
    }


    class World {

    public:
        EntityId new_entity();


        template<class T>
        void assign(EntityId id) {
            int component_id = Component::get_id<T>();
            entities[id].mask.set(component_id);

        }

        template<class T>
        bool has_component(EntityId id) {
            int component_id = Component::get_id<T>();
            return entities[id].mask.test(component_id);
        }

    private:
        std::vector<EntityInfo> entities;


    };





}

#endif //CATOS_WORLD_H
