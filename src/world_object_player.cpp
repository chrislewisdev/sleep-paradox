#include "world_object_player.h"

#include "bn_keypad.h"

#include "world_state.h"
#include "world_camera.h"

#include "bn_sprite_items_fred_side_profile.h"

namespace sp {
    constexpr bn::fixed speed(1.5);

    world_object_player::world_object_player() :
        world_object(bn::sprite_items::fred_side_profile)
    {}

    void world_object_player::update(sp::world_state& world_state) {
        world_camera& camera = world_state.get_camera();
        const int heading = camera.get_heading();

        vec3 offset;
        if (bn::keypad::left_held()) {
            offset.z -= bn::degrees_lut_sin(heading) * speed;
            offset.x -= bn::degrees_lut_cos(heading) * speed;
        } else if (bn::keypad::right_held()) {
            offset.z += bn::degrees_lut_sin(heading) * speed;
            offset.x += bn::degrees_lut_cos(heading) * speed;
        }
        if (bn::keypad::up_held()) {
            offset.z += bn::degrees_lut_cos(heading) * speed;
            offset.x -= bn::degrees_lut_sin(heading) * speed;
        } else if (bn::keypad::down_held()) {
            offset.z -= bn::degrees_lut_cos(heading) * speed;
            offset.x += bn::degrees_lut_sin(heading) * speed;
        }

        vec3 new_position = position + offset;
        if (world_state.get_current_zone().get_ceiling_tile(new_position) == 0) {
            position = new_position;
        }

        world_object::update(world_state);
    }
}
