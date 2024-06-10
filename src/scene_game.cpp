#include "scene_game.h"

#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_rect_window.h"
#include "bn_sprite_text_generator.h"
#include "bn_bg_palette_ptr.h"
#include "bn_sprite_palette_ptr.h"

#include "bn_affine_bg_items_zone_sandbox_floor.h"
#include "bn_affine_bg_items_zone_sandbox_ceiling.h"
#include "common_variable_8x16_sprite_font.h"
#include "bn_sprite_items_portrait.h"
#include "bn_sprite_items_fred_side_profile.h"
#include "bn_sprite_items_wall_placeholder.h"

namespace sp {
    scene_game::scene_game(sp::scene_manager& _scene_manager)
        : scene_manager(_scene_manager),
          bg_layer_floor(world_state.get_current_zone().floor.create_bg(0, 0)),
          bg_layer_ceiling(world_state.get_current_zone().ceiling.create_bg(0, 0)),
          portrait_sprite_upper(bn::sprite_items::portrait.create_sprite(-70, -28)),
          portrait_sprite_lower(bn::sprite_items::portrait.create_sprite(-70, 36, 1))
    {
        bg_layer_floor.set_priority(3);
        bg_layer_floor.set_wrapping_enabled(false);
        bg_layer_ceiling.set_priority(1);
        bg_layer_ceiling.set_wrapping_enabled(false);

        bn::rect_window rect_window = bn::rect_window::external();
        rect_window.set_boundaries(
            28 - (bn::display::height() / 2),
            -bn::display::width() / 2,
            (bn::display::height() / 2) - 60,
            bn::display::width() / 2
        );

        bn::window outside_window = bn::window::outside();
        outside_window.set_show_bg(bg_layer_floor, false);
        outside_window.set_show_bg(bg_layer_ceiling, false);
        // outside_window.set_show_sprites(false);

        bn::sprite_text_generator text_gen(common::variable_8x16_sprite_font);

        text_gen.generate(-114, 30, "Fredericko", text_sprites);
        text_gen.generate(-110, 46, "Something is seriously wrong here.", text_sprites);
        text_gen.generate(-110, 58, "I need to escape!", text_sprites);

        bn::optional<bn::bg_palette_ptr> bg_pal = bn::bg_palette_ptr::find(world_state.get_current_zone().floor.palette_item());
        bg_pal->set_fade_intensity(bn::fixed(0.4));
        bn::optional<bn::sprite_palette_ptr> sprite_pal = bn::sprite_palette_ptr::find(bn::sprite_items::fred_side_profile.palette_item());
        sprite_pal->set_fade_intensity(bn::fixed(0.4));
        bn::optional<bn::sprite_palette_ptr> sprite_pal2 = bn::sprite_palette_ptr::find(bn::sprite_items::wall_placeholder.palette_item());
        sprite_pal2->set_fade_intensity(bn::fixed(0.4));
    }

    void scene_game::update() {
        constexpr int wall_height = 32;
        constexpr int pitch = 45;
        constexpr bn::fixed scale = 1;

        world_camera& camera = world_state.get_camera();
        int heading = camera.get_heading();
        if (bn::keypad::r_held()) {
            if (heading == 0) heading = 359;
            else heading -= 1;
        } else if (bn::keypad::l_held()) {
            if (heading == 359) heading = 0;
            else heading += 1;
        }

        // This order of operations is a little messed up because there is a circular dependency between
        // player position -> camera position -> sprite screen position
        // We can solve this by splitting update/draw into separate cycles but for now at least, let's just see how we go
        camera.update_camera(world_state.get_player().get_position(), pitch, heading, scale);
        world_state.update();

        vec3 bg_position = -camera.get_position() * camera.get_world_transform();
        bg_layer_floor.set_position(bg_position.x, bg_position.z);
        bg_layer_ceiling.set_position(bg_position.x, bg_position.z + bn::degrees_lut_sin(pitch) * camera.get_scale() * -wall_height);

        bg_layer_floor.set_mat_attributes(camera.get_affine_transform_xz());
        bg_layer_ceiling.set_mat_attributes(camera.get_affine_transform_xz());

    }
}
