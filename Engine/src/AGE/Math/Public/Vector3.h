#ifndef VECTOR3_H
#define VECTOR3_H
#endif // !VECTOR3_H

#pragma once
#include <cmath>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <sstream>

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

		/**
 * @brief This function returns a reference to the element at index 'i' in an array of float numbers.
 * @param[in] i The index of the element to return.
 * @return A reference to the element at index 'i'. If 'i' is out of bounds, it will throw an exception.
 */
float& operator [](int i)
		{
			return ((&x)[i]);
		}
		/**
 * @brief This function returns a reference to the element at index 'i' in an array.
 * @param[in] i The index of the element to return.
 * @return A constant reference to the element at index 'i'. If 'i' is out of bounds, it will throw an exception.
 */
const float& operator [](int i) const
		{
			return ((&x)[i]);
		}
		/**
 * @brief Adds two vectors together component-wise.
 *
 * This function takes another vector as an argument and adds its components to the current vector's components. The result is a new Vector3 object with the sum of the x, y, and z coordinates.
 *
 * @param vec A constant reference to another Vector3 object whose components will be added to this one.
 * @return A new Vector3 object resulting from adding the x, y, and z components of the two vectors together.
 */
Vector3 operator+(const Vector3& vec) const {
			return Vector3(x + vec.x, y + vec.y, z + vec.z);
		}

		/**
 * @brief This function adds the components of a Vector3 to the current vector.
 * 
 * @param vec The Vector3 to add to this one.
 */
void operator+=(const Vector3& vec) {
			x += vec.x;
			y += vec.y;
			z += vec.z;
		}

		/**
 * @brief Subtracts another vector from this one and returns the result.
 * @param vec The Vector3 to subtract from this instance.
 * @return A new Vector3 that is the difference between this instance and the provided Vector3.
 */
Vector3 operator-(const Vector3& vec) const {
			return Vector3(x - vec.x, y - vec.y, z - vec.z);
		}

		/**
 * @brief Subtracts another Vector3 from this one.
 *
 * This function subtracts the x, y and z values of the provided Vector3 from the corresponding values in this Vector3.
 * 
 * @param vec The Vector3 to be subtracted from this one.
 */
void operator-=(const Vector3& vec) {
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
		}

		/**
 * @brief This function returns a new vector that is the result of scaling this vector by a given scalar value.
 * @param scalar The value to scale the vector by.
 * @return A new Vector3 object representing the scaled vector.
 */
Vector3 operator*(float scalar) const {
			return Vector3(x * scalar, y * scalar, z * scalar);
		}

		//Vector3 Vector3::operator*(Vector3 s)
		//{
		//	return Vector3(x * s.x, y * s.y, z * s.z);
		//}
		/**
 * @brief This function scales the x, y and z coordinates of an object by a given scalar value.
 * 
 * @param scalar The value to scale the coordinates with.
 * 
 * @return void
 */
void operator*=(float scalar) {
			x *= scalar;
			y *= scalar;
			z *= scalar;
		}

		/**
 * @brief Performs division of the vector by a scalar value.
 * @param scalar The float value to divide each component of the vector by.
 * @return A new Vector3 where each component is the result of dividing the corresponding component of this vector by the given scalar.
 */
Vector3 operator/(float scalar) const {
			return Vector3(x / scalar, y / scalar, z / scalar);
		}

		/**
 * @brief Divides the vector's components by a given scalar.
 *
 * This function divides each of the vector's components (x, y, z) by the provided scalar. It modifies the vector in-place and returns it for convenience.
 *
 * @param scalar The value to divide the vector's components by. Must not be zero to avoid division by zero.
 * 
 * @return A reference to this Vector3 object after the operation.
 */
void operator/=(float scalar) {
			x /= scalar;
			y /= scalar;
			z /= scalar;
		}

		Vector3 normalize() const;

		/**
 * @brief Computes the dot product of this vector with another Vector3 object.
 *
 * The function takes a constant reference to another Vector3 object and calculates 
 * the dot product by multiplying each corresponding component of both vectors 
 * together (x*vec.x, y*vec.y, z*vec.z) and summing these products up.
 *
 * @param vec The other Vector3 object to compute the dot product with.
 * @return float Returns the computed dot product as a floating-point number.
 */
float dot(const Vector3& vec) const {
			float DotProduct = (x * vec.x) + (y * vec.y) + (z * vec.z);
			return DotProduct;
		}
		
		/**
 * @brief Computes the cross product of this vector with another one.
 * 
 * The cross product is a vector that is perpendicular to both given vectors and points in the direction from the first to the second. It has a length equal to the area of the parallelogram with edges being the two input vectors.
 * @param vec The other vector for the cross product operation.
 * @return A new Vector3 representing the result of the cross product.
 */
[[nodiscard]] Vector3 cross(const Vector3& vec) const {
			return {(y * vec.z) - (z * vec.y), (z * vec.x) - (x * vec.z), (x * vec.y) - (y * vec.x)};
		}

		/**
 * @brief Calculates the Euclidean norm (magnitude) of a Vector3 object.
 *
 * This function calculates the length of the vector from the origin to the point defined by its x, y and z coordinates. 
 * It does this by taking the square root of the sum of the squares of differences in each coordinate:
 * sqrtf((x - vec.x)^2 + (y - vec.y)^2 + (z - vec.z)^2).
 *
 * @param vec The Vector3 object for which to calculate the norm.
 * 
 * @return A float representing the Euclidean norm of the input vector.
 */
[[nodiscard]] float norm(const Vector3& vec) const {
			float Magnitude = sqrtf(
				powf((x - vec.x), 2.f) +
				powf((y - vec.y), 2.f) +
				powf((z - vec.z), 2.f)
			);

			return Magnitude;
		}

		/**
 * @brief Calculates the magnitude of a vector using Euclidean distance formula.
 * @return The magnitude (float) of the vector. If the vector is zero, returns 0.0.
 */
[[nodiscard]] float magnitude() const {
			return norm(Vector3());
		}
		/**
 * @brief Compares this Vector3 with another for equality.
 *
 * This function compares the x, y and z coordinates of this vector with those of the provided one. It returns true if all three are equal, false otherwise.
 *
 * @param vec The Vector3 to compare against.
 * @return True if the vectors are equal (i.e., their x, y, and z values are all identical), false otherwise.
 */
bool operator==(Vector3 vec) const {
			return (x == vec.x && y == vec.y && z == vec.z);
		}
		/**
 * @brief Compares this vector with another for equality.
 *
 * The comparison is done component-wise, i.e., it checks if the x, y and z components of both vectors are equal.
 *
 * @param vec The Vector3 to compare against.
 * 
 * @return True if all components of this vector match those of the provided one; false otherwise.
 */
bool operator==(const Vector3& vec) const {
			return (x == vec.x && y == vec.y && z == vec.z);
		}

		/**
 * @brief Compares this vector with another for inequality.
 *
 * This function compares the x, y and z components of this vector with those of the provided vector. It returns true if any of these components are not equal, false otherwise.
 *
 * @param vec The Vector3 to compare against.
 * @return True if any component is different, false otherwise.
 */
bool operator!=(const Vector3& vec) {
			return (x != vec.x || y != vec.y || z != vec.z);
		}

		/**
 * @brief Converts the object into a string representation.
 *
 * This function converts the object's x, y and z coordinates into a formatted string. The resulting string includes each coordinate prefixed with "X: ", "Y: ", and "Z: ". 
 *
 * @return A std::string containing the formatted coordinates.
 */
operator std::string()
		{
			std::stringstream SS;

			SS << "X: " << x << " Y: " << y << " Z: " << z << '\n';

			return SS.str();
		}

		/**
 * @brief Converts the object to a glm::vec3 type.
 * 
 * This operator overload allows for implicit conversion of an object into a glm::vec3 type. It returns a new vector with x, y and z coordinates set as per the current object's values.
 * @return A glm::vec3 object containing the x, y and z coordinates of the current object.
 */
operator glm::vec3()
		{
			return {x, y,z};
		}

		/**
 * @brief Converts the current instance of Vector3 to a quaternion.
 *
 * This function converts the x, y and z values of this vector into a glm::quat object. 
 * The resulting quaternion represents the same rotation as this vector.
 *
 * @return A new glm::quat that represents the same rotation as this Vector3.
 */
operator glm::quat()
		{
			return {glm::vec3(x,y,z)};
		}

	};

	/**
 * @brief This function performs element-wise multiplication of two vectors.
 *
 * @param a The first vector for the operation.
 * @param b The second vector for the operation.
 * @return A new Vector3 object resulting from the multiplication of the input vectors.
 */
inline Vector3 operator*(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
	}

}