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
		explicit Vector2(float a);
		Vector2(float a, float b);
		/**
 * @brief Copy constructor for a 2D vector class.
 * 
 * This function creates a new instance of the Vector2 class by copying the values from another instance.
 * The parameters are copied to the newly created object.
 *
 * @param Other A const reference to an existing Vector2 object.
 */
Vector2(const Vector2& Other)
		{
			x = Other.x;
			y = Other.y;
		}

		/**
 * @brief Assigns the values of another Vector2 to this one.
 *
 * This operator overload allows for assignment of the x and y coordinates from another Vector2 object.
 * The function takes a constant reference to a Vector2 as its parameter, which is then used to set the x and y 
 * coordinates of the current Vector2 object. It returns a reference to the modified Vector2 object.
 *
 * @param Other A constant reference to a Vector2 object whose values are to be assigned to this one.
 *
 * @return A reference to the modified Vector2 object.
 */
Vector2& operator=(const Vector2& Other)
		{
			x = Other.x;
			y = Other.y;
			return *this;
		}

		/**
 * @brief Computes the dot product of this vector with another vector.
 *
 * The function takes a constant reference to another Vector2 object and calculates the dot product by multiplying the x-coordinates together, then the y-coordinates, and finally adding these two products together. 
 * It returns the result as a float.
 *
 * @param vec A const reference to the other vector with which to compute the dot product.
 * @return The computed dot product of this vector and the input vector.
 */
/**
 * @brief Computes the dot product of this vector with another Vector2 object.
 *
 * The function takes a constant reference to another Vector2 object and calculates the dot product 
 * by multiplying the x-coordinates together, then the y-coordinates, and finally adding these two products together.
 * It returns the resulting float value which represents the dot product of this vector with the input vector.
 *
 * @param vec A constant reference to another Vector2 object that will be used in the calculation of the dot product.
 * 
 * @return The function returns a float representing the dot product of this vector and the input vector.
 */
float dot(const Vector2& vec) const {
			float product = (x * vec.x) + (y * vec.y);
			return product;
		}

		/**
 * @brief Calculates the Euclidean norm (magnitude) of a two dimensional vector.
 * 
 * This function calculates the length of the given Vector2 object by applying the formula for the Euclidean distance in a 2D space, which is sqrt(x^2 + y^2).
 * @param vec A constant reference to another Vector2 object whose norm (magnitude) we want to calculate.
 * @return Returns a float representing the magnitude of the input vector.
 */
/**
 * @brief Calculates the Euclidean norm (magnitude) of a 2D vector.
 * 
 * This function takes in a constant reference to a Vector2 object and calculates its Euclidean norm, which is defined as the square root of the sum of the squares of its x and y components.
 * @param vec A constant reference to a Vector2 object representing the input vector.
 * @return The Euclidean norm (magnitude) of the input vector.
 */
float norm(const Vector2& vec) const {
			float magnitude = sqrtf(powf((x - vec.x), 2.f) + powf((y - vec.y), 2.f));

			return magnitude;
		}

		/**
 * @brief Calculates the magnitude of a Vector2 object using Euclidean distance formula.
 * @return Returns the magnitude as a float value. If the vector is (0,0), returns 0.
 */
/**
 * @brief Calculates the magnitude of a Vector2 object using the Euclidean distance formula.
 * @return The magnitude (length) of the vector as a float value. If the vector is [0, 0], returns 0.
 */
float magnitude() const {
			return norm(Vector2());
		}

		Vector2 normalize() const;

		/**
 * @brief This function is an overloaded operator that returns a reference to the element at index 'i' in the array.
 * @param[in] i The index of the element to return.
 * @return A reference to the element at index 'i'. If 'i' is out of bounds, it will throw an exception.
 */
/**
 * @brief This function returns a reference to the element at index 'i' in an array.
 * @param[in] i The index of the element to return.
 * @return A reference to the element at index 'i'. If 'i' is out of bounds, it will throw an exception.
 */
float& operator [](int i)
		{
			return ((&x)[i]);
		}

		/**
 * @brief This function returns a reference to the element at index 'i' in an array.
 *
 * The function takes an integer as input and returns a constant float reference. It is used for accessing elements of an array-like object, such as an array or vector. 
 *
 * @param i An integer representing the index of the desired element in the array-like object.
 * @return A constant float reference to the element at index 'i' in the array-like object.
 */
/**
 * @brief This function returns a reference to the element at index 'i' in an array.
 * 
 * The function takes an integer as input and returns a constant float reference. It is used for accessing elements of an array-like object, such as an array or vector.
 * 
 * @param i An integer representing the index of the desired element in the array-like object.
 * @return A constant float reference to the element at index 'i'.
 */
const float& operator [](int i) const
		{
			return ((&x)[i]);
		}

		/**
 * @brief Adds two Vector2 objects together.
 *
 * This function takes another Vector2 object as an argument and returns a new Vector2 that represents the sum of this vector and the input vector.
 * The x-coordinates are added together, while the y-coordinates are also added.
 * 
 * @param vec A constant reference to another Vector2 object to be added with this one.
 * @return A new Vector2 object representing the sum of the two vectors.
 */
/**
 * @brief This function adds two Vector2 objects together.
 * 
 * @param vec The second Vector2 object to add to the current one.
 * @return A new Vector2 object that is the result of adding this vector and the input vector.
 */
Vector2 operator+(const Vector2& vec) const {
			return Vector2(x + vec.x, y + vec.y);
		}

		/**
 * @brief This function adds the components of a given vector to this vector.
 * @param vec The Vector2 object whose components are added to this one.
 * @return Nothing is returned as the result directly modifies the current instance (x and y).
 */
/**
 * @brief This function adds the components of a given vector to this vector.
 * @param vec The Vector2 object whose components are added to this one.
 */
void operator+=(const Vector2& vec) {
			x += vec.x;
			y += vec.y;
		}

		/**
 * @brief Subtracts another vector from this one.
 *
 * This function subtracts the x and y components of the given vector from the corresponding components of this vector.
 * The result is a new Vector2 object representing the difference between the two vectors.
 *
 * @param vec The Vector2 to be subtracted from this one.
 * @return A new Vector2 that represents the difference between this and the input Vector2.
 */
/**
 * @brief Subtracts another vector from this one and returns the result.
 * @param vec The vector to subtract from this one.
 * @return A new Vector2 representing the difference between this vector and the input vector.
 */
Vector2 operator-(const Vector2& vec) const {
			return Vector2(x - vec.x, y - vec.y);
		}
		/**
 * @brief Subtracts a scalar value from both x and y coordinates of the vector.
 * @param[in] val The scalar value to subtract.
 * @return A new Vector2 object with the result of the subtraction operation.
 */
Vector2 operator-(const float val) const {
			return Vector2(x - val, y - val);
		}


		/**
 * @brief Subtracts another vector from this one.
 *
 * This function subtracts the x and y components of the given vector from the corresponding components of this vector.
 * The result is stored in this vector, so it will be modified by this operation.
 *
 * @param vec The Vector2 to subtract from this one.
 */
/**
 * @brief Subtracts another vector from this one.
 *
 * This function subtracts the x and y components of the given vector from the corresponding components of this vector.
 * The result is stored in this vector, so it will be modified by this operation.
 *
 * @param vec The Vector2 to subtract from this one.
 */
void operator-=(const Vector2& vec) {
			x -= vec.x;
			y -= vec.y;
		}

		COMMENT:
/**
 * @brief This function returns a new vector that is the result of scaling this vector by a given scalar value.
 * @param scalar The value to scale the vector by.
 * @return A new Vector2 object representing the scaled vector.
 */
CONFIDENCE: 1.0;

COMMENT:
/**
 * @brief This function returns a new vector that is the result of scaling this vector by a given scalar value.
 * @param scalar The float value to scale the vector by.
 * @return A new Vector2 object representing the scaled vector.
 */
CONFIDENCE: 1.0;

Vector2 operator*(float scalar) const {
			return Vector2(x * scalar, y * scalar);
		}

		/**
 * @brief Multiplies the x and y coordinates of this vector by a given scalar.
 * 
 * This function multiplies the values of 'x' and 'y' by the provided scalar, effectively scaling the vector.
 * The result is stored back in 'x' and 'y', so no new value is returned.
 *
 * @param scalar The value to scale this vector by.
 */
/**
 * @brief Multiplies the x and y coordinates of this vector by a given scalar.
 * @param[in] scalar The value to multiply with.
 */
void operator*=(float scalar) {
			x *= scalar;
			y *= scalar;
		}

		COMMENT:
/**
 * @brief This function divides the vector by a given scalar value.
 * @param scalar The float value to divide the vector components by.
 * @return A new Vector2 object where each component is the result of division of the corresponding vector component by the scalar.
 */
CONFIDENCE: 1.0;

COMMENT:
/**
 * @brief This function divides the vector by a given scalar value.
 * 
 * @param scalar The value to divide the vector components by.
 * @return A new Vector2 object where each component is the corresponding component of this vector divided by the scalar.
 */
CONFIDENCE: 1.0;

Vector2 operator/(float scalar) const {
			return Vector2(x / scalar, y / scalar);
		}

		/**
 * @brief Performs element-wise division of this vector by another vector.
 * @param vec The vector to divide elements by.
 * @return A new Vector2 where each component is the corresponding components of this vector divided by the input vector.
 */
COMMENT:
/**
 * @brief Performs element-wise division of this vector by another vector.
 * @param vec The divisor vector.
 * @return A new Vector2 where each component is the result of the corresponding components in this vector divided by the corresponding components in the input vector.
 */
CONFIDENCE: 1.0;

Vector2 operator/(const Vector2& vec) const {
			return Vector2(x / vec.x, y / vec.y);
		}

		/**
 * @brief Divides the coordinates (x, y) by a given scalar.
 *
 * This function divides both x and y by the provided scalar. It modifies the object on which it is called.
 *
 * @param scalar The value to divide the coordinates by. Must not be zero to avoid division by zero.
 */
/**
 * @brief Divides the coordinates (x, y) by a given scalar.
 * @param[in] scalar The value to divide the coordinates by.
 */
void operator/=(float scalar) {
			x /= scalar;
			y /= scalar;
		}

		/**
 * @brief Compares two Vector2 objects for equality.
 *
 * This function compares the x and y coordinates of this Vector2 object with another Vector2 object's x and y coordinates.
 * It returns true if both are equal, false otherwise.
 * 
 * @param vec The Vector2 object to compare against.
 * @return True if the objects have identical x and y coordinates, false otherwise.
 */
/**
 * @brief Compares two Vector2 objects for equality based on their x and y coordinates.
 * @param vec The Vector2 object to compare with the current one.
 * @return True if both the x and y coordinates of the two vectors are equal, false otherwise.
 */
bool operator==(const Vector2& vec) const {
			return x == vec.x && y == vec.y;
		}

		/**
 * @brief Compares two Vector2 objects for inequality.
 *
 * This function compares the current Vector2 object with another one to determine if they are not equal. It does this by comparing the x and y coordinates of both vectors.
 * 
 * @param vec The Vector2 object to compare with.
 * @return True if the objects are not equal, false otherwise.
 */
/**
 * @brief Compares two Vector2 objects for inequality.
 *
 * This function compares the x and y coordinates of this Vector2 object with another Vector2 object's x and y coordinates. 
 * It returns true if any of these values are not equal, false otherwise.
 *
 * @param vec The other Vector2 object to compare with.
 * @return True if the objects are not equal (i.e., their x or y coordinates differ), false otherwise.
 */
bool operator!=(const Vector2& vec) const {
			return x != vec.x || y != vec.y;
		}

		/**
 * @brief Converts the object into a string representation.
 *
 * This function converts the object's x and y coordinates into a string format. The resulting string includes the labels "X:" and "Y:" followed by their respective values. 
 *
 * @return A std::string containing the formatted coordinate information.
 */
/**
 * @brief Converts the object to a string representation.
 *
 * This function converts the object into its string representation, which includes the x and y coordinates of the object. 
 * The format is "X: <x> Y: <y>".
 *
 * @return A std::string containing the formatted coordinates.
 */
operator std::string()
		{
			std::stringstream SS;

			SS << "X: " << x << " Y: " << y << '\n';

			return SS.str();
		}
	};


}


