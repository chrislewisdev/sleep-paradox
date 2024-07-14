#include "bn_core.h"

#include "scene_manager.h"
#include "scene_title.h"

int main()
{
    bn::core::init();

    sp::world_state world_state;
    sp::scene_manager scene_manager(world_state);
    scene_manager.queue_scene_change(sp::scene_id::title);

    while(true)
    {
        scene_manager.process_scene_changes();
        scene_manager.update();
        bn::core::update();
    }
}
