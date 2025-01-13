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

        const float* value_ptr() const {
            return _[0];
        }
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

    inline Vector4 operator*(Matrix4& m, const Vector4& v) {
        Vector4 mov0{v[0]};
        Vector4 mov1{v[1]};
        Vector4 mul0 = Vector4{m[0][0], m[0][1], m[0][2], m[0][3]} * mov0;
        Vector4 mul1 =Vector4{m[1][0], m[1][1], m[1][2], m[1][3]}  * mov1;
        Vector4 add0 = mul0 + mul1;
        Vector4 mov2{v[2]};
        Vector4 mov3{v[3]};
        Vector4 mul2 = Vector4{m[2][0], m[2][1], m[2][2], m[2][3]} * mov2;
        Vector4 mul3 = Vector4{m[3][0], m[3][1], m[3][2], m[3][3]}  * mov3;
        Vector4 add1 = mul2 + mul3;
        Vector4 add2 = add0 + add1;
        return add2;
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

    static Matrix4 ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
        Matrix4 result;

        result[0][0] = 2 / (right - left);
        result[1][1] = 2 / (top - bottom);
        result[2][2] = -2 / (zFar - zNear);

        result[3][0] = -(right + left) / (right - left);
        result[3][1] = -(top + bottom) / (top - bottom);
        result[3][2] = -(zFar + zNear) / (zFar - zNear);

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


    //HUGE credits to: https://github.com/travisvroman/kohi/blob/main/kohi.core/src/math/kmath.h
    static Matrix4 inverse(Matrix4& matrix) {
        Matrix4 out{};

        float* m = matrix.value_ptr();

        float t0 = m[10] * m[15];
        float t1 = m[14] * m[11];
        float t2 = m[6] * m[15];
        float t3 = m[14] * m[7];
        float t4 = m[6] * m[11];
        float t5 = m[10] * m[7];
        float t6 = m[2] * m[15];
        float t7 = m[14] * m[3];
        float t8 = m[2] * m[11];
        float t9 = m[10] * m[3];
        float t10 = m[2] * m[7];
        float t11 = m[6] * m[3];
        float t12 = m[8] * m[13];
        float t13 = m[12] * m[9];
        float t14 = m[4] * m[13];
        float t15 = m[12] * m[5];
        float t16 = m[4] * m[9];
        float t17 = m[8] * m[5];
        float t18 = m[0] * m[13];
        float t19 = m[12] * m[1];
        float t20 = m[0] * m[9];
        float t21 = m[8] * m[1];
        float t22 = m[0] * m[5];
        float t23 = m[4] * m[1];

        float* o = out.value_ptr();

        o[0] = (t0 * m[5] + t3 * m[9] + t4 * m[13]) -
               (t1 * m[5] + t2 * m[9] + t5 * m[13]);
        o[1] = (t1 * m[1] + t6 * m[9] + t9 * m[13]) -
               (t0 * m[1] + t7 * m[9] + t8 * m[13]);
        o[2] = (t2 * m[1] + t7 * m[5] + t10 * m[13]) -
               (t3 * m[1] + t6 * m[5] + t11 * m[13]);
        o[3] = (t5 * m[1] + t8 * m[5] + t11 * m[9]) -
               (t4 * m[1] + t9 * m[5] + t10 * m[9]);

        float d = 1.0f / (m[0] * o[0] + m[4] * o[1] + m[8] * o[2] + m[12] * o[3]);

        o[0] = d * o[0];
        o[1] = d * o[1];
        o[2] = d * o[2];
        o[3] = d * o[3];
        o[4] = d * ((t1 * m[4] + t2 * m[8] + t5 * m[12]) -
                    (t0 * m[4] + t3 * m[8] + t4 * m[12]));
        o[5] = d * ((t0 * m[0] + t7 * m[8] + t8 * m[12]) -
                    (t1 * m[0] + t6 * m[8] + t9 * m[12]));
        o[6] = d * ((t3 * m[0] + t6 * m[4] + t11 * m[12]) -
                    (t2 * m[0] + t7 * m[4] + t10 * m[12]));
        o[7] = d * ((t4 * m[0] + t9 * m[4] + t10 * m[8]) -
                    (t5 * m[0] + t8 * m[4] + t11 * m[8]));
        o[8] = d * ((t12 * m[7] + t15 * m[11] + t16 * m[15]) -
                    (t13 * m[7] + t14 * m[11] + t17 * m[15]));
        o[9] = d * ((t13 * m[3] + t18 * m[11] + t21 * m[15]) -
                    (t12 * m[3] + t19 * m[11] + t20 * m[15]));
        o[10] = d * ((t14 * m[3] + t19 * m[7] + t22 * m[15]) -
                     (t15 * m[3] + t18 * m[7] + t23 * m[15]));
        o[11] = d * ((t17 * m[3] + t20 * m[7] + t23 * m[11]) -
                     (t16 * m[3] + t21 * m[7] + t22 * m[11]));
        o[12] = d * ((t14 * m[10] + t17 * m[14] + t13 * m[6]) -
                     (t16 * m[14] + t12 * m[6] + t15 * m[10]));
        o[13] = d * ((t20 * m[14] + t12 * m[2] + t19 * m[10]) -
                     (t18 * m[10] + t21 * m[14] + t13 * m[2]));
        o[14] = d * ((t18 * m[6] + t23 * m[14] + t15 * m[2]) -
                     (t22 * m[14] + t14 * m[2] + t19 * m[6]));
        o[15] = d * ((t22 * m[10] + t16 * m[2] + t21 * m[6]) -
                     (t20 * m[6] + t23 * m[10] + t17 * m[2]));

        return out;
    }
}