#include "AGEpch.hpp"
#include "Render/Public/Renderer.h"
#include "Render/Public/Renderer2D.h"
#include "Core/Public/App.h"


namespace AGE
{
	Renderer::SceneData* Renderer::m_SceneData = new SceneData;
	std::vector<WidgetStack> Renderer::m_WidgetStacks;

	void Renderer::Init()
	{
		AGE_PROFILE_FUNCTION();
		RenderCommand::Init();
		Renderer2D::Init();
	}

	
	void Renderer::BeginScene(const Camera& Camera, const Matrix4D& Transform)
	{
		Renderer2D::BeginScene(Camera, Transform);
	}

	void Renderer::BeginScene(const EditorCamera& Camera)
	{
		Renderer2D::BeginScene(Camera);
	}

	void Renderer::OnWindowResize(uint32_t Width, uint32_t Height)
	{
		RenderCommand::SetViewport(0, 0, Width, Height);
	}

	void Renderer::OnFramebufferResize(uint32_t Width, uint32_t Height)
	{
		RenderCommand::SetViewport(0, 0, Width, Height);
	}
	
	void Renderer::EndScene()
	{
		Renderer2D::EndScene();
	}
	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	void Renderer::RenderUI(TimeStep DeltaTime)
	{
		for (auto& WS : m_WidgetStacks)
		{
			for (auto& W : WS)
			{
				W->OnUpdate(DeltaTime);
			}
		}
	}

	void Renderer::Submit()
	{
		RenderCommand::Submit();
	}
	void Renderer::Flush()
	{
		RenderCommand::Flush();
	}
}