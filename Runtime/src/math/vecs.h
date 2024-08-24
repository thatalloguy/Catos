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

        void operator+(Vector2& b) {
            this->x += b.x;
            this->y += b.y;
        }

        void operator+(glm::vec2& b) {
            this->x += b.x;
            this->y += b.y;
        }
    };


    struct Vector3 {

        float x, y, z;

        bool operator==(Vector3 &b) const {
            return (this->x == b.x && this->y == b.y && this->z == b.z);
        }

        Vector3& operator=(float val) {
            this->x = val;
            this->y = val;
            this->z = val;
            return *this;
        }


        void operator+=(Vector3 &b) {
            this->x += b.x;
            this->y += b.y;
            this->z += b.z;
        }


    };

    struct Quaternion {

        float x, y, z, w;

        bool operator==(Quaternion &b) const {
            return (this->x == b.x && this->y == b.y && this->z == b.z && this->w == b.w);
        }

        Quaternion& operator=(float val) {
            this->x = val;
            this->y = val;
            this->z = val;
            this->w = val;
            return *this;
        }

        void operator+(Quaternion &b) {
            this->x += b.x;
            this->y += b.y;
            this->z += b.z;
            this->w += b.z;
        }

        void sIdentity() {
            w = 1;
        }

    };

}



#endif //CATOS_MATH_H
