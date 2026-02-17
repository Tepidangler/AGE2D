#pragma once
#include "Render/Public/RenderAPI.h"

namespace AGE
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public: //functions

		~OpenGLRendererAPI() =default;
		void Init() override;
		void SetClearColor(const Vector4 Color) override;
		void SetViewport(uint32_t x, uint32_t y, uint32_t Width, uint32_t Height) override;
		void Clear() override;

		void Flush() override;
		void DrawIndexed(uint32_t IndexCount, uint32_t IndexStart, int VertexStart) override {}
		void DrawIndexed(const Ref<VertexArray>& VertexArray, uint32_t IndexCount) override;
		void DrawLines(const Ref<VertexArray>& VertexArray, uint32_t VertexCount) override;
		void DrawStrips(const Ref<VertexArray>& VertexArray, uint32_t IndexCount) override;
		void SetLineWidth(float Width) override;


		/** This Function Currently Fails silently since there is really no use for them
		* however because of how pure virtual classes work it has to be here to compile
		*/
		void Submit() override;
		/** This Function Currently Fails silently since there is really no use for them
		* however because of how pure virtual classes work it has to be here to compile
		*/
		void Present() override;
	};
}