#ifndef VECTOR_4_H
#define VECTOR_4_H
#endif // !VECTOR_4_H

#pragma once
#include <cmath>
#include <glm/glm.hpp>
#include "Vector3.h"
#include <sstream>

namespace AGE {
	struct Vector4
	{
	public:
		
		float x, y, z, w;
		Vector4();
		Vector4(float a);
		Vector4(glm::vec4 vec);
		Vector4(float a, float b, float c, float d);
		Vector4(uint8_t a, uint8_t b, uint8_t c, uint8_t d);
		Vector4(const float* color);

		//static void Serialize(DataWriter* Serializer, const Vector4& Instance);
		//static void Deserialize(DataReader* Serializer, Vector4& Instance);


#pragma warning(push, 0)
		//https://stackoverflow.com/questions/22244629/efficient-way-to-convert-from-premultiplied-float-rgba-to-8-bit-rgba
		operator uint32_t()
		{
			//TODO: Temp need to fix because Clang and MSVC treat this type differently so this solution won't work. Instead I'll probably just pack the uint32_t.
			//double rgb[4] = { x,y,z, 0};
			//__m128 alpha = _mm_set1_ps(w);
			//__m128i* converted = new __m128i();
			//
			//__m128 tmp1 = _mm256_cvtpd_ps(_mm256_load_pd(&rgb[0]));
			//
			//__m128 fact = _mm_set1_ps(w > 0 ? 255.f / w: 0);
			//
			//tmp1 = _mm_mul_ps(fact, tmp1); //rbg0
			//alpha = _mm_mul_ps(_mm_set1_ps(255.f), _mm_set1_ps(w)); //alpha
			//tmp1 = _mm_insert_ps(tmp1, alpha, _MM_MK_INSERTPS_NDX(1,3, 0x00000400));
			//
			//__m128i tmp1i = _mm_cvtps_epi32(tmp1);
			//
			//_mm_store_si128((__m128i*)converted, tmp1i);
			//uint32_t out = converted->m128i_u32[0] | (converted->m128i_u32[1] << 8) | (converted->m128i_u32[2] << 16) | (converted->m128i_u32[3] << 24);
			uint32_t out = 0x00000000;

			return out;
		}

		operator uint32_t*()
		{
			//TODO: Temp need to fix because Clang and MSVC treat this type differently so this solution won't work. Instead I'll probably just pack the uint32_t.
			//double rgb[4] = { x,y,z, 0 };
			//__m128 alpha = _mm_set1_ps(w);
			//uint32_t out[4];
//
			//__m128 tmp1 = _mm256_cvtpd_ps(_mm256_load_pd(&rgb[0]));
//
			//__m128 fact = _mm_set1_ps(w > 0 ? 255.f / w : 0);
//
			//tmp1 = _mm_mul_ps(fact, tmp1); //rbg0
			//alpha = _mm_mul_ps(_mm_set1_ps(255.f), _mm_set1_ps(w)); //alpha
			//tmp1 = _mm_insert_ps(tmp1, alpha, _MM_MK_INSERTPS_NDX(1, 3, 0x00000400));
//
			//__m128i tmp1i = _mm_cvtps_epi32(tmp1);
//
			//_mm_store_si128((__m128i*)out, tmp1i);
//
			uint32_t out[4] = {0,0,0,0};
			return out;
		}
#pragma warning(pop)

		float& operator [](int i)
		{
			return ((&x)[i]);
		}
		const float& operator [](int i) const
		{
			return ((&x)[i]);
		}
		void operator=(Vector3& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = 1.f;
		}

#if 0
		void operator=(const float* color) {
			x = color[0];
			y = color[1];
			z = color[2];
			w = color[3];
		}
#endif
		Vector4 operator+(const Vector4& vec) const {
			return Vector4(x + vec.x, y + vec.y, z + vec.z, vec.w);
		}

		void operator+=(const Vector4& vec) {
			x += vec.x;
			y += vec.y;
			z += vec.z;
			w += vec.w;
		}

		Vector4 operator-(const Vector4& vec) const {
			return Vector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
		}

		void operator-=(const Vector4& vec) {
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
			w -= vec.w;
		}

		Vector4 operator*(float scalar) const {
			return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
		}

		void operator*=(float scalar) {
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;
		}

		Vector4 operator/(float scalar) const {
			return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
		}

		void operator/=(float scalar) {
			x /= scalar;
			y /= scalar;
			z /= scalar;
			w /= scalar;
		}


		float dot(const Vector4& vec) const {
			float DotProduct = (x * vec.x) + (y * vec.y) + (z * vec.z) + (w * vec.w);
			return DotProduct;
		}

		float norm(const Vector4& vec) const {
			float Magnitude = sqrt(
				pow((x - vec.x), 2.f) +
				pow((y - vec.y), 2.f) +
				pow((z - vec.z), 2.f) +
				pow((w - vec.w), 2.f)
			);

			return Magnitude;
		}

		float magnitude() const {
			return norm(Vector4());
		}

		Vector4 normalize() const;


		bool operator==(const Vector4& vec) const {
			return x == vec.x && y == vec.y && z == vec.z && w == vec.w;
		}

		bool operator!=(const Vector4& vec) const {
			return x != vec.x || y != vec.y || z != vec.z || w != vec.w;
		}

		operator std::string()
		{
			std::stringstream SS;

			SS << "X: " << x << " Y: " << y << " Z: " << z << " W: " << w << '\n';

			return SS.str();
		}

	};


}