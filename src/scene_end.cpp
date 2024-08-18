#include "scene_end.h"

#include "bn_sprite_text_generator.h"

#include "common_variable_8x16_sprite_font.h"
#include "bn_regular_bg_items_end.h"

namespace sp {
    scene_end::scene_end(sp::scene_manager& _scene_manager, sp::world_state& _world_state)
        : scene_manager(_scene_manager), world_state(_world_state), bg(bn::regular_bg_items::end.create_bg(0, 0))
    {
        bn::sprite_text_generator text_gen(common::variable_8x16_sprite_font);
        text_gen.set_center_alignment();

        text_gen.generate(70, -60, "The end.", text_sprites);

        world_state.cleanup();
    }

    void scene_end::update() {}
}
