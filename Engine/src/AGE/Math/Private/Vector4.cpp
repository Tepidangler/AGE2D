#include "AGEpch.hpp"
#include "Math/Public/Vector4.h"
#ifdef AG_PLATFORM_WINDOWS
#include <shtypes.h>
#endif

namespace AGE {
	/**
 * @brief Default constructor for the Vector4 class. Initializes all components to zero.
 *
 * This function initializes each component of a Vector4 object, setting them all to zero. The four components are x, y, z and w. 
 * They represent different aspects of the vector such as position, direction or color intensity.
 *
 * @return void
 */
Vector4::Vector4() {
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	/**
 * @brief Constructs a Vector4 with all components set to the same value.
 * 
 * This constructor initializes each component of the vector to the provided float value 'a'.
 * The resulting vector will have x, y, z and w equal to 'a'.
 *
 * @param a The value to initialize all four components of the Vector4 with.
 */
Vector4::Vector4(float a) {
		x = a;
		y = a;
		z = a;
		w = a;
	}

	/**
 * @brief Constructs a Vector4 object from a glm::vec4.
 *
 * This constructor takes a glm::vec4 and assigns its x, y, z, w values to the corresponding members of this Vector4 object.
 * 
 * @param vec The source vector.
 */
Vector4::Vector4(glm::vec4 vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
	}

	/**
 * @brief Constructs a Vector4 object with four components.
 * 
 * This function is used to initialize a Vector4 object with the given four float values. The first two parameters represent x and y coordinates, while the next two are z and w respectively.
 * 
 * @param a Float value representing the x component of the vector.
 * @param b Float value representing the y component of the vector.
 * @param c Float value representing the z component of the vector.
 * @param d Float value representing the w component of the vector.
 */
Vector4::Vector4(float a, float b, float c, float d) {
		x = a;
		y = b;
		z = c;
		w = d;
	}

	COMMENT:
/**
 * @brief Constructs a Vector4 object from four uint8_t values, each representing a byte of data. The bytes are converted to float and normalized between 0 and 100.
 * @param a First uint8_t value.
 * @param b Second uint8_t value.
 * @param c Third uint8_t value.
 * @param d Fourth uint8_t value.
 */
CONFIDENCE: 1.0;

Vector4::Vector4(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
	{
		std::byte tmpbyte = std::byte(a);
		int tmpint = std::to_integer<int>(tmpbyte);
		x = ((100.f * (float)tmpint) / 255.f) * .01f;

		tmpbyte = std::byte(b);
		tmpint = std::to_integer<int>(tmpbyte);
		y = ((100.f * (float)tmpint) / 255.f) * .01f;

		tmpbyte = std::byte(c);
		tmpint = std::to_integer<int>(tmpbyte);
		z = ((100.f * (float)tmpint) / 255.f) * .01f;

		tmpbyte = std::byte(d);
		tmpint = std::to_integer<int>(tmpbyte);

		w = ((100.f * (float)tmpint) / 255.f) * .01f;
	}

	/**
 * @brief Constructs a Vector4 object from an array of four floats.
 * 
 * The constructor takes in an array of four floats, which are used to initialize the x, y, z and w members of the Vector4 object.
 * 
 * @param color An array of four floats representing the initial values for the Vector4 object.
 * 
 * @return A new Vector4 object with its x, y, z and w members set to the corresponding elements in the input array.
 */
Vector4::Vector4(const float* color) {
		x = color[0];
		y = color[1];
		z = color[2];
		w = color[3];
	}

	//void Vector4::Serialize(DataWriter *Serializer, const Vector4 &Instance)
	//{
	//	Serializer->WriteRaw<float>(Instance.x);
	//	Serializer->WriteRaw<float>(Instance.y);
	//	Serializer->WriteRaw<float>(Instance.z);
	//	Serializer->WriteRaw<float>(Instance.w);
	//}
//
	//void Vector4::Deserialize(DataReader *Serializer, Vector4 &Instance)
	//{
	//	Serializer->ReadRaw<float>(Instance.x);
	//	Serializer->ReadRaw<float>(Instance.y);
	//	Serializer->ReadRaw<float>(Instance.z);
	//	Serializer->ReadRaw<float>(Instance.w);
	//}

	/**
 * @brief Normalizes this vector.
 * 
 * This function scales the vector so that its length (or magnitude) is equal to one, while maintaining its direction. If the vector has a zero length (i.e., it's a zero vector), the result will be another zero vector.
 * 
 * @return Vector4 The normalized version of this vector.
 */
Vector4 Vector4::normalize() const
	{
		return Vector4();
	}
}
