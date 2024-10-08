#include "world_camera.h"

#include "mat2.h"

namespace sp {
    world_camera::world_camera() :
        pitch(45),
        base_heading(0),
        scale(1),
        affine_transform_ptr_xy(bn::sprite_affine_mat_ptr::create(affine_transform_xy)),
        affine_transform_ptr_yz(bn::sprite_affine_mat_ptr::create(affine_transform_yz))
    {}

    int world_camera::get_pitch() const { return pitch; }
    int world_camera::get_heading() const { return base_heading; }
    bn::fixed world_camera::get_scale() const { return scale; }

    const vec3& world_camera::get_position() const { return position; }
    const vec3& world_camera::get_direction() const { return direction; }
    const vec3& world_camera::get_right_axis() const { return right_axis; }

    const mat4& world_camera::get_world_transform() const { return world_transform; }

    const bn::affine_mat_attributes& world_camera::get_affine_transform_xz() const { return affine_transform_xz; }
    const bn::affine_mat_attributes& world_camera::get_affine_transform_xy() const { return affine_transform_xy; }
    const bn::affine_mat_attributes& world_camera::get_affine_transform_yz() const { return affine_transform_yz; }
    const bn::sprite_affine_mat_ptr& world_camera::get_affine_transform_ptr_xy() const { return affine_transform_ptr_xy; }
    const bn::sprite_affine_mat_ptr& world_camera::get_affine_transform_ptr_yz() const { return affine_transform_ptr_yz; }

    void world_camera::update_camera(const sp::vec3& target, int _pitch, int _heading, bn::fixed _scale) {
        pitch = _pitch;
        base_heading = _heading;
        scale = _scale;

        auto x_factor = base_heading == 0
            ? 1
            : base_heading == 180 ? -1 : 0;
        auto z_factor = base_heading == 90
            ? 1
            : base_heading == 270 ? -1 : 0;
        heading = base_heading - (target.x.integer() / 10 * x_factor) - (target.z.integer() / 10 * z_factor);
        if (heading < 0) heading += 360;
        if (heading > 360) heading -= 360;

        position = vec3(
            target.x + -bn::degrees_lut_sin(heading) * bn::degrees_lut_cos(pitch),
            target.y + bn::degrees_lut_sin(pitch),
            target.z + bn::degrees_lut_cos(heading) * bn::degrees_lut_cos(pitch)
        );

        // We could probably recalculate all these things only when pitch/heading changes...
        direction = normalise(target - position);

        right_axis = vec3(bn::degrees_lut_cos(heading), 0, bn::degrees_lut_sin(heading));

        vec3 up_axis(
            direction.x,
            bn::degrees_lut_sin(pitch),
            direction.z
        );

        world_transform = mat4(
            vec3(right_axis.x, up_axis.x, direction.x),
            vec3(right_axis.y, up_axis.y, direction.y),
            vec3(right_axis.z, up_axis.z, direction.z),
            // This was supposed to be the -position vector, but my maths must be off somehow because it wasn't working correctly
            // Instead we just apply the translation in world_object.cpp before transformation
            vec3::zero 
        );
        
        update_transform_xz();
        update_transform_xy(up_axis);
        update_transform_yz(up_axis);
    }

    vec3 world_camera::to_screen(const vec3& v) {
        return (v - position) * world_transform * scale;
    }

    void world_camera::update_transform_xz() {
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

    void world_camera::update_transform_xy(const vec3& up_axis) {
        auto scale_matrix = mat2::scale_inverse(scale + bn::fixed(0.05), scale);
        auto perspective_matrix = inverse(mat2(right_axis.x, right_axis.y, up_axis.x, up_axis.y));
        auto transform = scale_matrix * perspective_matrix;

        affine_transform_xy.unsafe_set_register_values(
            transform.a.data() >> 8,
            transform.b.data() >> 8,
            transform.c.data() >> 8,
            transform.d.data() >> 8
        );
        affine_transform_ptr_xy.set_attributes(affine_transform_xy);
    }

    void world_camera::update_transform_yz(const vec3& up_axis) {
        auto scale_matrix = mat2::scale_inverse(scale + bn::fixed(0.05), scale);
        auto perspective_matrix = inverse(mat2(right_axis.z, right_axis.y, up_axis.z, up_axis.y));
        auto transform = scale_matrix * perspective_matrix;

        affine_transform_yz.unsafe_set_register_values(
            transform.a.data() >> 8,
            transform.b.data() >> 8,
            transform.c.data() >> 8,
            transform.d.data() >> 8
        );
        affine_transform_ptr_yz.set_attributes(affine_transform_yz);
    }
}

