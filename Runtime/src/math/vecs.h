//
// Created by allos on 5/16/2024.
//
#pragma once

#include <cmath>

namespace catos::math {

    struct Vector2i {

        Vector2i() = default;
        Vector2i(float _x, float _y) {
            x = _x;
            y = _y;
        }

        float x = 0.0f;
        float y = 0.0f;
    };

    struct Vector2: public Vector2i {

        Vector2(): Vector2i() {};
        Vector2(float x, float y): Vector2i(x, y) {};

        // DO NOT TOUCH
        float _[2] = { 0.0f, 0.0f };

        float getX() const {
            return x;
        }

        float getY() const {
            return y;
        }

        bool operator==(Vector2& b) {
            return (this->x == b.x && this->y == b.y);
        }

        void operator+(Vector2& b) {
            this->x += b.x;
            this->y += b.y;
        }

        void operator=(const Vector2& b) {
            x = b.getX();
            y = b.getY();
        }

        float* value_ptr() {
            _[0] = x;
            _[1] = y;
            return &_[0];
        }

    };

    struct Vector3i {

        Vector3i() = default;
        Vector3i(float _x, float _y, float _z) {
            x = _x;
            y = _y;
            z = _z;
        }

        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    };

    struct Vector3: public Vector3i {
        Vector3() = default;

        Vector3(float x, float y, float z) : Vector3i(x, y, z) {
            _[0] = x;
            _[1] = y;
            _[2] = z;
        }

        // DO NOT TOUCH!
        float _[3] = {0.0f, 0.0f, 0.0f};

        float getX() const {
            return x;
        }

        float getY() const {
            return y;
        }

        float getZ() const {
            return z;
        }

        bool operator==(const Vector3 &b) const {
            return (this->x == b.x && this->y == b.y && this->z == b.z);
        }

        Vector3& operator=(float val) {
            this->x = val;
            this->y = val;
            this->z = val;
            return *this;
        }

        void operator=(const Vector3i& b) {
            x = b.x;
            y = b.y;
            z = b.z;
        }

        Vector3 operator*(float v) const {
            return Vector3{x * v, y * v, z * v};
        }

        Vector3 operator*(const Vector3& v) const {
            return Vector3{x * v.x, y * v.y, z * v.z};
        }

        Vector3 operator-(const Vector3& b) const {
            return {x - b.x, y - b.y, z - b.z};
        }

        Vector3 operator+(const Vector3& b) const {
            return Vector3{x + b.x, y + b.y, z + b.z};
        }

        void operator+=(const Vector3 &b) {
            this->x += b.x;
            this->y += b.y;
            this->z += b.z;
        }

        void operator/=(float v) {
            x /= v;
            y /= v;
            z /= v;
        }

        float* value_ptr() {
            _[0] = x;
            _[1] = y;
            _[2] = z;
            return &_[0];
        }

    };

    static Vector3 normalize(const Vector3& v) {
        float a = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

        return Vector3{v.x / a, v.y / a, v.z / a};
    }

    static Vector3 cross(const Vector3& a, const Vector3& b) {
        return Vector3{
           a.y * b.z - b.y * a.z,
           a.z * b.x - b.z * a.x,
           a.x * b.y - b.x * a.y
        };
    }

    static float dot(const Vector3& a,const Vector3& b) {
        Vector3 temp = a * b;

        return temp.x + temp.y + temp.z;
    }

    struct Vector4i {

        Vector4i() = default;

        Vector4i(float _x, float _y, float _z, float _w) {
            x = _x;
            y = _y;
            z = _z;
            w = _w;
        }

        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float w = 0.0f;
    };

    struct Vector4: public Vector4i {

        Vector4(float x, float y, float z, float w): Vector4i(x, y, z, w) {
            _[0] = x;
            _[1] = y;
            _[2] = z;
            _[3] = w;
        };

        Vector4(float val): Vector4i(val, val, val, val) {
            _[0] = x;
            _[1] = y;
            _[2] = z;
            _[3] = w;
        }

        Vector4() = default;

        //Our internal buffer.
        float _[4] = {0.0f, 0.0f, 0.0f, 0.0f};


        float getX() const {
            return x;
        }

        float getY() const {
            return y;
        }

        float getZ() const {
            return z;
        }

        float getW() const {
            return z;
        }

        // Returns the begin of our internal buffer.
        // Meant for opengl uniforms
        float* value_ptr() {
            _[0] = x;
            _[1] = y;
            _[2] = z;
            _[3] = w;

            return &_[0];
        }


        float operator[](int index)const {
            return _[index];
        }

        float operator[](int index)  {
            _[0] = x;
            _[1] = y;
            _[2] = z;
            _[3] = w;

            return _[index];
        }

        Vector4 operator*(float v) {
            return {x  * v, y * v, z * v, w * v};
        }

        Vector4 operator*(const Vector4& v) const {
            return {x  * v.x, y * v.y, z * v.z, w * v.w};
        }

        Vector4 operator+(const Vector4& v) const {
            return {x + v.x, y +  v.x, z + v.z, w +  v.w};
        }

        Vector4 operator/(float val) const {
            return {x / val, y / val, z / val, w / val};
        }

    };


    template<typename T>
    static T toRadians(T degrees) {
        return degrees * static_cast<T>(0.01745329251994329576923690768489);;
    }


    template<typename T>
    static T fma(const T& a,const T& b,const T& c) {
        return a + b * c;
    }

}