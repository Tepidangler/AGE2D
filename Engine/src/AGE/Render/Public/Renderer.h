#pragma once
#include "Render/Public/RenderAPI.h"
#include "Camera/Public/Camera.h"
#include "Camera/Public/EditorCamera.h"
#include "UI/Public/WidgetStack.h"

namespace AGE
{
	class Renderer
	{
		public:

			static void Init();
			static void BeginScene(const Camera&  Camera, const Matrix4D& Transform);
			static void BeginScene(const EditorCamera&  Camera);
			static void OnWindowResize(uint32_t Width, uint32_t Height);
			static void OnFramebufferResize(uint32_t Width, uint32_t Height);
			static void EndScene();
			static void Shutdown();

			static void Submit();

			static void Flush();

			/**
 * @brief This function returns the current API being used by the renderer.
 * @return The enum value representing the currently active API (RendererAPI::OpenGL, RendererAPI::Vulkan, etc.).
 */
/**
 * @brief This function returns the current API being used by the renderer.
 * @return The enum value representing the current API, which can be either RendererAPI::None, RendererAPI::OpenGL, or RendererAPI::DirectX. 
 */
static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
			/**
 * @brief Sets the rendering API to be used by the application.
 *
 * This function sets the API that will be used for rendering operations in the application. The API can be one of three types: OpenGL, DirectX or Vulkan. 
 * It is important to note that this function does not handle any errors or exceptions related to invalid APIs. Therefore, it's crucial to ensure that the input value is a valid one (OpenGL, DirectX or Vulkan).
 *
 * @param Renderer The API to be set for rendering operations. It can be either RendererAPI::API::OPENGL, RendererAPI::API::DIRECTX or RendererAPI::API::VULKAN.
 */
COMMENT:
/**
 * @brief Sets the rendering API to be used by the application.
 * @param Renderer The type of renderer API to use (e.g., OpenGL, DirectX).
 */
CONFIDENCE: 1.0;

static inline void SetAPI(RendererAPI::API Renderer) { RendererAPI::SetAPI(Renderer); }
		private:
			struct SceneData
			{
				Matrix4D ViewProjectionMatrix;

				Matrix4D ViewProjectionModelMatrix;
			};

			static SceneData* m_SceneData;



	};
}
