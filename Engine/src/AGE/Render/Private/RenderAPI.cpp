#include "AGEpch.hpp"
#include "Render/Public/RenderAPI.h"
#include "Platform/OpenGL/Public/OpenGLRendererAPI.h"

namespace AGE
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	/**
 * @brief Creates a new instance of the RendererAPI based on the current setting.
 * 
 * This function creates and returns an instance of the appropriate RendererAPI class, depending on the currently set API. If no API is set (i.e., s_API is None), it asserts false with a message "RendererAPI::API::None is currently not supported!". For OpenGL, it returns a new instance of OpenGLRendererAPI. In all other cases, it asserts false with the message "Unknown Renderer API!" and returns nullptr.
 * 
 * @return Scope<RendererAPI> - The newly created RendererAPI instance or nullptr if an invalid API is set.
 */
Scope<RendererAPI> RendererAPI::Create()
	{
		switch ((int)s_API)
		{
		case 0:
			CoreLogger::Assert(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateScope<OpenGLRendererAPI>();
			break;
		default:
			CoreLogger::Assert(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		CoreLogger::Assert(false, "Unknown Renderer API!");
		return nullptr;
	}
}