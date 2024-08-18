#pragma once

#include "bn_regular_bg_ptr.h"

#include "scene.h"
#include "scene_manager.h"

namespace sp {

    class scene_title : public scene {
        private:
            sp::scene_manager& scene_manager;
            bn::regular_bg_ptr bg;
            int timer = 240;
        public:
            scene_title(sp::scene_manager& _scene_manager);
            void update();
    };
}

