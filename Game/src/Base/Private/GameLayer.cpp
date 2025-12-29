#include "Base/Public/GameLayer.h"

namespace Proj
{
#if AG_DIST
	static AGE::Ref<AGE::Font> s_Font;
#endif

	GameLayer* GameLayer::s_Instance  = nullptr;
	GameLayer::GameLayer()
		:Layer("GameLayer")
	{

		s_Instance = this;
	}

	GameLayer::~GameLayer()
	{
	}

	void GameLayer::Init()
	{
#if AG_DIST
		s_Font = AGE::Font::GetDefault();
#endif
	}

	void GameLayer::SetViewportSize(AGE::Vector2 Size)
	{
#if AG_DIST
		m_ActiveScene->OnViewportResize((uint32_t)Size[0], (uint32_t)Size[1]);
		if (AGE::Renderer::GetAPI() != AGE::RendererAPI::DirectX11 && AGE::Renderer::GetAPI() != AGE::RendererAPI::DirectX12)
		{
			m_FrameBuffer->Resize((uint32_t)Size.x, (uint32_t)Size.y);
		}
#endif
	}
	void GameLayer::OnUpdate(AGE::TimeStep DeltaTime)
	{
#if AG_DIST
		DT = 1000 / DeltaTime.GetMilliseconds();
		//Update

		//UpdateScene
		AGE::RenderCommand::ResetStats();
		//Render
		if (AGE::RendererAPI::GetAPI() != AGE::RendererAPI::DirectX11)
		{
			m_FrameBuffer->Bind(0);
		}
		AGE::RenderCommand::SetClearColor(AGE::Vector4(1.f, .1f, .8f, .1f));
		AGE::RenderCommand::SetViewport(0, 0, m_FrameBuffer->GetSpecification().Width, m_FrameBuffer->GetSpecification().Height);
		AGE::RenderCommand::Clear();
		m_FrameBuffer->ClearAttachment(1, -1);
		m_ActiveScene->OnRuntimeUpdate(DeltaTime);

		if (AGE::RendererAPI::GetAPI() != AGE::RendererAPI::DirectX11)
		{
			m_FrameBuffer->Unbind();
		}
		else
		{
			m_FrameBuffer->Bind(0);
		}
#endif

		m_GameState->OnUpdate(DeltaTime);
	}
	void GameLayer::OnAttach()
	{
#ifdef WIN32
		MONITORINFOEX MonInfo;
		MonInfo.cbSize = sizeof(MonInfo);
		GetMonitorInfo(MonitorFromWindow(AGE::App::Get().GetDeviceManager().GetWindow().GetWin32Window(), MONITOR_DEFAULTTONEAREST), (LPMONITORINFO)&MonInfo);
		AGE::FrameBufferSpecification FbSpec;
		FbSpec.Attachments = { AGE::FramebufferTextureFormat::RGBA8, AGE::FramebufferTextureFormat::RED_INTEGER, AGE::FramebufferTextureFormat::DEPTH24STENCIL8 };
		FbSpec.Width = MonInfo.rcWork.right;
		FbSpec.Height = MonInfo.rcWork.bottom;

#else
		AGE::FrameBufferSpecification FbSpec;
		FbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::DEPTH24STENCIL8 };
		FbSpec.Width = 1280;
		FbSpec.Height = 720;
#endif
#if AG_DIST
		m_FrameBuffer = AGE::FrameBuffer::Create(FbSpec);
#endif
		m_GameState = AGE::CreateRef<GameFramework::GameState>();
	}
	void GameLayer::OnEvent(AGE::Event& Event)
	{
		AGE::EventDispatcher Dispatcher(Event);

#if AG_DIST
		m_FrameBuffer->OnEvent(Event);
#endif
	}
}