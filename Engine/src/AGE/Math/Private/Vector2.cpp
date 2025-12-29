#include "AGEpch.hpp"
#include "Math/Public/Vector2.h"

namespace AGE {
	Vector2::Vector2() {
		x = 0;
		y = 0;
	}
	Vector2::Vector2(float a, float b) {
		x = a;
		y = b;
	}
	Vector2::Vector2(float a) {
		x = a;
		y = a;
	}

	Vector2 Vector2::normalize() const {
		float magnitude = this->magnitude();
		if (magnitude == 0) {
			return Vector2(0, 0);
		}

		return Vector2(x, y) / magnitude;
	}

}