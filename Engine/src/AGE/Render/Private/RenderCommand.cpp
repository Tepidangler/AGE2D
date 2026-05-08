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
void RenderCommand::Submit()
	{
		s_RendererAPI->Submit();
	}
	/**
 * @brief This function is used to present the current frame buffer on screen.
 * 
 * The function calls the Present method of the s_RendererAPI object, which should handle presenting the current frame buffer on screen.
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
void RenderCommand::ResetStats()
	{
		s_GraphicsPipeline->ResetStats();
	}
}