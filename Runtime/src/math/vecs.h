//
// Created by allos on 5/16/2024.
//
#pragma once

#include <cmath>

namespace catos::math {


    struct Vector2 {

        float _[2] = { 0.0f, 0.0f };

        float& x() {
            return _[0];
        }
        float& y() {
            return _[1];
        }

        float x() const {
            return _[0];
        }
        float y() const {
            return _[1];
        }


        float operator[](int index) const {
            return _[index];
        }

        bool operator==(Vector2& b) {
            return (this->x() == b.x() && this->y() == b.y());
        }

        void operator+(Vector2& b) {
            this->x() += b.x();
            this->y() += b.y();
        }

    };

    struct Vector3 {

        Vector3(float x, float y, float z) {
            _[0] = x;
            _[1] = y;
            _[2] = z;
        }

        float _[3] = {0.0f, 0.0f, 0.0f};

        float& x() {
            return _[0];
        }
        float& y() {
            return _[1];
        }
        float& z() {
            return _[2];
        }


        float x() const{
            return _[0];
        }
        float y() const {
            return _[1];
        }
        float z() const {
            return _[2];
        }



        float operator[](int index) const {
            return _[index];
        }

        bool operator==(Vector3 &b) {
            return (this->x() == b.x() && this->y() == b.y() && this->z() == b.z());
        }

        Vector3& operator=(float val) {
            this->x() = val;
            this->y() = val;
            this->z() = val;
            return *this;
        }

        Vector3 operator*(float v) {
            return Vector3{_[0] * v, _[1] * v, _[2] * v};
        }


        void operator+=(Vector3 &b) {
            this->x() += b.x();
            this->y() += b.y();
            this->z() += b.z();
        }

        float* value_ptr() {
            return &_[0];
        }
    };

    static Vector3 normalize(const Vector3& v) {
        float a = sqrt((v.x() * v.x()) + (v.y() * v.y()) + (v.z() + v.z()));

        return Vector3{v.x() / a, v.y() / a, v.z() / a};
    }

    struct Vector4 {

        Vector4(float x, float y, float z, float w) {
            _[0] = x;
            _[1] = y;
            _[2] = z;
            _[3] = w;
        };

        Vector4() = default;

        //Our internal buffer.
        float _[4] = {0.0f, 0.0f, 0.0f, 0.0f};

        //Returns the value of the given axis.
        float operator[](int index) const {
            return _[index];
        }

        float& operator[](int index) {
            return _[index];
        }

        // Returns the begin of our internal buffer.
        // Meant for opengl uniforms
        float* value_ptr() {
            return &_[0];
        }

        Vector4 operator*(float v) {
            return {_[0] * v, _[1] * v, _[2] * v, _[3] * v};
        }

        Vector4 operator+(Vector4 v) {
            return {_[0] + v[0], _[1] + v[1], _[2] + v[2], _[3] + v[3]};
        }

    };


    template<typename T>
    static T toRadians(T degrees) {
        return degrees * static_cast<T>(0.01745329251994329576923690768489);;
    }
}