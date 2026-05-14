#include "AGEpch.hpp"
#include "Render/Public/FrameBuffer.h"
#include "Render/Public/Renderer.h"
#include "Platform/OpenGL/Public/OpenGLFrameBuffer.h"

namespace AGE
{
	/**
 * @brief Creates a new FrameBuffer based on the specified specification.
 * The type of FrameBuffer to create is determined by the current RendererAPI in use.
 * 
 * @param Spec The specification for the FrameBuffer to be created. This includes things like width, height and color attachments.
 * @return A reference to the newly created FrameBuffer. If the RendererAPI in use does not support a FrameBuffer of that type, nullptr is returned instead.
 */
/**
 * @brief Creates a new frame buffer based on the given specification.
 * The type of FrameBuffer to create is determined by the current RendererAPI in use.
 * 
 * @param Spec The specification for the new frame buffer. This includes things like width, height and color attachments.
 * @return A reference to the newly created FrameBuffer. If no suitable FrameBuffer could be created (e.g., due to unsupported RendererAPI), nullptr is returned instead.
 */
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
	/**
 * @brief This function is currently not implemented and will always throw an assertion.
 * It returns a null pointer of type T*. The purpose of this function is unknown.
 * 
 * @return A null pointer of type T*
 */
/**
 * @brief This function is currently not implemented and will always throw an assertion error.
 * It returns a null pointer of type T*. The purpose of this function is unknown.
 * 
 * @return A null pointer of type T*
 */
T* FrameBuffer::As()
	{
		CoreLogger::Assert(false, "As() Failed!");
		return nullptr;
	}
}