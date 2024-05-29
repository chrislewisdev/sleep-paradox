#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "scene.h"
#include "scene_manager.h"

namespace sp {
    class scene_title : public scene {
        private:
            sp::scene_manager& scene_manager;
        public:
            scene_title(sp::scene_manager& _scene_manager);
            void update();
    };
}

#endif
