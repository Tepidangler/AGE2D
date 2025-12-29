#include "AGEpch.hpp"
#include "Render/Public/GraphicsContext.h"
#include "Render/Public/Renderer.h"
#include "Platform/OpenGL/Public/OpenGlContext.h"

namespace AGE
{

	Scope<GraphicsContext> GraphicsContext::Create(void* Window)
	{
		switch (Renderer::GetAPI())
		{
		case 0:
			AGE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(Window));
			break;
		default:
			AGE_CORE_ASSERT(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		AGE_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;

	}

	template<typename T>
	T* GraphicsContext::As()
	{
		AGE_CORE_ASSERT(false, "As() Failed!");
		return nullptr;
	}

}

