#pragma once

#include "bn_string_view.h"

namespace sp {
    enum class item_id : uint8_t {
        potion,
        strength_boost,
        defence_boost,
    };

    class world_object_player;
    using item_effect = void (*)(sp::world_object_player& player);

    void item_effect_potion(sp::world_object_player& player);
    void item_effect_strength_boost(sp::world_object_player& player);
    void item_effect_defence_boost(sp::world_object_player& player);

    class item {
        public:
            constexpr item(bn::string_view _name, bn::string_view _description, item_effect _effect)
                : name(_name), description(_description), effect(_effect)
            {}

            const bn::string_view name, description;
            const item_effect effect;
    };

    constexpr item items[] = {
        item("Potion", "Restores 20 health.", item_effect_potion),
        item("Strength Mod", "Permanently increases your strength by 2.", item_effect_strength_boost),
        item("Defence Mod", "Permanently increases your defence by 1.", item_effect_defence_boost),
    };
}

