//
// Created by allos on 1/2/2025.
//
#pragma once


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

           _[3][0] = vec.x;
           _[3][1] = vec.y;
           _[3][2] = vec.z;

        }

        // Scales the Matrix according to the Vector2
        void scale(const Vector3& vec) {

            _[0][0] *= vec.x;
            _[1][1] *= vec.y;
            _[2][2] *= vec.z;

            _[3][3] = 1;
        }

        void rotate(float angle, const Vector3& v) {
            float const a = angle;
            float const c = cos(a);
            float const s = sin(a);

            Vector3 axis = normalize(v);
            Vector3 temp = axis * (1.0f - c);

            _[0][0] = c + temp.x * axis.x;
            _[0][1] = temp.x * axis.y + s * axis.z;
            _[0][2] = temp.x * axis.z - s * axis.y;

            _[1][0] = temp.y * axis.x - s * axis.z;
            _[1][1] = c + temp.y * axis.y;
            _[1][2] = temp.y * axis.z + s * axis.x;

            _[2][0] = temp.z * axis.x + s * axis.y;
            _[2][1] = temp.z * axis.y - s * axis.x;
            _[2][2] = c + temp.z * axis.z;
        }

        float* value_ptr() {
            return _[0];
        };
    };


    inline Matrix4 operator*(Matrix4& a, Matrix4& b) {
        Matrix4 result;

        int k, r, c;
        for (c = 0; c < 4; ++c) {
            for (r = 0; r < 4; ++r) {
                result[c][r] = 0.f;

                for (k = 0; k < 4; ++k) {
                    result[c][r] += a[k][r] * b[c][k];
                }
            }
        }

        return result;
    }

    static Matrix4 perspective(float fov, float aspect, float zNear, float zFar) {
        Matrix4 result{};

        float const tanHalfFov = tan(fov / 2);

        result[0][0] = 1 / (aspect * tanHalfFov);
        result[1][1] = 1 / tanHalfFov;
        result[2][2] = - (zFar + zNear) / (zFar - zNear);
        result[2][3] = - 1;
        result[3][2] = - (2 * zFar * zNear) / (zFar - zNear);

        return result;
    }

    static Matrix4 lookAt(const Vector3& eye, const Vector3& center,const Vector3& up) {
        Matrix4 result;

        Vector3 f = normalize(center - eye);
        Vector3 s = normalize(cross(f, up));
        Vector3 u = cross(s, f);

        result[0][0] = s.x;
        result[1][0] = s.y;
        result[2][0] = s.z;

        result[0][1] = u.x;
        result[1][1] = u.y;
        result[2][1] = u.z;

        result[0][2] = -f.x;
        result[1][2] = -f.y;
        result[2][2] = -f.z;

        result[3][0] = -dot(s, eye);
        result[3][1] = -dot(u, eye);
        result[3][2] = dot(f, eye);

        return result;
    }
}