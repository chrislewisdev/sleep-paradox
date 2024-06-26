#include "scene_end.h"

#include "bn_sprite_text_generator.h"

#include "common_variable_8x16_sprite_font.h"

namespace sp {
    scene_end::scene_end(sp::scene_manager& _scene_manager)
        : scene_manager(_scene_manager)
    {
        bn::sprite_text_generator text_gen(common::variable_8x16_sprite_font);
        text_gen.set_center_alignment();

        text_gen.generate(0, -8, "End scene", text_sprites);
    }

    void scene_end::update() {}
}
