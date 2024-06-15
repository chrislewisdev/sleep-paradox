#pragma once

namespace sp {
    class rpg_stats {
        public:
            rpg_stats() = default;
            rpg_stats(int h, int a, int d, int s);

            int max_health;
            int attack, defence;
            int speed;
    };

    int calculate_damage(const rpg_stats& attacker, const rpg_stats& target);
}
