#include "AGEpch.hpp"
#include "Platform/OpenGL/Public/OpenGLRendererAPI.h"

#include <glad/glad.h>
#include "Debug/Public/Instrumentor.h"
namespace AGE
{
	void OpenGLRendererAPI::Init()
	{
		AGE_PROFILE_FUNCTION();
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glClearDepth(1.0f);
		glEnable(GL_LINE_SMOOTH);
		glFrontFace(GL_CW);
	}
	void OpenGLRendererAPI::SetClearColor(const Vector4 Color)
	{
		glClearColor(Color[0], Color[1], Color[2], Color[3]);
		glBlendColor(1.f, 1.f, 1.f, 1.f);
		
	}
	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t Width, uint32_t Height)
	{
		glViewport(-1, -1, Width, Height);
		
	}
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	}
	void OpenGLRendererAPI::Flush()
	{
		glFlush();
	}
	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& VertexArray, uint32_t IndexCount)
	{
		VertexArray->Bind();

		uint32_t Count = IndexCount ? IndexCount : VertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, Count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void OpenGLRendererAPI::DrawLines(const Ref<VertexArray>& VertexArray, uint32_t VertexCount)
	{
		VertexArray->Bind();
		glDrawArrays(GL_LINES, 0, VertexCount);
	}
	void OpenGLRendererAPI::DrawStrips(const Ref<VertexArray>& VertexArray, uint32_t IndexCount)
	{
		VertexArray->Bind();

		uint32_t Count = IndexCount ? IndexCount : VertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLE_STRIP, Count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void OpenGLRendererAPI::SetLineWidth(float Width)
	{
		glLineWidth(Width);
	}
	void OpenGLRendererAPI::Submit()
	{
	}
	void OpenGLRendererAPI::Present()
	{
	}
}