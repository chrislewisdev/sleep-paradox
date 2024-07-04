#include "rpg.h"

#include "bn_core.h"

namespace sp {
    rpg_stats::rpg_stats(int h, int a, int d, int s)
        : max_health(h), attack(a), defence(d), speed(s)
    {}

    int calculate_damage(const rpg_stats& attacker, const rpg_stats& target) {
        bn::fixed dmg = bn::fixed(attacker.attack) / (bn::fixed(target.defence * 10 + 100) / 100);
        return dmg.integer();
    }
}
