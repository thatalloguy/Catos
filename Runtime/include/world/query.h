//
// Created by allos on 5/21/2024.
//

#ifndef CATOS_QUERY_H
#define CATOS_QUERY_H

#include <world/world.h>

namespace catos {


    template<typename... Components>
    struct Query {


        Query(World& world) : p_world(&world) {

            if (sizeof...(Components) == 0) {
                all = true;
            } else {
                //unpacking time :)
                int component_ids[] = {0, Component::get_id<Components>() ...};
                for (int i = 1; i < (sizeof...(Components) + 1); i++) {
                    componentMask.set(component_ids[i]);
                }
            }

        };

        struct Iterator {

            Iterator(World* world, EntityIndex index, ComponentMask mask, bool all) :
             p_world(world), index(index), mask(mask), all(all) {}

            EntityId operator*() const {
                return p_world->entities[index].id;
            };

            bool operator==(const Iterator& other) const {
                return index == other.index || index == p_world->entities.size();
            };

            bool operator!=(const Iterator& other) const {
                return index != other.index && index != p_world->entities.size();
            };
            bool valid_index() {
                return EntityUtils::is_entity_valid(p_world->entities[index].id) && (all || mask == (mask & p_world->entities[index].mask));
            }

            Iterator& operator++() {
                do {
                    index++;
                } while (index < p_world->entities.size() && !valid_index());
                return *this;
            }

            EntityIndex index;
            World* p_world;
            ComponentMask  mask;
            bool all{false};

        };

        const Iterator begin() const {
            int first_index = 0;
            while (first_index < p_world->entities.size() &&
                    (componentMask != (componentMask & p_world->entities[first_index].mask) ||
                    !EntityUtils::is_entity_valid(p_world->entities[first_index].id))) {
                first_index++;
            }

            return Iterator(p_world, first_index, componentMask, all);
        };
        const Iterator end() const {
            return Iterator(p_world, EntityIndex(p_world->entities.size()), componentMask, all);
        };



        World* p_world{nullptr};
        ComponentMask  componentMask;
        bool all {false};

    };



}




#endif //CATOS_QUERY_H
