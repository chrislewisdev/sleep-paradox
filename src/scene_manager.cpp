#include "scene_manager.h"

#include "scene_title.h"
#include "scene_game.h"
#include "scene_end.h"

namespace sp {
    void scene_manager::queue_scene_change(sp::scene_id scene_id) {
        queued_scene_id = scene_id;
    }

    void scene_manager::process_scene_changes() {
        if (queued_scene_id.has_value()) {
            if (!stack.empty()) stack.pop_back();

            switch (queued_scene_id.value()) {
                case sp::scene_id::title:
                    stack.push_back(bn::make_unique<sp::scene_title>(*this));
                    break;
                case sp::scene_id::gameplay:
                    stack.push_back(bn::make_unique<sp::scene_game>(*this));
                    break;
                case sp::scene_id::end:
                    stack.push_back(bn::make_unique<sp::scene_end>(*this));
                    break;
                default:
                    BN_ERROR("Unknown scene id ", (int)queued_scene_id.value());
            }

            queued_scene_id.reset();
        }
    }

    void scene_manager::update() {
        stack.back()->update();
    }
}
