#pragma once
#include "RenderCommand.h"
#include "RenderAPI.h"
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

			static void RenderUI(TimeStep DeltaTime);

			static void Submit();

			static void Flush();

			static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
			static inline void SetAPI(RendererAPI::API Renderer) { RendererAPI::SetAPI(Renderer); }

		static std::vector<WidgetStack> m_WidgetStacks;

		private:
			struct SceneData
			{
				Matrix4D ViewProjectionMatrix;

				Matrix4D ViewProjectionModelMatrix;
			};

			static SceneData* m_SceneData;



	};
}
