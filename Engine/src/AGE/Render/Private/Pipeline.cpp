#include "AGEpch.hpp"
#include "Render/Public/Pipeline.h"
#include "Platform/OpenGL/Public/OpenGLPipeline.h"
#include "Render/Public/RenderAPI.h"

namespace AGE
{
	Scope<Pipeline> Pipeline::Create()
	{
		switch (RendererAPI::GetAPI())
		{
			case 0:
			{
				return nullptr;
			}
			case 1: //OpenGL
			{
				return CreateScope<OpenGLPipeline>();
			}

				return nullptr;
		}
	}

	template<typename T>
	T* Pipeline::As()
	{
		AGE_CORE_ASSERT(false, "As() Failed!");
		return nullptr;
	}
}

