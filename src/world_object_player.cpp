#include "world_object_player.h"

#include "bn_keypad.h"

#include "bn_sprite_items_fred_side_profile.h"

namespace sp {
    world_object_player::world_object_player() :
        world_object(bn::sprite_items::fred_side_profile)
    {}

    void world_object_player::update(const world_camera& camera) {
        const int heading = camera.get_heading();
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

        world_object::update(camera);
    }
}
