#ifndef VECTOR3_H
#define VECTOR3_H
#endif // !VECTOR3_H

#pragma once
#include <cmath>
#include <glm/glm.hpp>
#include <sstream>
#include <rttr/type>

namespace AGE {

	struct Vector4;
	struct Vector2;

	struct Vector3
	{
	public:
		
		
		float x, y, z;
		

		Vector3();
		Vector3(float a);
		Vector3(float a, float b, float c);
		Vector3(Vector2 a, float c);
		Vector3(glm::vec3 v);
		Vector3(Vector4 v);

		float& operator [](int i)
		{
			return ((&x)[i]);
		}
		const float& operator [](int i) const
		{
			return ((&x)[i]);
		}

		Vector3 operator+(const Vector3& vec) const {
			return Vector3(x + vec.x, y + vec.y, z + vec.z);
		}

		void operator+=(const Vector3& vec) {
			x += vec.x;
			y += vec.y;
			z += vec.z;
		}

		Vector3 operator-(const Vector3& vec) const {
			return Vector3(x - vec.x, y - vec.y, z - vec.z);
		}

		void operator-=(const Vector3& vec) {
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
		}

		Vector3 operator*(float scalar) const {
			return Vector3(x * scalar, y * scalar, z * scalar);
		}

		//Vector3 Vector3::operator*(Vector3 s)
		//{
		//	return Vector3(x * s.x, y * s.y, z * s.z);
		//}
		void operator*=(float scalar) {
			x *= scalar;
			y *= scalar;
			z *= scalar;
		}

		Vector3 operator/(float scalar) const {
			return Vector3(x / scalar, y / scalar, z / scalar);
		}

		void operator/=(float scalar) {
			x /= scalar;
			y /= scalar;
			z /= scalar;
		}

		Vector3 normalize() const;

		float dot(const Vector3& vec) const {
			float DotProduct = (x * vec.x) + (y * vec.y) + (z * vec.z);
			return DotProduct;
		}
		
		Vector3 cross(const Vector3& vec) const {
			struct Vector3 CrossProduct;
			CrossProduct.x = (y * vec.z) - (z * vec.y);
			CrossProduct.y = (z * vec.x) - (x * vec.z);
			CrossProduct.z = (x * vec.y) - (y * vec.x);

			return CrossProduct;
		}

		float norm(const Vector3& vec) const {
			float Magnitude = sqrt(
				pow((x - vec.x), 2.f) +
				pow((y - vec.y), 2.f) +
				pow((z - vec.z), 2.f)
			);

			return Magnitude;
		}

		float magnitude() const {
			return norm(Vector3());
		}
		bool operator==(Vector3 vec) const {
			return (x == vec.x && y == vec.y && z == vec.z);
		}
		bool operator==(const Vector3& vec) const {
			return (x == vec.x && y == vec.y && z == vec.z);
		}

		bool operator!=(const Vector3& vec) {
			return (x != vec.x || y != vec.y || z != vec.z);
		}

		operator std::string()
		{
			std::stringstream SS;

			SS << "X: " << x << " Y: " << y << " Z: " << z << '\n';

			return SS.str();
		}
	};

	inline Vector3 operator*(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
	}


}