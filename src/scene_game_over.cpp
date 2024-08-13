#include "scene_game_over.h"

#include "bn_sprite_text_generator.h"
#include "bn_keypad.h"

#include "common_variable_8x16_sprite_font.h"

namespace sp {
    scene_game_over::scene_game_over(sp::scene_manager& _scene_manager, sp::world_state& _world_state) :
        scene_manager(_scene_manager),
        world_state(_world_state)
    {
        bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
        text_generator.set_center_alignment();
        text_generator.generate(0, 0, "You died :(", text_sprites);
        text_generator.generate(0, 16, "Press A to respawn", text_sprites);
    }

    void scene_game_over::update() {
        if (bn::keypad::a_pressed()) {
            world_state.respawn();
            scene_manager.queue_scene_change(sp::scene_id::gameplay);
        }
    }
}

