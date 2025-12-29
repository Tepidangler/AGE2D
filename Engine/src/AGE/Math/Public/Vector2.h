#ifndef VECTOR2_H
#define VECTOR2_H
#endif // !VECTOR2_H

#include <cmath>

#include <sstream>
#pragma once

namespace AGE {
	struct Vector2
	{
	public:
		
		float x, y;
		

		Vector2();
		Vector2(float a);
		Vector2(float a, float b);

		float dot(const Vector2& vec) const {
			float product = (x * vec.x) + (y * vec.y);
			return product;
		}

		float norm(const Vector2& vec) const {
			float magnitude = sqrt(pow((x - vec.x), 2.f) + pow((y - vec.y), 2.f));

			return magnitude;
		}

		float magnitude() const {
			return norm(Vector2());
		}

		Vector2 normalize() const;

		float& operator [](int i)
		{
			return ((&x)[i]);
		}

		const float& operator [](int i) const
		{
			return ((&x)[i]);
		}

		Vector2 operator+(const Vector2& vec) const {
			return Vector2(x + vec.x, y + vec.y);
		}

		void operator+=(const Vector2& vec) {
			x += vec.x;
			y += vec.y;
		}

		Vector2 operator-(const Vector2& vec) const {
			return Vector2(x - vec.x, y - vec.y);
		}

		void operator-=(const Vector2& vec) {
			x -= vec.x;
			y -= vec.y;
		}

		Vector2 operator*(float scalar) const {
			return Vector2(x * scalar, y * scalar);
		}

		void operator*=(float scalar) {
			x *= scalar;
			y *= scalar;
		}

		Vector2 operator/(float scalar) const {
			return Vector2(x / scalar, y / scalar);
		}

		void operator/=(float scalar) {
			x /= scalar;
			y /= scalar;
		}

		bool operator==(const Vector2& vec) const {
			return x == vec.x && y == vec.y;
		}

		bool operator!=(const Vector2& vec) const {
			return x != vec.x || y != vec.y;
		}

		operator std::string()
		{
			std::stringstream SS;

			SS << "X: " << x << " Y: " << y << '\n';

			return SS.str();
		}
	};


}


