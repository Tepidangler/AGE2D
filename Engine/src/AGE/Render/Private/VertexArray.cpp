#include "AGEpch.hpp"
#include "Render/Public/VertexArray.h"
#include "Render/Public/Renderer.h"
#include "Platform/OpenGL/Public/OpenGLVertexArray.h"

namespace AGE
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case 0:
			AGE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
			return nullptr;
			break;
		case 1:
			return CreateRef<OpenGLVertexArray>();
			break;
		default:
			AGE_CORE_ASSERT(false, "Unknown Renderer API!");
			return nullptr;
			break;
		}
		AGE_CORE_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}
}