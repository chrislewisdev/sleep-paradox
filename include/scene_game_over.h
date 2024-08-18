#pragma once

#include "bn_vector.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_ptr.h"

#include "scene.h"
#include "scene_manager.h"
#include "world_state.h"

namespace sp {
    class scene_game_over : public scene {
        private:
            sp::scene_manager& scene_manager;
            sp::world_state& world_state;
            bn::vector<bn::sprite_ptr, 24> text_sprites;
            bn::regular_bg_ptr bg;
 
        public:
            scene_game_over(sp::scene_manager& _scene_manager, sp::world_state& _world_state);

            void update();
    };
}

