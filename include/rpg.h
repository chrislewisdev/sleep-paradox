#pragma once

namespace sp {
    class rpg_stats {
        public:
            rpg_stats() = default;
            constexpr rpg_stats(int h, int a, int d, int s) : max_health(h), attack(a), defence(d), speed(s) {}

            int max_health;
            int attack, defence;
            int speed;
    };

    constexpr rpg_stats player_base_stats(10, 5, 10, 5);

    int calculate_damage(const rpg_stats& attacker, const rpg_stats& target);
}
