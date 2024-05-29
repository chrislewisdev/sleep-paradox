#pragma once

#include "bn_vector.h"
#include "bn_sprite_ptr.h"

#include "scene.h"
#include "scene_manager.h"

namespace sp {
    class scene_end : public scene {
        private:
            sp::scene_manager& scene_manager;
            bn::vector<bn::sprite_ptr, 16> text_sprites;
        public:
            scene_end(sp::scene_manager& scene_manager);
            void update();
    };
}
