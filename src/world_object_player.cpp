#include "world_object_player.h"

#include "bn_keypad.h"

#include "world_state.h"
#include "world_camera.h"
#include "animations.h"

#include "bn_sprite_items_fred_sprite_sheet.h"

namespace sp {
    constexpr bn::fixed speed(2);

    world_object_player::world_object_player() :
        world_object(bn::sprite_items::fred_sprite_sheet)
    {
        use_animation("idle", animations::player::idle);
    }

    void world_object_player::update(sp::world_state& world_state) {
        world_camera& camera = world_state.get_camera();
        const int heading = camera.get_heading();

        // TODO: Fix increased diagonal speed
        vec3 offset;
        if (bn::keypad::left_held()) {
            offset.z -= bn::degrees_lut_sin(heading) * speed;
            offset.x -= bn::degrees_lut_cos(heading) * speed;
            sprite->set_horizontal_flip(true);
        } else if (bn::keypad::right_held()) {
            offset.z += bn::degrees_lut_sin(heading) * speed;
            offset.x += bn::degrees_lut_cos(heading) * speed;
            sprite->set_horizontal_flip(false);
        }
        if (bn::keypad::up_held()) {
            offset.z += bn::degrees_lut_cos(heading) * speed;
            offset.x -= bn::degrees_lut_sin(heading) * speed;
        } else if (bn::keypad::down_held()) {
            offset.z -= bn::degrees_lut_cos(heading) * speed;
            offset.x += bn::degrees_lut_sin(heading) * speed;
        }

        if (offset.x != 0 || offset.z != 0) {
            use_animation("run", animations::player::run);
        } else {
            use_animation("idle", animations::player::idle);
        }

        vec3 new_position = position + offset;
        if (world_state.get_current_zone().get_ceiling_tile(new_position) == 0) {
            position = new_position;
        }

        world_object::update(world_state);
    }
}
