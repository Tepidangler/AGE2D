#include "AGEpch.hpp"
#include "Math/Public/UtilityFunctions.h"

namespace AGE {
#ifdef AG_PLATFORM_WINDOWS
	 /**
 * @brief Converts a Vector2 to XMFLOAT2.
 * 
 * This function takes a Vector2 object and returns an equivalent XMFLOAT2 object. The conversion is done by simply copying the x and y values from the Vector2 to the XMFLOAT2.
 *
 * @param vec A Vector2 object to be converted.
 * @return DirectX::XMFLOAT2 An equivalent XMFLOAT2 object with same x and y values as input Vector2.
 */
DirectX::XMFLOAT2 Convert::ToXMFloat2(Vector2 vec)
	{
		return DirectX::XMFLOAT2(vec.x, vec.y);
	}

	 /**
 * @brief Converts a Vector3 object to an XMFLOAT3 object.
 * 
 * This function takes a Vector3 object as input and returns an XMFLOAT3 object with the same x, y, and z values.
 * The conversion is done through the constructor of XMFLOAT3 which expects three float parameters representing the x, y, and z coordinates respectively.
 * 
 * @param vec A Vector3 object to be converted.
 * @return An XMFLOAT3 object with the same x, y, and z values as the input Vector3 object.
 */
DirectX::XMFLOAT3 Convert::ToXMFloat3(Vector3 vec)
	{
		return DirectX::XMFLOAT3(vec.x, vec.y, vec.z);
	}

	 /**
 *  @brief Converts a Vector4 to an XMFLOAT4.
 *  
 *  This function takes in a Vector4 and returns its equivalent DirectX::XMFLOAT4 representation, which is essentially the same data structure but with different names for clarity.
 *  
 *  @param vec The Vector4 to be converted.
 *  @return A new XMFLOAT4 object representing the input Vector4.
 */
DirectX::XMFLOAT4 Convert::ToXMFloat4(Vector4 vec)
	{
		return DirectX::XMFLOAT4(vec.x, vec.y, vec.z, vec.w);
	}

	 /**
 * @brief Converts a Vector2 to an XMVECTOR.
 *
 * This function takes a Vector2 object and converts it into an XMVECTOR, which is used in the DirectX Math library for vector operations. 
 * The Vector2's x and y values are set as the first two components of the resulting XMVECTOR. The remaining components (z and w) are set to 1.0f.
 *
 * @param vec A Vector2 object to be converted.
 * @return An XMVECTOR with the same x and y values as the input Vector2, but z and w set to 1.0f.
 */
DirectX::XMVECTOR Convert::ToXMVec(Vector2 vec)
	{
		DirectX::XMVECTOR DXXMVec = DirectX::XMVectorSet(vec.x, vec.y, 1.f, 1.f);
		return DXXMVec;
	}

	 /**
 * @brief Converts a Vector3 object to an XMVECTOR object using DirectX Math library functions.
 * 
 * This function takes in a Vector3 object and converts it into an XMVECTOR object by setting the x, y, z components of the vector. The w component is set to 1.0f as per the standard convention for homogeneous coordinates.
 * @param vec A Vector3 object containing the x, y, and z components to be converted.
 * @return An XMVECTOR object with the same x, y, and z values as in the input Vector3 object, but with w set to 1.0f.
 */
DirectX::XMVECTOR Convert::ToXMVec(Vector3 vec)
	{
		DirectX::XMVECTOR DXXMVec = DirectX::XMVectorSet(vec.x, vec.y, vec.z, 1.f);
		return DXXMVec;
	}

	 /**
 * @brief Converts a Vector4 to an XMVECTOR.
 * 
 * This function takes a Vector4 object and converts it into an XMVECTOR, which is used in DirectX math library for vector operations.
 * The Vector4's x, y, z, w values are set as the components of the resulting XMVECTOR.
 * 
 * @param vec A Vector4 object to be converted.
 * @return An XMVECTOR with the same components as the input Vector4.
 */
DirectX::XMVECTOR Convert::ToXMVec(Vector4 vec)
	{
		DirectX::XMVECTOR DXXMVec = DirectX::XMVectorSet(vec.x, vec.y, vec.z, vec.w);
		return DXXMVec;
	}
#endif
	 /**
 * @brief Converts a Vector3 to GLM's vec3 format.
 *
 * This function takes in a Vector3 object and returns its equivalent glm::vec3 representation. 
 * It directly maps the x, y, and z properties of the input Vector3 to the respective components of the output glm::vec3.
 *
 * @param vec The Vector3 object to be converted.
 * @return A glm::vec3 object with the same values as the input Vector3.
 */
glm::vec3 Convert::ToGLM(Vector3 vec) {
		return glm::vec3(vec.x, vec.y, vec.z);
	}

	 /**
 * @brief Converts a Vector4 to a GLM vec4.
 * 
 * This function takes in a Vector4 object and returns its equivalent glm::vec4 representation. The conversion is done by simply copying the x, y, z, and w values from the input Vector4 into the corresponding components of the output glm::vec4.
 * 
 * @param vec The Vector4 to be converted.
 * @return A glm::vec4 with the same x, y, z, and w values as the input Vector4.
 */
glm::vec4 Convert::ToGLM(Vector4 vec) {
		return glm::vec4(vec.x, vec.y, vec.z, vec.w);
	}
}