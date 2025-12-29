#include "AGEpch.hpp"
#include "Math/Public/UtilityFunctions.h"

namespace AGE {
	 DirectX::XMFLOAT2 Convert::ToXMFloat2(Vector2 vec)
	{
		return DirectX::XMFLOAT2(vec.x, vec.y);
	}

	 DirectX::XMFLOAT3 Convert::ToXMFloat3(Vector3 vec)
	{
		return DirectX::XMFLOAT3(vec.x, vec.y, vec.z);
	}

	 DirectX::XMFLOAT4 Convert::ToXMFloat4(Vector4 vec)
	{
		return DirectX::XMFLOAT4(vec.x, vec.y, vec.z, vec.w);
	}

	 DirectX::XMVECTOR Convert::ToXMVec(Vector2 vec)
	{
		DirectX::XMVECTOR DXXMVec = DirectX::XMVectorSet(vec.x, vec.y, 1.f, 1.f);
		return DXXMVec;
	}

	 DirectX::XMVECTOR Convert::ToXMVec(Vector3 vec)
	{
		DirectX::XMVECTOR DXXMVec = DirectX::XMVectorSet(vec.x, vec.y, vec.z, 1.f);
		return DXXMVec;
	}

	 DirectX::XMVECTOR Convert::ToXMVec(Vector4 vec)
	{
		DirectX::XMVECTOR DXXMVec = DirectX::XMVectorSet(vec.x, vec.y, vec.z, vec.w);
		return DXXMVec;
	}

	 glm::vec3 Convert::ToGLM(Vector3 vec) {
		return glm::vec3(vec.x, vec.y, vec.z);
	}

	 glm::vec4 Convert::ToGLM(Vector4 vec) {
		return glm::vec4(vec.x, vec.y, vec.z, vec.w);
	}
}