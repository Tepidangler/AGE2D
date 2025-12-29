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

	void RenderCommand::SetClearColor(const Vector4 Color)
	{
		s_RendererAPI->SetClearColor(Color);
	}
	void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t Width, uint32_t Height)
	{
		s_RendererAPI->SetViewport(x, y, Width, Height);
	}
	void RenderCommand::Clear()
	{
		s_RendererAPI->Clear();
	}
	void RenderCommand::Submit()
	{
		s_RendererAPI->Submit();
	}
	void RenderCommand::Present()
	{
		s_RendererAPI->Present();
	}
	void RenderCommand::Flush()
	{
		s_RendererAPI->Flush();
	}
	void RenderCommand::ResetStats()
	{
		s_GraphicsPipeline->ResetStats();
	}
}