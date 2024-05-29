#include "scene_title.h"

#include "bn_sprite_text_generator.h"

#include "common_variable_8x16_sprite_font.h"

namespace sp {
    scene_title::scene_title(sp::scene_manager& _scene_manager)
        : scene_manager(_scene_manager)
    {
        bn::sprite_text_generator text_gen(common::variable_8x16_sprite_font);
        text_gen.set_center_alignment();

        text_gen.generate(0, -50, "Sleep Paradox", text_sprites);
        text_gen.generate(0, -8, "Title scene", text_sprites);
        text_gen.generate(0, 30, "Press A to start", text_sprites);
    }

    void scene_title::update() {}
}
