//
// Created by allos on 5/16/2024.
//

#ifndef CATOS_MATH_H
#define CATOS_MATH_H

#include <glm/glm.hpp>

namespace catos::math {


    struct Vector2 {

        float x, y;

        bool operator==(Vector2& b) {
            return (this->x == b.x && this->y == b.y);
        }

        bool operator==(glm::vec2& b) {
            return (this->x == b.x && this->y == b.y);
        }
    };

}



#endif //CATOS_MATH_H
