#include "world_object_player.h"

#include "bn_keypad.h"
#include "bn_sprite_animate_actions.h"

#include "world_state.h"
#include "world_camera.h"

#include "bn_sprite_items_fred_sprite_sheet.h"

namespace sp {
    constexpr bn::fixed speed(2);

    bn::sprite_animate_action<10> idle_animation(const bn::sprite_ptr& sprite) {
        return bn::create_sprite_animate_action_forever(
            sprite,
            30,
            bn::sprite_items::fred_sprite_sheet.tiles_item(),
            9, 10
        );
    }

    bn::sprite_animate_action<10> run_animation(const bn::sprite_ptr& sprite) {
        return bn::create_sprite_animate_action_forever(
            sprite,
            5,
            bn::sprite_items::fred_sprite_sheet.tiles_item(),
            0, 1, 2, 3, 4, 5
        );
    }

    bn::sprite_animate_action<10> blink_animation(const bn::sprite_ptr sprite) {
        return bn::create_sprite_animate_action_once(
            sprite,
            20,
            bn::sprite_items::fred_sprite_sheet.tiles_item(),
            7, 8
        );
    }

    world_object_player::world_object_player() :
        world_object(bn::sprite_items::fred_sprite_sheet)
    {
        use_animation("idle", idle_animation);
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
            use_animation("run", run_animation);
        } else {
            use_animation("idle", idle_animation);
        }

        vec3 new_position = position + offset;
        if (world_state.get_current_zone().get_ceiling_tile(new_position) == 0) {
            position = new_position;
        }

        world_object::update(world_state);
    }
}
