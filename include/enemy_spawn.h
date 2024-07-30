#pragma once

#include "bn_core.h"

#include "enemy_type.h"

namespace sp {
	class enemy_spawn {
		public:
			const int16_t x;
			const int16_t y;
			const sp::enemy_type& enemy_type;
			constexpr enemy_spawn(uint16_t _x, uint16_t _y, const sp::enemy_type& _enemy_type): x(_x), y(_y), enemy_type(_enemy_type) {}
	};
}
