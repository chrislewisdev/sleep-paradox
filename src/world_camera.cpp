#include "world_camera.h"

#include "mat2.h"

namespace sp {
    const mat4& world_camera::get_world_transform() const {
        return world_transform;
    }

    const bn::affine_mat_attributes& world_camera::get_affine_transform_xz() const {
        return affine_transform_xz;
    }

    const bn::affine_mat_attributes& world_camera::get_affine_transform_xy() const {
        return affine_transform_xy;
    }

    const bn::affine_mat_attributes& world_camera::get_affine_transform_yz() const {
        return affine_transform_yz;
    }

    void world_camera::update_camera(const sp::vec3& target, bn::fixed pitch, bn::fixed heading, bn::fixed scale) {
        position = vec3(
            target.x + -bn::degrees_lut_sin(heading) * bn::degrees_lut_cos(pitch),
            target.y + bn::degrees_lut_sin(pitch),
            target.z + bn::degrees_lut_cos(heading) * bn::degrees_lut_cos(pitch)
        );

        direction = normalise(target - position);

        vec3 right_axis(bn::degrees_lut_cos(heading), 0, bn::degrees_lut_sin(heading));

        vec3 up_axis(
            direction.x,
            bn::degrees_lut_sin(pitch),
            direction.z
        );

        world_transform = mat4(
            vec3(right_axis.x, up_axis.x, direction.x),
            vec3(right_axis.y, up_axis.y, direction.y),
            vec3(right_axis.z, up_axis.z, direction.z),
            -position
        );
        
        update_transform_xz(pitch, heading, scale);
        update_transform_xy(right_axis, up_axis, scale);
        update_transform_yz(right_axis, up_axis, scale);
    }

    void world_camera::update_transform_xz(bn::fixed pitch, bn::fixed heading, bn::fixed scale) {
        auto rotation_matrix = mat2::rotate_inverse(heading);
        auto scale_matrix = mat2::scale_inverse(scale, scale * bn::degrees_lut_cos(pitch));
        auto transform = rotation_matrix * scale_matrix;

        affine_transform_xz.unsafe_set_register_values(
            transform.a.data() >> 8,
            transform.b.data() >> 8,
            transform.c.data() >> 8,
            transform.d.data() >> 8
        );
    }

    void world_camera::update_transform_xy(const vec3& right_axis, const vec3& up_axis, bn::fixed scale) {
        auto scale_matrix = mat2::scale_inverse(scale + bn::fixed(0.05), scale * bn::fixed(0.55));
        auto perspective_matrix = inverse(mat2(right_axis.x, right_axis.y, up_axis.x, up_axis.y));
        auto transform = scale_matrix * perspective_matrix;

        affine_transform_xy.unsafe_set_register_values(
            transform.a.data() >> 8,
            transform.b.data() >> 8,
            transform.c.data() >> 8,
            transform.d.data() >> 8
        );
    }

    void world_camera::update_transform_yz(const vec3& right_axis, const vec3& up_axis, bn::fixed scale) {
        auto scale_matrix = mat2::scale_inverse(scale + bn::fixed(0.05), scale * bn::fixed(0.55));
        auto perspective_matrix = inverse(mat2(right_axis.z, right_axis.y, up_axis.z, up_axis.y));
        auto transform = scale_matrix * perspective_matrix;

        affine_transform_yz.unsafe_set_register_values(
            transform.a.data() >> 8,
            transform.b.data() >> 8,
            transform.c.data() >> 8,
            transform.d.data() >> 8
        );
    }
}

