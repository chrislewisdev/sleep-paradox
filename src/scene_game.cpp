#include "scene_game.h"

#include "bn_keypad.h"

#include "bn_sprite_items_fred.h"
#include "bn_affine_bg_items_zone_classroom_floor.h"
#include "bn_affine_bg_items_zone_classroom_ceiling.h"

namespace sp {
    scene_game::scene_game(sp::scene_manager& _scene_manager)
        : scene_manager(_scene_manager),
          player(bn::sprite_items::fred),
          bg_layer_floor(bn::affine_bg_items::zone_classroom_floor.create_bg(0, 0)),
          bg_layer_ceiling(bn::affine_bg_items::zone_classroom_ceiling.create_bg(0, 0))
    {
        bg_layer_floor.set_priority(3);
        bg_layer_ceiling.set_priority(1);
    }

    void scene_game::update() {
        constexpr int pitch = 45;
        constexpr int scale = 1;
        constexpr int wall_height = 8;

        if (bn::keypad::left_held()) {
            camera_target.x -= 1;
        } else if (bn::keypad::right_held()) {
            camera_target.x += 1;
        }
        if (bn::keypad::up_held()) {
            camera_target.z += 1;
        } else if (bn::keypad::down_held()) {
            camera_target.z -= 1;
        }
        if (bn::keypad::l_held()) {
            if (heading == 0) heading = 359;
            else heading -= 1;
        } else if (bn::keypad::r_held()) {
            if (heading == 359) heading = 0;
            else heading += 1;
        }

        camera.update_camera(camera_target, pitch, heading, scale);

        vec3 bg_position = vec3::zero * camera.get_world_transform();
        bg_layer_floor.set_pivot_position(-bg_position.x, bg_position.z);
        bg_layer_ceiling.set_pivot_position(-bg_position.x, bg_position.z);
        bg_layer_ceiling.set_y(bn::degrees_lut_sin(pitch) * scale * -wall_height);

        bg_layer_floor.set_mat_attributes(camera.get_affine_transform_xz());
        bg_layer_ceiling.set_mat_attributes(camera.get_affine_transform_xz());

        //player.set_position(target);
        player.update(camera);
    }
}
