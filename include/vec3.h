#pragma once

#include "bn_core.h"

namespace sp {
    class vec3 {
        public:
            bn::fixed_t<16> x, y, z;

            static vec3 zero, up, right, forward;

            vec3() {}
            vec3(bn::fixed _x, bn::fixed _y, bn::fixed _z) : x(_x), y(_y), z(_z) {}

            bn::fixed magnitude() const {
                return bn::sqrt(x*x + y*y + z*z);
            }

            bn::fixed dot(const vec3& rhs) const {
                return x*rhs.x + y*rhs.y + z*rhs.z;
            }

            vec3 cross(const vec3& rhs) const {
                return vec3(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
            }
    };

    vec3 vec3::zero;
    vec3 vec3::right(1, 0, 0);
    vec3 vec3::up(0, 1, 0);
    vec3 vec3::forward(0, 0, 1);

    vec3 operator+(const vec3& lhs, const vec3& rhs) {
        return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }

    vec3 operator-(const vec3& lhs, const vec3& rhs) {
        return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }

    vec3 operator*(const vec3& lhs, const bn::fixed& rhs) {
        return vec3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
    }

    vec3 operator/(const vec3& lhs, const bn::fixed& rhs) {
        return vec3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
    }

    vec3 operator-(const vec3& lhs) {
        return vec3(-lhs.x, -lhs.y, -lhs.z);
    }

    vec3 normalise(const vec3& v) {
        return v / v.magnitude();
    }
}

