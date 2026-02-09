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
				CoreLogger::Assert(false, "RendererAPI::API::None is currently not supported!");
				return nullptr;
				break;
			case 1:
				return CreateRef<OpenGLFrameBuffer>(Spec);
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
	T* FrameBuffer::As()
	{
		CoreLogger::Assert(false, "As() Failed!");
		return nullptr;
	}
}