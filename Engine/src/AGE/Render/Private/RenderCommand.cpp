#include "AGEpch.hpp"
#include "Render/Public/RenderCommand.h"
#include "Platform/OpenGL/Public/OpenGLRendererAPI.h"
#include "Platform/OpenGL/Public/OpenGlContext.h"
#include "Core/Public/App.h"

namespace AGE
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
	RendererAPI::API RenderCommand::s_CurrentAPI = RendererAPI::API::OpenGL;
	Ref<Pipeline> RenderCommand::s_GraphicsPipeline = nullptr;

	
/**
 * @brief Initializes the RenderCommand. This includes setting up the renderer API, current API, and creating a graphics pipeline based on the type of API in use. 
 * 
 * The function uses a switch-case statement to determine which API is currently being used. If it's OpenGL (API value 1), it sets the pipeline for the OpenGL context and initializes the graphics pipeline. 
 * If an unsupported API is detected, an error message is logged.
 * 
 * @return void
 */
void RenderCommand::Init()
	{
		s_RendererAPI->Init();
		s_CurrentAPI = RendererAPI::GetAPI();
		s_GraphicsPipeline = Pipeline::Create();
		switch (RendererAPI::GetAPI())
		{
		case 1:
		{
			App::Get().GetDeviceManager().GetWindow().GetGraphicsContext()->As<OpenGLContext>()->SetPipeline(s_GraphicsPipeline->As<OpenGLPipeline>());
			s_GraphicsPipeline->Init();
			break;

		}
		default:
		{
			CoreLogger::Error("Renderer Not supported!");
			break;
		}
		}
	}

	/**
 * @brief Sets the clear color for the renderer.
 * 
 * This function sets the clear color used by the renderer to clear the frame buffer before rendering each new frame.
 * The color is specified as a Vector4 with components in the range [0,1].
 * 
 * @param Color The new clear color.
 */
/** 
 * @brief Sets the clear color for the renderer.
 * 
 * This function sets the clear color used by the renderer to clear the frame buffer before rendering a new frame. The color is specified as a Vector4 with components in the range [0,1].
 * 
 * @param Color A Vector4 specifying the red, green, blue and alpha values of the clear color. Each component should be in the range [0,1].
 * 
 * @return void
 */
void RenderCommand::SetClearColor(const Vector4 Color)
	{
		s_RendererAPI->SetClearColor(Color);
	}
	/**
 * @brief Set the viewport dimensions.
 * 
 * This function sets the dimensions of the viewport in pixels. The viewport is a rectangular area within which to render.
 * 
 * @param x The x-coordinate of the lower left corner of the viewport.
 * @param y The y-coordinate of the lower left corner of the viewport.
 * @param Width The width of the viewport in pixels.
 * @param Height The height of the viewport in pixels.
 */
/**
 * @brief Set the viewport for rendering.
 * 
 * This function sets the viewport dimensions for the renderer API. The viewport is a rectangle in the framebuffer that specifies what part of the framebuffer should be rendered to.
 * 
 * @param x The x-coordinate, indicating the left side of the viewport.
 * @param y The y-coordinate, indicating the top side of the viewport.
 * @param Width The width of the viewport.
 * @param Height The height of the viewport.
 */
void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t Width, uint32_t Height)
	{
		s_RendererAPI->SetViewport(x, y, Width, Height);
	}
	/**
 * @brief Clears the rendering buffer.
 * 
 * This function calls the Clear method of the currently bound Renderer API, which is responsible for clearing the rendering buffer. It's typically used to prepare the framebuffer for a new render pass.
 * 
 * @return void
 */
/**
 * @brief Clears the rendering buffer.
 * 
 * This function calls the Clear method of the currently bound Renderer API, which is responsible for clearing the rendering buffer.
 * The specifics of this operation are dependent on the concrete implementation of the Renderer API in use.
 */
void RenderCommand::Clear()
	{
		s_RendererAPI->Clear();
	}
	/**
 * @brief Submits the command to be processed by the renderer API.
 * 
 * This function submits a command for processing by the Renderer API, which is responsible for managing and executing all rendering operations.
 * The specifics of this submission process are handled internally by the Renderer API, so it's not necessary to understand these details in order to use this function.
 * 
 * @return void
 */
/**
 * @brief Submits the command to be processed by the renderer API.
 * 
 * This function submits a command for processing by the Renderer API, which is responsible for rendering and managing graphics resources.
 * The specifics of what this means will depend on the implementation of the Renderer API in use.
 * 
 * @return void
 */
void RenderCommand::Submit()
	{
		s_RendererAPI->Submit();
	}
	/**
 * @brief This function is used to present the current frame buffer on screen.
 * 
 * The function calls the Present method of the s_RendererAPI object, which should handle presenting the current frame buffer on screen.
 */
/**
 * @brief This function is used to present the current frame buffer for display.
 * 
 * It calls the Present method of the s_RendererAPI object, which should handle presenting the frame buffer on the target platform.
 */
void RenderCommand::Present()
	{
		s_RendererAPI->Present();
	}
	/**
 * @brief This function is used to flush the rendering commands in the renderer API. 
 * It calls the Flush method of the s_RendererAPI object, which should handle flushing all pending rendering commands.
 *
 * @return void No return value expected.
 */
/**
 * @brief This function flushes the renderer API buffer.
 * 
 * The function calls the Flush method of the s_RendererAPI object, which is presumably responsible for clearing or emptying any buffers that have been filled by rendering operations in previous frames. It does not take any parameters and returns void.
 */
void RenderCommand::Flush()
	{
		s_RendererAPI->Flush();
	}
	/**
 * @brief Resets the graphics pipeline statistics.
 * 
 * This function is used to reset all the statistics related to the graphics pipeline. It calls the `ResetStats` method on the global instance of `GraphicsPipeline`, which resets any accumulated data or counters for rendering performance tracking.
 *
 * @return void
 */
/** 
 * @brief Resets the graphics pipeline statistics.
 * 
 * This function is used to reset all the statistics related to the graphics pipeline. It calls the `ResetStats` method on the global instance of `GraphicsPipeline`.
 */
void RenderCommand::ResetStats()
	{
		s_GraphicsPipeline->ResetStats();
	}
}