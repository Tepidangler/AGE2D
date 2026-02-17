#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H
#endif // !UTILITY_FUNCTIONS_H
#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#ifdef AG_PLATFORM_WINDOWS
#include "d3d11_4.h"
#include "DirectXMath.h"
#endif
#include <glm/glm.hpp>


namespace AGE {

	class Convert {
	public:
		Convert() {}
#ifdef AG_PLATFORM_WINDOWS
		static DirectX::XMFLOAT2 ToXMFloat2(Vector2 vec);
		static DirectX::XMFLOAT3 ToXMFloat3(Vector3 vec);
		static DirectX::XMFLOAT4 ToXMFloat4(Vector4 vec);

		static DirectX::XMVECTOR ToXMVec(Vector2 vec);
		static DirectX::XMVECTOR ToXMVec(Vector3 vec);
		static DirectX::XMVECTOR ToXMVec(Vector4 vec);
#endif
		static glm::vec3 ToGLM(Vector3 vec);
		static glm::vec4 ToGLM(Vector4 vec);
	};
}