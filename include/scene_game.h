#pragma once

#include "bn_vector.h"
#include "bn_affine_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"

#include "scene.h"
#include "scene_manager.h"
#include "world_state.h"

namespace sp {
    class scene_game : public scene {
        private:
            sp::scene_manager& scene_manager;
            sp::world_state& world_state;
            bn::affine_bg_ptr bg_layer_floor, bg_layer_ceiling;
            bn::sprite_text_generator text_generator;
            bn::vector<bn::sprite_ptr, 4> hud_health_sprites;
            int target_heading = 0;

        public:
            scene_game(sp::scene_manager& _scene_manager, sp::world_state& _world_state);
            void update();
    };
}

