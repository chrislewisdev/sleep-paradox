#include "rpg.h"

#include "bn_core.h"

namespace sp {
    int get_xp_for_level_up(int level) {
        return level * 10;
    }

    int calculate_base_player_health(int level) {
        return 8 + level * 2;
    }
    int get_player_health_growth(int level) {
        return calculate_base_player_health(level) - calculate_base_player_health(level - 1);
    }

    int calculate_base_player_attack(int level) {
        bn::fixed exponential_factor = bn::fixed(level) * level / 10;
        return 4 + level + exponential_factor.floor_integer();
    }
    int get_player_attack_growth(int level) {
        return calculate_base_player_attack(level) - calculate_base_player_attack(level - 1);
    }

    int calculate_base_player_defence(int level) {
        return 8 + level;
    }
    int get_player_defence_growth(int level) {
        return calculate_base_player_defence(level) - calculate_base_player_defence(level - 1);
    }

    int calculate_base_player_speed(int level) {
        bn::fixed increment = bn::fixed(level) * 3 / 2;
        return 5 + increment.floor_integer();
    }
    int get_player_speed_growth(int level) {
        return calculate_base_player_speed(level) - calculate_base_player_speed(level - 1);
    }

    int calculate_damage(const rpg_stats& attacker, const rpg_stats& target) {
        bn::fixed dmg = bn::fixed(attacker.attack) / (bn::fixed(target.defence * 10 + 100) / 100);
        return dmg.integer();
    }
}
