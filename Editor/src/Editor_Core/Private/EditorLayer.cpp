#if !AG_DIST
//#include <Core/Public/AGEpch.h>
#include <Age.h>

#include "Physics/Public/Physics2D.h"
#include "Render/Public/Renderer2D.h"
#include "Editor_Core/Public/EditorLayer.h"
#include "SimpleIni.h"

namespace AGE
{
	extern std::filesystem::path g_AssetPath;
	static Ref<Font> s_Font;

	EditorLayer* EditorLayer::s_Instance = nullptr;

	EditorLayer::EditorLayer()
		: Layer("Editor")
	{
		s_Instance = this;

	}

	void EditorLayer::SetViewportSize(AGE::Vector2 Size)
	{
		m_ActiveScene->OnViewportResize((uint32_t)Size[0], (uint32_t)Size[1]);
		m_EditorCamera.SetViewportSize(Size[0], Size[1]);
		m_FrameBuffer->Resize((uint32_t)Size[0], (uint32_t)Size[1]);
	}

	void EditorLayer::Init()
	{
		s_Font = Font::GetDefault();
		std::filesystem::path WindowIcon = App::Get().GetAppConfig().EditorAssetPath.string() + "/IconTexture/AGEIconbase.png";
		App::Get().GetDeviceManager().GetWindow().SetWindowIcon(WindowIcon);
	}

	void EditorLayer::OnUpdate(TimeStep DeltaTime)
	{
		DT = 1000 / DeltaTime.GetMilliseconds();
		//Update
		
		//UpdateScene
		RenderCommand::ResetStats();
		m_FrameBuffer->Bind();
		//Render
		AGE::RenderCommand::SetClearColor(AGE::Vector4(1.f, .1f, .8f, 1.f));
		RenderCommand::SetViewport(0, 0, m_FrameBuffer->GetSpecification().Width, m_FrameBuffer->GetSpecification().Height);
		AGE::RenderCommand::Clear();
		m_FrameBuffer->ClearAttachment(1, -1);
		switch (m_Toolbar->GetSceneState())
		{
		case SceneState::Edit:
		{
			if (m_ViewportFocused)
			{
			}
			m_EditorCamera.OnUpdate(DeltaTime);
			m_ActiveScene->OnEditorUpdate(DeltaTime, m_EditorCamera);

			break;
		}
		case SceneState::Play:
		{
			m_ActiveScene->OnRuntimeUpdate(DeltaTime);

			break;
		}
		}

		m_Viewport->OnUpdate(DeltaTime);
		m_FrameBuffer->Unbind();
		m_UIEditorWindow->OnUpdate(DeltaTime, m_EditorCamera);
	}


	void EditorLayer::OnAttach() 
	{
#ifdef WIN32
		MONITORINFOEX MonInfo;
		MonInfo.cbSize = sizeof(MonInfo);
		GetMonitorInfo(MonitorFromWindow(App::Get().GetDeviceManager().GetWindow().GetWin32Window(), MONITOR_DEFAULTTONEAREST), (LPMONITORINFO) & MonInfo);
		FrameBufferSpecification FbSpec;
		FbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::DEPTH24STENCIL8};
		//FbSpec.Width = MonInfo.rcWork.right;
		//FbSpec.Height = MonInfo.rcWork.bottom;
		FbSpec.Width = 1280;
		FbSpec.Height = 720;

#else
		FrameBufferSpecification FbSpec;
		FbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::DEPTH24STENCIL8 };
		FbSpec.Width = 1280;
		FbSpec.Height = 720;
#endif
		m_Database = CreateScope<Database>();
		m_FrameBuffer = FrameBuffer::Create(FbSpec);
		m_NodeEditorManager = CreateScope<NodeEditorManager>();
		m_UIEditorWindow = CreateRef<UIEditorWindow>();
		m_ActiveScene = CreateRef<Scene>();
		m_EditorCamera = EditorCamera(30.f,1.778f,.1f,1000.f);
		m_EditorCamera.SetProjectionType(ProjectionType::Perspective);
		m_Viewport = CreateRef<Viewport>("Scene Viewport");
		m_Panel = CreateRef<Panel>("Stats Panel");
		m_SceneHierarchyPanel = CreateRef<SceneHierarchyPanel>(m_ActiveScene);
		m_DatabaseWindow = CreateRef<DatabaseWindow>(m_Database.get());
		m_ContentBrowserPanel = CreateRef<ContentBrowserPanel>();
		m_MainMenuBar = CreateRef<MainMenuBar>();
		m_Toolbar = CreateRef<Toolbar>();
		m_InventoryDatabase = CreateRef<InventoryDatabase>();
		m_QuestManagerWindow = CreateRef<QuestManagerWindow>();
		m_AssetRegistryWindow = CreateRef<AssetRegistryWindow>();
		m_SceneHierarchyPanel->SetContext(m_ActiveScene);
		m_LogWindow = CreateRef<ConsoleLogWindow>();
		m_EditorScenePath = std::filesystem::path();
	}
	void EditorLayer::OnImGuiRender(TimeStep DeltaTime) 
	{
		DockSpace::MakeDockspace();

		if (!m_bLoadedIni)
		{
			m_MainMenuBar->LoadProjectIniFile();
			m_bLoadedIni = true;
		}
		m_MainMenuBar->OnImGuiRender(DeltaTime);
		m_SceneHierarchyPanel->OnImGuiRender();
		m_ContentBrowserPanel->OnImGuiRender();
		m_Toolbar->OnImGuiRender();
		m_QuestManagerWindow->OnImGuiRender();
		m_DatabaseWindow->OnImGuiRender();
		m_AssetRegistryWindow->OnImGuiRender();
		m_InventoryDatabase->OnImGuiRender();
		m_NodeEditorManager->RenderWindows(DeltaTime);
		m_Viewport->OnImGuiRender(DeltaTime,m_FrameBuffer, m_EditorCamera,0);
		m_UIEditorWindow->OnImGuiRender();
		m_Panel->OnImGuiRender(DeltaTime);
		m_LogWindow->OnImGuiRender();
	}

	void EditorLayer::OnEvent(Event& Event) 
	{
		EventDispatcher Dispatcher(Event);

		Dispatcher.Dispatch<RendererChangeEvent>(BIND_EVENT_FN(EditorLayer::OnRendererChanged));

		m_FrameBuffer->OnEvent(Event);
		m_MainMenuBar->OnEvent(Event);
		m_Viewport->OnEvent(Event);
		m_EditorCamera.OnEvent(Event);
		m_ContentBrowserPanel->OnEvent(Event);
		m_Toolbar->OnEvent(Event);
	}

	bool EditorLayer::OnRendererChanged(RendererChangeEvent& E)
	{
		GraphicsContext* Context = App::Get().GetDeviceManager().GetWindow().GetGraphicsContext();
		m_FrameBuffer.reset();
#ifdef WIN32
		MONITORINFOEX MonInfo{};
		MonInfo.cbSize = sizeof(MonInfo);
		GetMonitorInfo(MonitorFromWindow(App::Get().GetDeviceManager().GetWindow().GetWin32Window(), MONITOR_DEFAULTTONEAREST), &MonInfo);
		FrameBufferSpecification FbSpec;
		FbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::DEPTH24STENCIL8 };
		//FbSpec.Width = App::Get().GetDeviceManager().GetWindow().GetWidth();
		//FbSpec.Height = App::Get().GetDeviceManager().GetWindow().GetHeight();
		FbSpec.Width = 1280;
		FbSpec.Height = 720;

#else
		FrameBufferSpecification FbSpec;
		FbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::DEPTH24STENCIL8 };
		FbSpec.Width = 1280;
		FbSpec.Height = 720;
#endif
		m_FrameBuffer = FrameBuffer::Create(FbSpec);
		return false;
	}
}

#endif //AG_DIST