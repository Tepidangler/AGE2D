#include "AGEpch.hpp"
#include "Math/Public/Vector2.h"

namespace AGE {
	/**
 * @brief Default constructor for the Vector2 class. Initializes x and y to zero.
 */
Vector2::Vector2() {
		x = 0;
		y = 0;
	}
	/**
 * @brief Constructs a Vector2 object with given x and y coordinates.
 * 
 * @param a The x-coordinate of the vector.
 * @param b The y-coordinate of the vector.
 */
Vector2::Vector2(float a, float b) {
		x = a;
		y = b;
	}
	/**
 * @brief Constructs a Vector2 object with both x and y components set to the same value.
 * 
 * @param a The value to be assigned to both x and y.
 */
Vector2::Vector2(float a) {
		x = a;
		y = a;
	}

	/**
 * @brief Normalizes this vector.
 *
 * This function calculates the unit vector (a vector with a length of 1) in the same direction as this vector. If the magnitude of this vector is zero, it returns a vector at origin.
 *
 * @return A new Vector2 object representing the normalized version of this vector.
 */
Vector2 Vector2::normalize() const {
		float magnitude = this->magnitude();
		if (magnitude == 0) {
			return Vector2(0, 0);
		}

		return Vector2(x, y) / magnitude;
	}

}