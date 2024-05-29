#pragma once

#include "bn_deque.h"
#include "bn_unique_ptr.h"
#include "bn_optional.h"

#include "scene.h"

namespace sp {
    class scene_manager {
        private:
            bn::deque<bn::unique_ptr<sp::scene>, 4> stack;
            bn::optional<scene_id> queued_scene_id;
        public:
            void queue_scene_change(sp::scene_id scene_id);
            void process_scene_changes();
            void update();
    };
}

