#pragma once

#include "bn_vector.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_ptr.h"

#include "scene.h"
#include "scene_manager.h"

namespace sp {
    class scene_end : public scene {
        private:
            sp::scene_manager& scene_manager;
            sp::world_state& world_state;
            bn::vector<bn::sprite_ptr, 16> text_sprites;
            bn::regular_bg_ptr bg;

        public:
            scene_end(sp::scene_manager& scene_manager, sp::world_state& world_state);
            void update();
    };
}
