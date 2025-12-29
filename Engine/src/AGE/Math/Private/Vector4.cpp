#include "AGEpch.hpp"
#include "Math/Public/Vector4.h"

namespace AGE {
	Vector4::Vector4() {
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	Vector4::Vector4(float a) {
		x = a;
		y = a;
		z = a;
		w = a;
	}

	Vector4::Vector4(glm::vec4 vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
	}

	Vector4::Vector4(float a, float b, float c, float d) {
		x = a;
		y = b;
		z = c;
		w = d;
	}

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

	Vector4 Vector4::normalize() const
	{
		return Vector4();
	}
}