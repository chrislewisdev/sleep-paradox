#pragma once

#include "world_object.h"
#include "rpg.h"
#include "interactable.h"
#include "item.h"

namespace sp {
    class world_object_player : public world_object {
        private:
            vec3 get_movement_input(bn::fixed heading);
            void trigger_attack(sp::world_state& world_state);
            void update_fx();
            bool apply_xp(int amount);
            bn::optional<const interactable*> get_interactable(sp::world_state& world_state);

            int level, xp;
            rpg_stats stats;
            int health;
            int facing = 1;
            int attack_cooldown = 0;
            bn::optional<bn::sprite_ptr> attack_fx;
            bn::optional<world_object_animation> attack_fx_animation;
            bn::optional<bn::sprite_ptr> interaction_callout;
            bn::vector<sp::item_id, 16> inventory;

        public:
            world_object_player();

            const rpg_stats& get_stats() const;

            void update(sp::world_state& world_state);
            void receive_attack(sp::world_state& world_state, const rpg_stats& attacker);
            void grant_item(sp::item_id item_id);
    };
}
