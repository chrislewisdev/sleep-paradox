#include "scene_game_over.h"

#include "bn_sprite_text_generator.h"
#include "bn_keypad.h"

#include "advikku_global.h"
#include "nocando.h"

#include "common_variable_8x16_sprite_font.h"
#include "bn_regular_bg_items_game_over.h"

namespace sp {
    scene_game_over::scene_game_over(sp::scene_manager& _scene_manager, sp::world_state& _world_state) :
        scene_manager(_scene_manager),
        world_state(_world_state),
        bg(bn::regular_bg_items::game_over.create_bg(0, 0))
    {
        bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
        text_generator.set_center_alignment();
        text_generator.generate(0, 70, "Press A to respawn", text_sprites);

        cell_song_setup(No_Can_DoSongStruct);
    }

    void scene_game_over::update() {
        if (bn::keypad::a_pressed()) {
            world_state.respawn();
            scene_manager.queue_scene_change(sp::scene_id::gameplay);
        }
    }
}

