#include "AGEpch.hpp"
#include "Render/Public/GraphicsContext.h"
#include "Render/Public/Renderer.h"
#include "Platform/OpenGL/Public/OpenGlContext.h"

namespace AGE
{

	
/**
 * @brief Creates a graphics context based on the current renderer API.
 * 
 * This function creates and returns a Scope of GraphicsContext which is initialized according to the currently set Renderer API. If no valid API is set, it asserts false and returns nullptr.
 */
Scope<GraphicsContext> GraphicsContext::Create(void* Window)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
			CoreLogger::Assert(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(Window));
			break;
		default:
			CoreLogger::Assert(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		CoreLogger::Assert(false, "Unknown Renderer API!");
		return nullptr;

	}

	template<typename T>
	/**
 * @brief This function is a placeholder for future use. It currently always asserts false and returns null.
 * @param None
 * @return T* Returns nullptr.
 */
/**
 * @brief This function is currently not implemented and will always throw an assertion.
 * It returns a pointer of type T*, which in this case is unknown to the documentation.
 * The function does not take any parameters. 
 * In future, it should be implemented to cast the GraphicsContext instance to another derived class if possible.
 * @return A nullptr as per current implementation.
 */
T* GraphicsContext::As()
	{
		CoreLogger::Assert(false, "As() Failed!");
		return nullptr;
	}

}

