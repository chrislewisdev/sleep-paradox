#pragma once

#include "bn_vector.h"
#include "bn_sprite_ptr.h"

#include "scene.h"
#include "scene_manager.h"

namespace sp {
    class scene_title : public scene {
        private:
            sp::scene_manager& scene_manager;
            bn::vector<bn::sprite_ptr, 16> text_sprites;
        public:
            scene_title(sp::scene_manager& _scene_manager);
            void update();
    };
}

