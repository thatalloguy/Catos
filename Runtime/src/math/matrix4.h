//
// Created by allos on 1/2/2025.
//
#pragma once


#include <cmath>
#include "vecs.h"

namespace catos::math {

    struct Matrix4 {

        float _[4][4] = {
                {1.f, 0.f, 0.f, 0.f},
                {0.f, 1.f, 0.f, 0.f},
                {0.f, 0.f, 1.f, 0.f},
                {0.f, 0.f, 0.f, 1.f}
        };

        //Returns the array of the given row (index)
        float* operator[](int index) {
            return _[index];
        }

        // translates the Matrix according to the Vector2
        void translate(const Vector3& vec) {

            Vector4 m1 = {_[0][0] * vec[0], _[0][1] * vec[0], _[0][1] * vec[0], _[0][3]};
            // translate the y dimension
            Vector4 m2 = {_[1][0] * vec[1], _[1][1] * vec[1], _[1][2] * vec[1], _[1][3]};
            //Keep the Z dimension the same since its a 2d game.
            Vector4 m3 = {_[2][0] * vec[2], _[2][1] * vec[2], _[2][2] * vec[2], _[2][3]};


            Vector4 m4 = {_[3][0], _[3][1], _[3][2], _[3][3]};

            //Calc the result
            Vector4 result = m1 + m2 + m3 + m4;

            //Apply the result to our internal data.
            _[3][0] = result[0];
            _[3][1] = result[1];
            _[3][2] = result[2];
            _[3][3] = result[3];

        }

        // Scales the Matrix according to the Vector2
        void scale(const Vector3& vec) {

            //Scale the X dimension
            Vector4 m1 = {_[0][0] * vec[0], _[0][1] * vec[0], _[0][1] * vec[0], _[0][3]};
            //Scale the Y dimension
            Vector4 m2 = {_[1][0] * vec[0], _[1][1] * vec[1], _[1][2] * vec[1], _[1][3]};
            // Scale the Z dimension
            Vector4 m3 = {_[2][0] * vec[0], _[2][1] * vec[1], _[2][2] * vec[1], _[2][3]};

            //Apply our results to the internal buffer.
            _[0][0] = m1[0];
            _[0][1] = m1[1];
            _[0][2] = m1[2];
            _[0][3] = m1[3];

            _[1][0] = m2[0];
            _[1][1] = m2[1];
            _[1][2] = m2[2];
            _[1][3] = m2[3];

            _[2][0] = m3[0];
            _[2][1] = m3[1];
            _[2][2] = m3[2];
            _[2][3] = m3[3];

        }

        void rotate(float angle, const Vector3& v) {
            float const a = angle;
            float const c = cos(a);
            float const s = sin(a);

            Vector3 axis = normalize(v);
            Vector3 temp = axis * (1.0f - c);

            _[0][0] = c + temp[0] * axis[0];
            _[0][1] = temp[0] * axis[1] + s * axis[2];
            _[0][2] = temp[0] * axis[2] - s * axis[1];

            _[1][0] = temp[1] * axis[0] - s * axis[2];
            _[1][1] = c + temp[1] * axis[1];
            _[1][2] = temp[1] * axis[2] + s * axis[0];

            _[2][0] = temp[2] * axis[0] + s * axis[1];
            _[2][1] = temp[2] * axis[1] - s * axis[0];
            _[2][2] = c + temp[2] * axis[2];
        }

        float* value_ptr() {
            return _[0];
        };
    };

}