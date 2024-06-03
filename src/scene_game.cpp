#include "scene_game.h"

#include "bn_keypad.h"

#include "bn_sprite_items_fred_side_profile.h"
#include "bn_sprite_items_bully01_side_profile.h"
#include "bn_sprite_items_bully02_side_profile.h"
#include "bn_affine_bg_items_zone_classroom_floor.h"
#include "bn_affine_bg_items_zone_classroom_ceiling.h"

namespace sp {
    scene_game::scene_game(sp::scene_manager& _scene_manager)
        : scene_manager(_scene_manager),
          bg_layer_floor(bn::affine_bg_items::zone_classroom_floor.create_bg(0, 0)),
          bg_layer_ceiling(bn::affine_bg_items::zone_classroom_ceiling.create_bg(0, 0))
    {
        bg_layer_floor.set_priority(3);
        bg_layer_floor.set_wrapping_enabled(false);
        bg_layer_ceiling.set_priority(1);
        bg_layer_ceiling.set_wrapping_enabled(false);

        objects.push_back(world_object(bn::sprite_items::fred_side_profile));
        objects.push_back(world_object(bn::sprite_items::bully01_side_profile));
        objects.push_back(world_object(bn::sprite_items::bully02_side_profile));
    }

    void scene_game::update() {
        constexpr int pitch = 45;
        constexpr int scale = 1;
        constexpr int wall_height = 8;

        vec3 position = objects[0].get_position();
        if (bn::keypad::left_held()) {
            position.z -= bn::degrees_lut_sin(heading);
            position.x -= bn::degrees_lut_cos(heading);
        } else if (bn::keypad::right_held()) {
            position.z += bn::degrees_lut_sin(heading);
            position.x += bn::degrees_lut_cos(heading);
        }
        if (bn::keypad::up_held()) {
            position.z += bn::degrees_lut_cos(heading);
            position.x -= bn::degrees_lut_sin(heading);
        } else if (bn::keypad::down_held()) {
            position.z -= bn::degrees_lut_cos(heading);
            position.x += bn::degrees_lut_sin(heading);
        }
        if (bn::keypad::r_held()) {
            if (heading == 0) heading = 359;
            else heading -= 1;
        } else if (bn::keypad::l_held()) {
            if (heading == 359) heading = 0;
            else heading += 1;
        }

        camera.update_camera(position, pitch, heading, scale);

        vec3 bg_position = (vec3::zero - camera.get_position()) * camera.get_world_transform();
        bg_layer_floor.set_position(bg_position.x, bg_position.z);
        bg_layer_ceiling.set_position(bg_position.x, bg_position.z + bn::degrees_lut_sin(pitch) * scale * -wall_height);

        bg_layer_floor.set_mat_attributes(camera.get_affine_transform_xz());
        bg_layer_ceiling.set_mat_attributes(camera.get_affine_transform_xz());

        objects[0].set_position(position);
        objects[1].set_position(vec3(-48, 16, 48));
        objects[2].set_position(vec3(48, 16, 48));
        //objects[1].set_position(vec3(bn::degrees_lut_sin(timer) * 50, 0, bn::degrees_lut_sin(timer) * 50));
        //objects[2].set_position(vec3(0, 0, bn::degrees_lut_sin(timer) * 50));

        for (auto object : objects) {
            object.update(camera);
        }

        timer = (timer + 1) % 360;
    }
}
