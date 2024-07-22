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

    int get_xp_for_level_up(int level);

    int calculate_base_player_health(int level);
    int get_player_health_growth(int level);

    int calculate_base_player_attack(int level);
    int get_player_attack_growth(int level);

    int calculate_base_player_defence(int level);
    int get_player_defence_growth(int level);

    int calculate_base_player_speed(int level);
    int get_player_speed_growth(int level);

    int calculate_damage(const rpg_stats& attacker, const rpg_stats& target);
}
