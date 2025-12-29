#include "AGEpch.hpp"
#include "Render/Public/FrameBuffer.h"
#include "Render/Public/Renderer.h"
#include "Platform/OpenGL/Public/OpenGLFrameBuffer.h"

namespace AGE
{
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& Spec)
	{
			switch (Renderer::GetAPI())
			{
			case 0:
				AGE_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported!");
				return nullptr;
				break;
			case 1:
				return CreateRef<OpenGLFrameBuffer>(Spec);
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
	T* FrameBuffer::As()
	{
		AGE_CORE_ASSERT(false, "As() Failed!");
		return nullptr;
	}
}