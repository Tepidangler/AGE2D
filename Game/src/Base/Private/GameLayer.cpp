#include "Base/Public/GameLayer.h"

namespace Proj
{
#if AG_DIST
	static AGE::Ref<AGE::AGEFont> s_Font;
#endif

	GameLayer* GameLayer::s_Instance  = nullptr;
	GameLayer::GameLayer()
		:AGE::Layer("GameLayer")
	{

		s_Instance = this;
	}

	GameLayer::~GameLayer()
	{
	}

	void GameLayer::Init()
	{
#if AG_DIST
		s_Font = AGE::AGEFont::GetDefault();
#endif
	}

	void GameLayer::SetViewportSize(AGE::Vector2 Size)
	{
#if AG_DIST
		m_ActiveScene->OnViewportResize((uint32_t)Size[0], (uint32_t)Size[1]);
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
		AGE::RenderCommand::SetClearColor(AGE::Vector4(1.f, .1f, .8f, .1f));
		AGE::RenderCommand::SetViewport(0, 0, m_FrameBuffer->GetSpecification().Width, m_FrameBuffer->GetSpecification().Height);
		AGE::RenderCommand::Clear();
		m_FrameBuffer->ClearAttachment(1, -1);
		m_ActiveScene->OnRuntimeUpdate(DeltaTime);
		m_FrameBuffer->Bind();
#endif

		m_GameState->OnUpdate(DeltaTime);
	}
	void GameLayer::OnAttach()
	{
#ifdef WIN32
		MONITORINFOEX MonInfo;
		MonInfo.cbSize = sizeof(MonInfo);
		GetMonitorInfo(MonitorFromWindow(AGE::App::Get().GetDeviceManager().GetWindow().GetPlatformWindow(), MONITOR_DEFAULTTONEAREST), (LPMONITORINFO)&MonInfo);
		AGE::FrameBufferSpecification FbSpec;
		FbSpec.Attachments = { AGE::FramebufferTextureFormat::RGBA8, AGE::FramebufferTextureFormat::RED_INTEGER, AGE::FramebufferTextureFormat::DEPTH24STENCIL8 };
		FbSpec.Width = MonInfo.rcWork.right;
		FbSpec.Height = MonInfo.rcWork.bottom;

#else
		AGE::FrameBufferSpecification FbSpec;
		FbSpec.Attachments = { AGE::FramebufferTextureFormat::RGBA8, AGE::FramebufferTextureFormat::RED_INTEGER, AGE::FramebufferTextureFormat::DEPTH24STENCIL8 };
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