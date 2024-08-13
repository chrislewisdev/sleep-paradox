#include "scene_manager.h"

#include "scene_title.h"
#include "scene_game.h"
#include "scene_pause.h"
#include "scene_end.h"
#include "scene_game_over.h"

namespace sp {
    scene_manager::scene_manager(sp::world_state& _world_state) : world_state(_world_state) {}

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
                    stack.push_back(bn::make_unique<sp::scene_game>(*this, world_state));
                    break;
                case sp::scene_id::pause:
                    stack.push_back(bn::make_unique<sp::scene_pause>(*this, world_state));
                    break;
                case sp::scene_id::end:
                    stack.push_back(bn::make_unique<sp::scene_end>(*this));
                    break;
                case sp::scene_id::game_over:
                    stack.push_back(bn::make_unique<sp::scene_game_over>(*this, world_state));
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
