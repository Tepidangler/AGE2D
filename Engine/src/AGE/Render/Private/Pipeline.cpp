#include "AGEpch.hpp"
#include "Render/Public/Pipeline.h"
#include "Platform/OpenGL/Public/OpenGLPipeline.h"
#include "Render/Public/RenderAPI.h"

namespace AGE
{
	/**
 * @brief Creates a new pipeline based on the current RendererAPI.
 * 
 * This function creates and returns a new Pipeline object that is specific to the currently used RendererAPI. The type of Pipeline created depends on which API is in use at the time this function is called. If no valid RendererAPI is detected, nullptr is returned.
 * 
 * @return Scope<Pipeline> A new pipeline or nullptr if no valid RendererAPI was found.
 */
/**
 * @brief Creates a new Pipeline instance based on the current RendererAPI.
 * 
 * This function checks the currently set RendererAPI and creates an appropriate pipeline for it. If the API is not recognized, nullptr is returned.
 * 
 * @return Scope<Pipeline> A smart pointer to a new Pipeline instance or nullptr if the current RendererAPI is unrecognized.
 */
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
		}
		return nullptr;
	}

	template<typename T>
	/**
 * @brief This function is currently not implemented and will always throw an assertion error.
 * It returns a null pointer of type T*.
 * The purpose of this function is unknown.
 * 
 * @return A null pointer of type T*
 */
/**
 * @brief This function is currently not implemented and will always throw an assertion error.
 * It returns a null pointer of type T*. The purpose of this function is unknown.
 * 
 * @return A null pointer of type T*
 */
T* Pipeline::As()
	{
		CoreLogger::Assert(false, "As() Failed!");
		return nullptr;
	}
}

