#include "scene_game.h"

#include "bn_keypad.h"
#include "bn_backdrop.h"
#include "bn_color.h"
#include "bn_format.h"
#include "bn_bg_palette_ptr.h"
#include "bn_log.h"

#include "advikku_global.h"
#include "institutionalised.h"
#include "fyingde.h"
#include "zones.h"

#include "common_variable_8x8_sprite_font.h"
#include "bn_affine_bg_items_zone_sandbox_floor.h"
#include "bn_affine_bg_items_zone_sandbox_ceiling.h"

namespace sp {
    scene_game::scene_game(sp::scene_manager& _scene_manager, sp::world_state& _world_state)
        : scene_manager(_scene_manager),
          world_state(_world_state),
          bg_layer_floor(world_state.get_current_zone().floor.create_bg(0, 0)),
          bg_layer_ceiling(world_state.get_current_zone().ceiling.create_bg(0, 0)),
          text_generator(common::variable_8x8_sprite_font)
    {
        world_state.set_visible(true);

        bg_layer_floor.set_priority(3);
        bg_layer_floor.set_wrapping_enabled(false);
        bg_layer_ceiling.set_priority(1);
        bg_layer_ceiling.set_wrapping_enabled(false);

        text_generator.set_bg_priority(0);

        if (world_state.is_final_zone()) cell_song_setup(FyingDeSongStruct);
        else cell_song_setup(InstitutionalisedSongStruct);
    }

    void scene_game::update() {
        constexpr int wall_height = 32;
        constexpr int pitch = 45;
        constexpr bn::fixed scale = 1.4;

        world_camera& camera = world_state.get_camera();
        int heading = camera.get_heading();
        /*if (bn::keypad::r_held()) {
            if (heading == 0) heading = 359;
            else heading -= 1;
        } else if (bn::keypad::l_held()) {
            if (heading == 359) heading = 0;
            else heading += 1;
        }*/
        if (bn::keypad::l_pressed()) {
            if (target_heading == 0) target_heading = 90;
            else if (target_heading == 90) target_heading = 180;
            else if (target_heading == 180) target_heading = 270;
            else if (target_heading == 270) target_heading = 360;
        }
        if (heading < target_heading) heading += 5;
        // Gotta wrap back around to 0 after a full rotation...
        if (target_heading == 360 && heading == 360) {
            target_heading = 0;
            heading = 0;
        }

        /*if (bn::keypad::start_pressed()) {
            scene_manager.queue_scene_change(sp::scene_id::pause);
            world_state.set_visible(false);
        }*/

        if (world_state.get_player().get_health() <= 0) {
            scene_manager.queue_scene_change(sp::scene_id::game_over);
            world_state.set_visible(false);
        }

        if (world_state.is_zone_change_queued()) {
            world_state.process_zone_change();

            bg_layer_floor = world_state.get_current_zone().floor.create_bg(0, 0);
            bg_layer_ceiling = world_state.get_current_zone().ceiling.create_bg(0, 0);

            bg_layer_floor.set_priority(3);
            bg_layer_floor.set_wrapping_enabled(false);
            //bg_layer_floor.set_palette(world_state.get_current_zone().floor.palette_item().create_new_palette());
            auto palette = bg_layer_floor.palette();
            palette.set_colors(world_state.get_current_zone().floor.palette_item());
            bg_layer_ceiling.set_priority(1);
            bg_layer_ceiling.set_wrapping_enabled(false);
            //bg_layer_ceiling.set_palette(world_state.get_current_zone().ceiling.palette_item());
        }
        // When the final boss is killed, go to the ending scene...
        if (world_state.is_final_zone() && !world_state.get_boss()) {
            scene_manager.queue_scene_change(sp::scene_id::end);
            world_state.set_visible(false);
        }

        // This order of operations is a little messed up because there is a circular dependency between
        // player position -> camera position -> sprite screen position
        // We can solve this by splitting update/draw into separate cycles but for now at least, let's just see how we go
        camera.update_camera(world_state.get_player().get_position(), pitch, heading, scale);
        world_state.update();

        vec3 bg_position = -camera.get_position() * camera.get_world_transform() * scale;
        bg_layer_floor.set_position(bg_position.x, bg_position.z);
        bg_layer_ceiling.set_position(bg_position.x, bg_position.z + bn::degrees_lut_sin(pitch) * camera.get_scale() * -wall_height);

        bg_layer_floor.set_mat_attributes(camera.get_affine_transform_xz());
        bg_layer_ceiling.set_mat_attributes(camera.get_affine_transform_xz());

        auto& player = world_state.get_player();
        auto text = bn::format<16>("HP: {}/{}", player.get_health(), player.get_stats().max_health);
        hud_health_sprites = text_generator.generate<4>(-118, 72, text);
    }
}
