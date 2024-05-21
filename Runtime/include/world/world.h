//
// Created by allos on 5/20/2024.
//

#ifndef CATOS_WORLD_H
#define CATOS_WORLD_H


#include <vector>
#include <unordered_map>

namespace catos {

    int componentCounter = 0;

    namespace World {
        template<class T>
        int get_id() {
            static int componentId = componentCounter++;
            return componentId;
        }
    }





}

#endif //CATOS_WORLD_H
