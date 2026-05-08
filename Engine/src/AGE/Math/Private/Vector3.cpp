#include "AGEpch.hpp"
#include "Math/Public/Vector3.h"
#include "Math/Public/Vector2.h"
#include "Math/Public/Vector4.h"

namespace AGE {
	/**
 * @brief Default constructor for Vector3 class. Initializes x, y and z to zero.
 */
Vector3::Vector3() {
		x = 0;
		y = 0;
		z = 0;
	}
	/**
 * @brief Constructs a Vector3 object with the given x, y and z coordinates.
 * 
 * @param a The x-coordinate of the vector.
 * @param b The y-coordinate of the vector.
 * @param c The z-coordinate of the vector.
 */
Vector3::Vector3(float a, float b, float c) {
		x = a;
		y = b;
		z = c;
	}
	/**
 * @brief Constructs a Vector3 object from a Vector2 and a float. The x and y components of the vector are set to the x component of the input Vector2, while z is set to the provided float value.
 * 
 * @param a A Vector2 object representing the x and y components of the new Vector3.
 * @param c A float value representing the z component of the new Vector3.
 */
Vector3::Vector3(Vector2 a, float c)
	{
		x = a.x;
		y = a.x;
		z = c;
	}
	/**
 * @brief Constructs a Vector3 object from a glm::vec3 vector.
 *
 * This constructor takes a glm::vec3 vector and assigns its x, y, and z components to the corresponding members of this Vector3 object.
 * 
 * @param v The input glm::vec3 vector.
 */
Vector3::Vector3(glm::vec3 v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	//Including Vector4.h will cause compiler issues because of recursion, so....
	//Convoluted, but, it'll work.
	COMMENT:
/**
 * @brief Constructs a Vector3 from a Vector4 by copying the x, y and z values.
 * 
 * @param v The Vector4 to copy data from.
 */
CONFIDENCE: 1.0;

Vector3::Vector3(Vector4 v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	//void Vector3::Serialize(DataWriter *Serializer, const Vector3 &Instance)
	//{
	//	Serializer->WriteRaw<float>(Instance.x);
	//	Serializer->WriteRaw<float>(Instance.y);
	//	Serializer->WriteRaw<float>(Instance.z);
	//}
//
	//void Vector3::Deserialize(DataReader *Serializer, Vector3 &Instance)
	//{
	//	Serializer->ReadRaw<float>(Instance.x);
	//	Serializer->ReadRaw<float>(Instance.y);
	//	Serializer->ReadRaw<float>(Instance.z);
	//}

	/**
 * @brief Constructs a Vector3 object with the same value for x, y and z.
 * 
 * This constructor initializes all three components of the vector to the given scalar value 'a'.
 * The resulting vector will have equal values in each component (x = a, y = a, z = a).
 *
 * @param a The scalar value used for initialization.
 */
Vector3::Vector3(float a) {
		x = a;
		y = a;
		z = a;
	}

	/**
 * @brief Normalizes this vector.
 *
 * This function calculates the magnitude of the vector and divides each component by that magnitude to normalize it. If the magnitude is zero, a zero vector is returned.
 * 
 * @return A new Vector3 object representing the normalized version of this vector.
 */
Vector3 Vector3::normalize() const {
		float magnitude = this->magnitude();
		if (magnitude == 0) {
			return Vector3(0, 0, 0);
		}

		return Vector3(x, y, z) / magnitude;
	}

}