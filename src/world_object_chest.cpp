#include "world_object_chest.h"

#include "world_state.h"

#include "bn_sprite_items_chest.h"
#include "bn_sprite_items_chest_open.h"

namespace sp {
    world_object_chest::world_object_chest(const vec3& _position, sp::item_id _item_id) :
        world_object(bn::sprite_items::chest),
        item_id(_item_id)
    {
        position = _position;
    }

    vec3 world_object_chest::get_position() const { return position; }
    bool world_object_chest::get_is_opened() const { return is_opened; }

    void world_object_chest::interact(sp::world_state& world_state) const {
        if (!is_opened) world_state.activate_chest(*this);
    }

    void world_object_chest::activate(sp::world_state& world_state) {
        world_state.get_player().grant_item(item_id);
        is_opened = true;

        if (sprite) sprite->set_tiles(bn::sprite_items::chest_open.tiles_item());
    }
}

