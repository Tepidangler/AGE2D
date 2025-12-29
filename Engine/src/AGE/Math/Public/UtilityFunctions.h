#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H
#endif // !UTILITY_FUNCTIONS_H

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "d3d11_4.h"
#include "DirectXMath.h"
#include <glm/glm.hpp>

#pragma once

namespace AGE {
	class Convert {
	public:
		Convert() {}

		static DirectX::XMFLOAT2 ToXMFloat2(Vector2 vec);
		static DirectX::XMFLOAT3 ToXMFloat3(Vector3 vec);
		static DirectX::XMFLOAT4 ToXMFloat4(Vector4 vec);

		static DirectX::XMVECTOR ToXMVec(Vector2 vec);
		static DirectX::XMVECTOR ToXMVec(Vector3 vec);
		static DirectX::XMVECTOR ToXMVec(Vector4 vec);

		static glm::vec3 ToGLM(Vector3 vec);
		static glm::vec4 ToGLM(Vector4 vec);
	};
}