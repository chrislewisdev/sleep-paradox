#include "scene_end.h"

#include "bn_sprite_text_generator.h"

#include "common_variable_8x16_sprite_font.h"

namespace sp {
    scene_end::scene_end(sp::scene_manager& _scene_manager, sp::world_state& _world_state)
        : scene_manager(_scene_manager), world_state(_world_state)
    {
        bn::sprite_text_generator text_gen(common::variable_8x16_sprite_font);
        text_gen.set_center_alignment();

        text_gen.generate(0, -8, "The end!", text_sprites);
        text_gen.generate(0, 8, "Thanks for playing :3", text_sprites);

        world_state.cleanup();
    }

    void scene_end::update() {}
}
