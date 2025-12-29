#pragma once
#include "RenderAPI.h"
#include "Render/Public/Pipeline.h"



namespace AGE
{
	class RenderCommand
	{
	public:

		static void Init();
		static void SetClearColor(const Vector4 Color);
		static void SetViewport(uint32_t x, uint32_t y, uint32_t Width, uint32_t Height);
		static void Clear();
		static void Submit();
		static void Present();
		static void Flush();
		static void ResetStats();
		static RendererAPI::API& GetCurrentRendererAPI() { return s_CurrentAPI; }

		static void ChangeRendererAPI(const RendererAPI::API Renderer) { s_RendererAPI.reset();  s_RendererAPI = RendererAPI::Create(); }

		inline static void DrawIndexed(uint32_t IndexCount, uint32_t IndexStart, int VertexStart)
		{
			s_RendererAPI->DrawIndexed(IndexCount, IndexStart, VertexStart);
		}
		inline static void DrawIndexed(const Ref<VertexArray>& VertexArray, uint32_t IndexCount = 0)
		{
			s_RendererAPI->DrawIndexed(VertexArray, IndexCount);
		}	

		inline static void DrawLines(const Ref<VertexArray>& VertexArray, uint32_t VertexCount = 0)
		{
			s_RendererAPI->DrawLines(VertexArray, VertexCount);
		}
		inline static void DrawStrips(const Ref<VertexArray>& VertexArray, uint32_t VertexCount = 0)
		{
			s_RendererAPI->DrawStrips(VertexArray, VertexCount);
		}

		inline static void SetLineWidth(float Width)
		{
			s_RendererAPI->SetLineWidth(Width);
		}
	private:

		static Scope<RendererAPI> s_RendererAPI;

		static Ref<Pipeline> s_GraphicsPipeline;

		static RendererAPI::API s_CurrentAPI;

		friend class Renderer2D;
		friend class Renderer3D;
	};
}