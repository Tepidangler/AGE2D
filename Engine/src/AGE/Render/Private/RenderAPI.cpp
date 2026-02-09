#include "AGEpch.hpp"
#include "Render/Public/RenderAPI.h"
#include "Platform/OpenGL/Public/OpenGLRendererAPI.h"

namespace AGE
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

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