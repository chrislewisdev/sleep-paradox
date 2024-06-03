#pragma once

#include "bn_affine_mat_attributes.h"

#include "vec3.h"
#include "mat4.h"

namespace sp {
    class world_camera {
        private:
            vec3 position, direction;
            bn::fixed scale;
            mat4 world_transform;
            bn::affine_mat_attributes affine_transform_xz, affine_transform_xy, affine_transform_yz;

            void update_transform_xz(bn::fixed pitch, bn::fixed heading);
            void update_transform_xy(const vec3& right_axis, const vec3& up_axis);
            void update_transform_yz(const vec3& right_axis, const vec3& up_axis);

        public:
            const vec3& get_position() const;
            const mat4& get_world_transform() const;
            bn::fixed get_scale() const;
            const bn::affine_mat_attributes& get_affine_transform_xz() const;
            const bn::affine_mat_attributes& get_affine_transform_xy() const;
            const bn::affine_mat_attributes& get_affine_transform_yz() const;

            void update_camera(const vec3& target, bn::fixed pitch, bn::fixed heading, bn::fixed scale);
    };
}
