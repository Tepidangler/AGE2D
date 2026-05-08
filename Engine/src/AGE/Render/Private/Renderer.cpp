#include "AGEpch.hpp"
#include "Render/Public/Renderer.h"
#include "Render/Public/Renderer2D.h"
#include "Core/Public/App.h"
#include "Render/Public/RenderCommand.h"


namespace AGE
{
	Renderer::SceneData* Renderer::m_SceneData = new SceneData;

	/** 
 * @brief Initializes the renderer.
 * 
 * This function initializes various subsystems of the renderer, including RenderCommand and Renderer2D. It uses AGE_PROFILE_FUNCTION to record its performance.
 * 
 * @return void
 */
void Renderer::Init()
	{
		AGE_PROFILE_FUNCTION();
		RenderCommand::Init();
		Renderer2D::Init();
	}

	
	/**
 * @brief Begins a 3D scene with the given camera and transformation.
 * 
 * This function begins a new 3D scene using the provided camera and transformation matrix. It uses the Renderer2D::BeginScene() method to do this, passing in the camera and transform as parameters.
 * 
 * @param Camera The camera used for rendering the scene.
 * @param Transform The transformation matrix applied to the scene objects.
 * 
 * @return void No return value is expected.
 */
void Renderer::BeginScene(const Camera& Camera, const Matrix4D& Transform)
	{
		Renderer2D::BeginScene(Camera, Transform);
	}

	/** 
 * @brief Begins a new scene with the specified camera.
 * 
 * This function begins a new rendering scene using the provided EditorCamera object. It utilizes the Renderer2D class to begin the scene, which allows for efficient rendering of 2D graphics.
 * 
 * @param Camera The editor camera that will be used in this scene.
 */
void Renderer::BeginScene(const EditorCamera& Camera)
	{
		Renderer2D::BeginScene(Camera);
	}

	/**
 * @brief This function is called when the window size is resized. It sets the viewport to match the new dimensions.
 * @param Width The new width of the window in pixels.
 * @param Height The new height of the window in pixels.
 */
void Renderer::OnWindowResize(uint32_t Width, uint32_t Height)
	{
		RenderCommand::SetViewport(0, 0, Width, Height);
	}

	/**
 * @brief This function is called when the framebuffer size changes. It sets the viewport to match the new dimensions.
 * @param Width The width of the new framebuffer in pixels.
 * @param Height The height of the new framebuffer in pixels.
 */
void Renderer::OnFramebufferResize(uint32_t Width, uint32_t Height)
	{
		RenderCommand::SetViewport(0, 0, Width, Height);
	}
	
	/**
 * @brief Ends the current scene rendering.
 * 
 * This function is used to end the current scene rendering by calling the `EndScene` method of the Renderer2D class. It does not take any parameters and returns void.
 * 
 * @return None
 */
void Renderer::EndScene()
	{
		Renderer2D::EndScene();
	}
	/**
 * @brief Shuts down the renderer and its 2D component.
 *
 * This function is used to clean up resources held by the Renderer and its associated Renderer2D component. It should be called when shutting down the application or before initializing a new scene.
 *
 * @return void
 */
void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	/**
 * @brief Submits a render command to the queue.
 * 
 * This function submits a render command to the rendering system's queue, which will be processed and executed at some point in the future.
 * The specific behavior of this function is not specified as it depends on the implementation details of the Renderer class and its associated RenderCommand classes.
 * 
 * @return void
 */
void Renderer::Submit()
	{
		RenderCommand::Submit();
	}
	/**
 * @brief Flushes the rendering queue by calling the `Flush` function of the `RenderCommand` class.
 * 
 * This function is used to clear the rendering queue and ensure that all previous render commands are executed before any new ones are added. It calls the `Flush` function from the `RenderCommand` class, which should handle the actual flushing process.
 */
void Renderer::Flush()
	{
		RenderCommand::Flush();
	}
}