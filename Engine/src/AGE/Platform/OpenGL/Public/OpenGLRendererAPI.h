#pragma once
#include "Render/Public/RenderAPI.h"

namespace AGE
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public: //functions

		virtual void Init() override;
		virtual void SetClearColor(const Vector4 Color) override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t Width, uint32_t Height) override;
		virtual void Clear() override;

		virtual void Flush() override;
		virtual void DrawIndexed(uint32_t IndexCount, uint32_t IndexStart, int VertexStart) override {}
		virtual void DrawIndexed(const Ref<VertexArray>& VertexArray, uint32_t IndexCount) override;
		virtual void DrawLines(const Ref<VertexArray>& VertexArray, uint32_t VertexCount) override;
		virtual void DrawStrips(const Ref<VertexArray>& VertexArray, uint32_t IndexCount) override;
		virtual void SetLineWidth(float Width) override;


		/** This Function Currently Fails silently since there is really no use for them
		* however because of how pure virtual classes work it has to be here to compile
		*/
		virtual void Submit() override;
		/** This Function Currently Fails silently since there is really no use for them
		* however because of how pure virtual classes work it has to be here to compile
		*/
		virtual void Present() override;
	};
}