#include "AGEpch.hpp"
#include "Render/Public/VertexArray.h"
#include "Render/Public/Renderer.h"
#include "Platform/OpenGL/Public/OpenGLVertexArray.h"

namespace AGE
{
	/**
 * @brief Creates a new VertexArray object based on the current RendererAPI.
 * 
 * This function creates and returns a reference to a new VertexArray object, which is specific to the currently used RendererAPI. If the API is not supported or unknown, it asserts false and returns nullptr.
 * 
 * @return Ref<VertexArray> A reference to the newly created VertexArray object.
 */
/**
 * @brief Creates a new VertexArray based on the current RendererAPI.
 * 
 * This function creates and returns a reference to a new VertexArray object, which is specific to the currently used RendererAPI. If no supported API is found, it asserts false and returns nullptr.
 * 
 * @return Ref<VertexArray> A reference to the newly created VertexArray.
 */
Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case 0:
			CoreLogger::Assert(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateRef<OpenGLVertexArray>();
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