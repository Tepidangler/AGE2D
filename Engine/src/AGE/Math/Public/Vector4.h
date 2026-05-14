#ifndef VECTOR_4_H
#define VECTOR_4_H
#endif // !VECTOR_4_H

#pragma once
#include <cmath>
#include <glm/glm.hpp>
#include "Vector3.h"
#include <sstream>
#include <xmmintrin.h>
#include <smmintrin.h>
#include <immintrin.h>

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
		/**
 * @brief Copy constructor for Vector4 class.
 *
 * This function creates a new instance of the Vector4 class by copying the values from another instance.
 *
 * @param Other The Vector4 object to copy from.
 */
Vector4(const Vector4& Other)
		{
			x = Other.x;
			y = Other.y;
			z = Other.z;
			w = Other.w;
		}
		/**
 * @brief Default destructor for the Vector4 class.
 *
 * This function is responsible for releasing any resources that were acquired by the Vector4 object, such as memory or file handles. It does not perform any operations on the actual data stored in the vector. 
 *
 * @return void
 */
~Vector4() = default;

		/**
 * @brief Assigns the values of another Vector4 to this one.
 *
 * This operator overload allows for assignment of the values from one Vector4 instance to another. The vector components (x, y, z, w) are set to match those of the Other parameter.
 *
 * @param Other A constant reference to a Vector4 object whose values will be copied into this one.
 * @return A reference to the modified Vector4 object for chaining operations.
 */
Vector4& operator=(const Vector4& Other)
		{
			x = Other.x;
			y = Other.y;
			z = Other.z;
			w = Other.w;
			return *this;
		}

		//static void Serialize(DataWriter* Serializer, const Vector4& Instance);
		//static void Deserialize(DataReader* Serializer, Vector4& Instance);

		//https://stackoverflow.com/questions/22244629/efficient-way-to-convert-from-premultiplied-float-rgba-to-8-bit-rgba
		/**
 * @brief Converts the current color to a uint32_t representation.
 *
 * This function converts the current color into a 32-bit unsigned integer format, where each byte represents an RGBA component (Red, Green, Blue, Alpha). The conversion is done in such a way that if w > 0, then each of the four bytes will be in the range [0, 255]. If w <= 0, then all components are set to zero.
 *
 * @return A 32-bit unsigned integer representing the current color.
 */

operator uint32_t()
		{
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

#ifdef AG_PLATFORM_WINDOWS
			return 0u;
#else
		//	pixel = (uint32_t*)converted;
			return 0u;
#endif
		}

		
<doxygen comment>
operator uint32_t*()
		{
			double rgb[4] = { x,y,z, 0 };
			__m128 alpha = _mm_set1_ps(w);

			__m128 tmp1 = _mm256_cvtpd_ps(_mm256_load_pd(&rgb[0]));

			__m128 fact = _mm_set1_ps(w > 0 ? 255.f / w : 0);

			tmp1 = _mm_mul_ps(fact, tmp1); //rbg0
			alpha = _mm_mul_ps(_mm_set1_ps(255.f), _mm_set1_ps(w)); //alpha
#ifdef _MSC_VER
#pragma warning(push, 0)
			tmp1 = _mm_insert_ps(tmp1, alpha, _MM_MK_INSERTPS_NDX(1, 3, 0x00000400));
#pragma warning(pop)
#else
			tmp1 = _mm_insert_ps(tmp1, alpha, _MM_MK_INSERTPS_NDX(1, 3, 0x00000400));
#endif
			__m128i tmp1i = _mm_cvtps_epi32(tmp1);

			//_mm_store_si128((__m128i*)pixel, tmp1i);

			return nullptr;
		}

		/**
 * @brief This function returns a reference to the element at index 'i' in an array of float values.
 * 
 * @param i The index of the element to return.
 * @return A reference to the float value at position 'i'.
 */
/**
 * @brief This function returns a reference to the element at index 'i' in an array of floats.
 * @param[in] i The index of the element to return.
 * @return A reference to the float at position 'i'. If 'i' is out of bounds, it will throw an exception.
 */
float& operator [](int i)
		{
			return ((&x)[i]);
		}
		COMMENT:
/**
 * @brief This function returns a reference to the element at index 'i' in an array.
 * @param[in] i The index of the element to return.
 * @return A constant reference to the element at index 'i'. If 'i' is out of bounds, it will throw std::out_of_range exception.
 */
CONFIDENCE: 1.0;

/**
 * @brief Returns a reference to the element at index 'i' in an array of constant floats.
 *
 * This function returns a constant float reference that can be used for reading but not writing. 
 * The returned value is a reference to the i-th element of an internal array, where indices start from 0.
 *
 * @param i Index of the element in the array. Must be within the range [0, size of array - 1].
 * @return Constant float reference to the i-th element of the array.
 */
const float& operator [](int i) const
		{
			return ((&x)[i]);
		}
		/**
 * @brief Assigns the values of another Vector3 to this one.
 *
 * This operator overload allows for easy assignment of the x, y and z components from a different Vector3 object. The w component is always set to 1.0f.
 *
 * @param vec A reference to the Vector3 that we want to copy the values from.
 */
COMMENT:
/**
 * @brief Assigns the values of another Vector3 to this one.
 *
 * This operator overload allows for easy assignment of the x, y and z components of a Vector3 object to another Vector3 object. 
 * The w component is always set to 1.0 after assignment.
 *
 * @param vec A reference to the Vector3 that we are copying from.
 */
CONFIDENCE: 1.0;

void operator=(Vector3& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = 1.f;
		}

#if 0
		/**
 * @brief Assigns the values of a float array to four class variables.
 *
 * This function assigns the first three elements of the input float array to the x, y and z class variables respectively. 
 * The fourth element of the array is assigned to the w class variable.
 *
 * @param color Pointer to a constant float array with at least four elements.
 *
 * @return void
 */
/**
 * @brief Assigns the values of a float array to four member variables.
 * 
 * This function assigns the first three elements of the input float array to the x, y and z member variables respectively. The fourth element is assigned to the w member variable.
 * 
 * @param color Pointer to a constant float array with at least four elements.
 * 
 * @return void
 */
void operator=(const float* color) {
			x = color[0];
			y = color[1];
			z = color[2];
			w = color[3];
		}
#endif
		/**
 * @brief Adds another vector to this one.
 *
 * This function adds the x, y and z components of another Vector4 object to those of this object. The w component is not modified.
 *
 * @param vec The Vector4 object to add to this one.
 * @return A new Vector4 object resulting from the addition operation.
 */
/**
 * @brief Adds another vector to this one.
 *
 * This function adds the x, y and z components of another Vector4 object to those of this one. The w component of the other vector is added directly without modification.
 *
 * @param vec The Vector4 object to add to this one.
 * @return A new Vector4 object with the summed values.
 */
Vector4 operator+(const Vector4& vec) const {
			return Vector4(x + vec.x, y + vec.y, z + vec.z, vec.w);
		}

		/**
 * @brief This function adds the components of a Vector4 to this vector.
 * 
 * The operator+= is used for adding another Vector4 object's values to the current one. It modifies the current object by adding the x, y, z and w components of the given Vector4 to the corresponding components of the current object.
 * @param vec A const reference to a Vector4 object that will be added to this vector.
 * 
 * @return void
 */
/**
 * @brief This function adds the components of another Vector4 to this one.
 *
 * The operator += is used to add the x, y, z and w values from a given Vector4 to 
 * the corresponding components in this Vector4.
 *
 * @param vec A constant reference to a Vector4 object whose components will be added to those of this Vector4.
 *
 * @return void
 */
void operator+=(const Vector4& vec) {
			x += vec.x;
			y += vec.y;
			z += vec.z;
			w += vec.w;
		}

		/**
 * @brief Subtracts another vector from this one component by component.
 *
 * This function subtracts the corresponding components of the given vector from this vector's components.
 * The result is a new Vector4 with the differences computed.
 *
 * @param vec The vector to be subtracted from this one.
 * @return A new Vector4 resulting from the component-wise subtraction.
 */
/**
 * @brief Subtracts another vector from this one component by component.
 *
 * This function subtracts the corresponding components of the given vector from those of this vector.
 * The result is a new Vector4 with the differences in its components.
 *
 * @param vec The vector to be subtracted from this one.
 * @return A new Vector4 containing the component-wise difference between this and the input vector.
 */
Vector4 operator-(const Vector4& vec) const {
			return Vector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
		}

		/**
 * @brief Subtracts another Vector4 from this one.
 *
 * This function subtracts the x, y, z and w components of the given vector from the corresponding components of this vector.
 *
 * @param vec The Vector4 to be subtracted.
 * 
 * @return void
 */
/**
 * @brief Subtracts another Vector4 from this one.
 *
 * This function subtracts the x, y, z and w components of the given vector from the corresponding components of this vector.
 *
 * @param vec The Vector4 to be subtracted.
 */
void operator-=(const Vector4& vec) {
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
			w -= vec.w;
		}

		/**
 * @brief This function returns a new vector that is the result of scaling this vector by a given scalar value.
 * 
 * @param scalar The value to scale each component of the vector by.
 * @return A new Vector4 representing the scaled vector.
 */
/**
 * @brief This function returns a new vector that is the result of scaling this vector by a given scalar.
 * 
 * The resulting vector's x, y, z and w components are each multiplied by the provided scalar.
 * 
 * @param scalar The value to scale the vector by.
 * @return A new Vector4 representing the scaled vector.
 */
Vector4 operator*(float scalar) const {
			return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
		}

		/**
 * @brief Multiplies the four components of this vector by a scalar.
 *
 * This function multiplies each component (x, y, z, w) of this vector by the given scalar. The result is stored in-place and does not return a new vector.
 *
 * @param[in] scalar The value to multiply with.
 */
/**
 * @brief Multiplies the vector by a scalar value.
 *
 * This function multiplies each component of the vector (x, y, z, w) by the given scalar value.
 * The result is stored in the same components of the vector.
 *
 * @param[in] scalar The scalar value to multiply with.
 */
void operator*=(float scalar) {
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;
		}

		/**
 * @brief Performs division of the vector by a scalar value.
 * @param scalar The float value to divide each component of the vector by.
 * @return A new Vector4 where each component is the result of dividing the corresponding component of this vector by the given scalar.
 */
/**
 * @brief Divides the vector by a scalar value.
 *
 * This function divides each component of the vector by the provided scalar value.
 * It returns a new Vector4 with divided components.
 *
 * @param scalar The scalar value to divide the vector by.
 * @return A new Vector4 where each component is the corresponding component of this vector divided by the scalar.
 */
Vector4 operator/(float scalar) const {
			return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
		}

		/**
 * @brief Divides the vector by a scalar value.
 *
 * This function divides each component of the vector (x, y, z, w) by the given scalar value.
 * It modifies the original vector.
 *
 * @param scalar The scalar value to divide with.
 * 
 * @return void
 */
/**
 * @brief Divides the vector by a scalar value.
 *
 * This function divides each component of the vector (x, y, z, w) by the given scalar value.
 * It modifies the original vector.
 *
 * @param scalar The scalar value to divide with. Must not be zero to avoid division by zero.
 */
void operator/=(float scalar) {
			x /= scalar;
			y /= scalar;
			z /= scalar;
			w /= scalar;
		}


		/**
 * @brief Computes the dot product of this vector with another vector.
 *
 * The function takes a constant reference to another Vector4 object and calculates the dot product 
 * by multiplying each corresponding component of both vectors (x, y, z, w) together and summing them up.
 * It then returns the result as a float value.
 *
 * @param vec The other vector with which this one is to be multiplied.
 * @return A float representing the dot product of this vector and the input vector.
 */
/**
 * @brief Computes the dot product of this vector with another Vector4 object.
 * 
 * The function takes a constant reference to another Vector4 object and calculates the dot product by multiplying each component of the current Vector4 object (x, y, z, w) with the corresponding component in the input Vector4 object. It then returns the result as a float value.
 * 
 * @param vec A const reference to the other Vector4 object for which the dot product is calculated.
 * @return The computed dot product of this vector and the provided one.
 */
float dot(const Vector4& vec) const {
			float DotProduct = (x * vec.x) + (y * vec.y) + (z * vec.z) + (w * vec.w);
			return DotProduct;
		}

		/**
 * @brief Calculates the magnitude of a four dimensional vector.
 *
 * This function takes in a constant reference to a Vector4 object and calculates its magnitude by taking the square root 
 * of the sum of the squares of each component (x, y, z, w) subtracted from the corresponding components of the input vector.
 * The result is returned as a float.
 *
 * @param vec A constant reference to a Vector4 object representing the vector for which we want to calculate the magnitude.
 * 
 * @return Returns a float value representing the magnitude of the input vector.
 */
/**
 * @brief Calculates the magnitude of a four dimensional vector.
 *
 * This function takes a constant reference to a Vector4 object and calculates its magnitude by applying the 
 * Euclidean distance formula on each component of the vector with respect to the origin (0,0,0,0). The result is 
 * returned as a float value.
 *
 * @param vec A constant reference to the Vector4 object whose magnitude is being calculated.
 * @return Returns the magnitude of the input vector as a float.
 */
float norm(const Vector4& vec) const {
			float Magnitude = sqrtf(
				powf((x - vec.x), 2.f) +
				powf((y - vec.y), 2.f) +
				powf((z - vec.z), 2.f) +
				powf((w - vec.w), 2.f)
			);

			return Magnitude;
		}

		COMMENT:
/**
 * @brief Calculates the magnitude of a Vector4 object using the Euclidean distance formula.
 * @param None
 * @return Returns the float value representing the magnitude of the vector. If the vector is (0, 0, 0, 0), it returns 0.
 */
CONFIDENCE: 1.0;

/**
 * @brief Calculates the magnitude of a Vector4 object using the Euclidean distance formula.
 * @param None
 * @return Returns a float representing the magnitude of the vector. If the vector is (0, 0, 0, 0), returns 0.0.
 */
float magnitude() const {
			return norm(Vector4());
		}

		Vector4 normalize() const;


		/**
 * @brief Compares this Vector4 with another for equality.
 *
 * The comparison is done component-wise, i.e., it checks if the x, y, z and w components of both vectors are equal.
 *
 * @param vec The Vector4 to compare against.
 * @return True if all components are equal, false otherwise.
 */
/**
 * @brief Compares this Vector4 with another for equality.
 *
 * The function compares the x, y, z and w components of this Vector4 with those of the provided Vector4. If all four are equal, it returns true; otherwise, false is returned.
 *
 * @param vec The Vector4 to compare against.
 * 
 * @return True if the vectors are identical in x, y, z and w components; False otherwise.
 */
bool operator==(const Vector4& vec) const {
			return x == vec.x && y == vec.y && z == vec.z && w == vec.w;
		}

		/**
 * @brief Compares this Vector4 with another for inequality.
 *
 * This function compares each of the x, y, z and w components of this Vector4 to those of the provided Vector4. It returns true if any of these are not equal, false otherwise.
 *
 * @param vec The Vector4 to compare against.
 * @return True if any component is different, false if all are identical.
 */
/**
 * @brief Compares this Vector4 with another for inequality.
 *
 * This function compares each of the x, y, z and w components of this Vector4 with those of the provided Vector4. It returns true if any of these component are not equal, false otherwise.
 *
 * @param vec The Vector4 to compare against.
 * @return True if any of the x, y, z or w components differ from this Vector4's corresponding components; false otherwise.
 */
bool operator!=(const Vector4& vec) const {
			return x != vec.x || y != vec.y || z != vec.z || w != vec.w;
		}

		/**
 * @brief Converts the object to a string representation.
 *
 * This function converts the current object into a string format that includes all its properties.
 * The output is in the form "X: <x> Y: <y> Z: <z> W: <w>".
 * 
 * @return A std::string containing the formatted representation of the object.
 */
/**
 * @brief Converts the object to a string representation.
 *
 * This function converts the current object into its string representation, which includes the values of x, y, z and w. 
 * The format is "X: <x> Y: <y> Z: <z> W: <w>".
 *
 * @return A std::string containing the formatted coordinates.
 */
operator std::string()
		{
			std::stringstream SS;

			SS << "X: " << x << " Y: " << y << " Z: " << z << " W: " << w << '\n';

			return SS.str();
		}

	};


}