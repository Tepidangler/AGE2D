#include "AGEpch.hpp"
#include "App.h"
#include "Render/Public/Renderer.h"
#include "Video/Public/AGEVideo.h"
#include "Input.h"
#include "Core/Public/ScriptableComponentStack.h"
#include "Audio/Fmod/Public/FmodEngine.h"
#include <imgui.h>
#include <GLFW/glfw3.h>

#include "Serializers/Public/IniReader.h"

#define MAIN_MENU_GAME_OBJECT 10
namespace AGE
{

	App* App::s_Instance = nullptr;

	std::atomic_bool Active = true;
	std::atomic_bool Scene_Flag = false;
	static std::atomic<bool> bProgramRunning = true;
	static std::atomic<bool> bLoadingFonts = true;

	App::App(const std::string& name, ApplicationCommandLineArgs Args)
	{
		AGE_PROFILE_FUNCTION();

		AGE_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;
		m_CommandLineArgs = Args;
		m_AppConfig.ProjectBasePath = std::string(getenv("USERPROFILE")) + "/OneDrive/Documents/AGEProjects";

		if (m_CommandLineArgs.Count < 3)
		{
			bShowNewProjectMenu = true;
		}

		IniReader ini(m_CommandLineArgs.Args[1]);
		bool HasMulti;
		m_AppConfig.EditorAssetPath = ini.Read("Paths", "EditorAssetsPath",HasMulti);
		m_AppConfig.DefaultFontPath = m_AppConfig.EditorAssetPath.string() + "/Fonts/Open_Sans/static/OpenSans-Regular.ttf";
		if (HasMulti)
		{
			std::vector<std::string> Values  = ini.ReadAll("Paths", "EditorAssetsPath");
			return;
		}


	}



	App::~App()
	{
		Shutdown();
	}

	void App::Init()
	{
		m_DeviceManager = Scope<DeviceManager>(DeviceManager::Create(AudioEngineType::FModEngine));
		m_DeviceManager->GetWindow().SetEventCallback(BIND_EVENT_FN(App::OnEvent));
		//m_DeviceManager->GetXInput().SetEventCallback(BIND_EVENT_FN(App::OnEvent));
#if !AG_DIST


#else
		m_AssetManager = CreateScope<AssetManager>();
		//TODO: Load .AGEpak file
#endif


		m_ImGuiLayer = new ImGuiLayer;

		PushOverlay(m_ImGuiLayer);
		if (bShowNewProjectMenu)
		{
			Layer* NewProj =m_LayerStack.GetLayerByName("NewProjectLayer");
			NewProj->Init();
			NewProj->OnAttach();
		}

		m_Running = true;
	}

	void App::InitRenderer()
	{
		Renderer::Init();
	}

	void App::InitLayers()
	{
		for (auto& L : m_LayerStack)
		{
			if (L->GetName() == "NewProjectLayer" || L->GetName() == "ImGuiLayer")
			{
				continue;
			}
			L->Init();
			L->OnAttach();
		}
		bBlockThisFrame  = false;
	}

	void App::LoadAssets()
	{
		m_AssetLoadThreads.emplace_back(std::thread(&App::LoadScenes, this));
		m_AssetLoadThreads.emplace_back(std::thread(&App::LoadSoundBanks, this));
		m_AssetLoadThreads.emplace_back(std::thread(&App::LoadAsepriteFiles, this));
		for (auto& Th : m_AssetLoadThreads)
		{
			Th.detach();
		}
		LoadTextures();
		LoadShaders();
	}

	void App::Shutdown()
	{
		bProgramRunning.store(false);
		std::unique_lock<std::mutex> Lock(Mutex);

		Renderer::Shutdown();
	}

	void App::OnEvent(Event& E)
	{

		AGE_PROFILE_FUNCTION();
		EventDispatcher Dispatcher(E);

		Dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(App::OnWindowClose));
		Dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(App::OnWindowResize));
		Dispatcher.Dispatch<FramebufferResizeEvent>(BIND_EVENT_FN(App::OnFramebufferResize));
		Dispatcher.Dispatch<RendererChangeEvent>(BIND_EVENT_FN(App::OnRendererChanged));
		Dispatcher.Dispatch<ProjectCreatedEvent>(BIND_EVENT_FN(App::OnProjectCreated));
		Dispatcher.Dispatch<ProjectLoadedEvent>(BIND_EVENT_FN(App::OnProjectLoaded));

		if (bShowNewProjectMenu)
		{
			Layer* NewProj =m_LayerStack.GetLayerByName("NewProjectLayer");
			NewProj->OnEvent(E);
			return;
		}
		if (bBlockThisFrame)
		{
			return;
		}

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(E);
			if (E.Handled)
			{
				break;
			}
				
		}

		for (auto it = m_CompStack.end(); it != m_CompStack.begin();)
		{
			(*--it)->OnEvent(E);
			if (E.Handled)
			{
				break;
			}
		}



	}

	void App::PushLayer(Layer* Layer)
	{
		AGE_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(Layer);
		//Layer->OnAttach();
	}

	void App::PushOverlay(Layer* Layer)
	{
		AGE_PROFILE_FUNCTION();
		m_LayerStack.PushOverlay(Layer);
		Layer->OnAttach();
	}

	void App::PushScriptableComp(ScriptableEntity* Comp)
	{
		m_CompStack.PushComponent(Comp);
	}

	void App::GetDirectXErrorMessages()
	{

	}

	void App::Run()
	{
		Init();
		Layer* NewProjLayer = m_LayerStack.GetLayerByName("NewProjectLayer");
		AGE_PROFILE_FUNCTION("RunLoop");
		{
			while (m_Running)
			{
				m_CurrentFrame = (float)glfwGetTime();  //Platform::GetTime();
				m_DeltaTime = m_CurrentFrame - m_LastFrame;
				m_LastFrame = m_CurrentFrame;

				if (!m_Minimized)
				{
					if (bShowNewProjectMenu)
					{
						m_ImGuiLayer->Begin();
						NewProjLayer->OnImGuiRender(m_DeltaTime);
						m_ImGuiLayer->End();
						m_DeviceManager->UpdateWindow();
						continue;
					}

					{
						AGE_PROFILE_SCOPE("Layer Tick");
						if (!bBlockThisFrame)
						{
							m_ImGuiLayer->Begin();
							for (Layer* L : m_LayerStack)
							{
								L->OnUpdate(m_DeltaTime);
								L->OnImGuiRender(m_DeltaTime);
							}
							m_ImGuiLayer->End();
						}
						else
						{
							InitLayers();
						}

					}
				}

				m_DeviceManager->UpdateWindow();
			}
		}
	}

	void App::LoadScenes()
	{
		std::filesystem::path ScenesPath = m_AppConfig.CurrentProjectPath.string() + "/Scenes";
		if (!std::filesystem::is_directory(ScenesPath))
		{
			CoreLogger::Error("Unable to Loads Scenes! \n\t Scenes path: {} Does not exist!", ScenesPath.string());
			return;
		}
		for (auto F : std::filesystem::recursive_directory_iterator(ScenesPath))
		{
			if (bProgramRunning.load())
			{
				AGE::Ref<Scene> S = AssetManager::Get().LoadScene(F);
				S->SetEventCallback(BIND_EVENT_FN(App::OnEvent));
			}
			else
			{
				break;
			}
		}
	}
	void App::LoadShaders()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::OpenGL:
		{
			for (auto& S : std::filesystem::recursive_directory_iterator(m_AppConfig.EditorAssetPath.string() + "/Shaders/GLSL/Vertex"))
			{
				if (!S.is_directory())
				{
					AssetManager::Get().LoadShader(S.path().string());
				}
			}
			InitRenderer();
			break;
		}
		default:
		{
			AGE_CORE_ASSERT(false, "Renderer is not currently Implemented!")
		}
		}
	}
	void App::LoadTextures()
	{
		for (auto& T : std::filesystem::recursive_directory_iterator(AssetManager::Get().GetGameContentPath().string() + "/Textures"))
		{
			if (!T.is_directory())
			{
				if (bProgramRunning.load())
				{
					AssetManager::Get().LoadTexture(T);
				}
				else
				{
					break;
				}
			}
		}
	}
	void App::LoadSoundBanks()
	{
		switch (App::Get().GetDeviceManager().GetAudioManager().GetAudioEngineType())
		{
		case AudioEngineType::AGESoundEngine:
		{
			for (auto& S : std::filesystem::recursive_directory_iterator(AssetManager::Get().GetGameContentPath().string() + "/Sounds"))
			{
				if (!S.is_directory())
				{
					if (bProgramRunning.load())
					{
						AssetManager::Get().LoadSound(S);
					}
					else
					{
						break;
					}
				}
			}
			break;
		}

		case AudioEngineType::WWiseEngine:
		{
			for (auto& S : std::filesystem::directory_iterator(AssetManager::Get().GetGameContentPath().string() + "/Sounds/Banks"))
			{
				if (!S.is_directory())
				{
					if (bProgramRunning.load())
					{
						AssetManager::Get().LoadSoundbank(S);
					}
					else
					{
						break;
					}
				}
			}
			break;
		}

		case AudioEngineType::FModEngine:
		{
			for (auto& S : std::filesystem::directory_iterator(AssetManager::Get().GetGameContentPath().string() + "/Sounds/Banks"))
			{
				for (auto& F : std::filesystem::directory_iterator(S))
				{
					if (!F.is_directory())
					{
						if (bProgramRunning.load())
						{
							AssetManager::Get().LoadSoundbank(F);
						}
						else
						{
							break;
						}
					}
				}

			}

			m_DeviceManager->GetAudioManager().GetAudioEngine()->LoadEvents();
			break;
		}
		}

	}
	void App::LoadAsepriteFiles()
	{
		//for (auto& A : std::filesystem::recursive_directory_iterator(AssetManager::Get().GetGameContentPath().string() + "/Aesprite"))
		//{
		//	if (!A.is_directory())
		//	{
		//		AssetManager::Get().LoadAsepriteFile(A);
		//	}
		//}
	}

	void App::Close()
	{
		m_Running = false;
	}

	bool App::OnWindowClose(WindowCloseEvent& E)
	{
		m_Running = false;
		//WwiseObj->UnregisterGameObj((uint64_t)10);
		//WwiseObj->UnloadBank(AK::BANKS::INIT);
		//WwiseObj->UnloadBank(AK::BANKS::MM);
		//WwiseObj->~Wwise();
		return true;
	}
	bool App::OnWindowResize(WindowResizeEvent& E)
	{
		AGE_PROFILE_FUNCTION();
		if (E.GetWidth() == 0 || E.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		Renderer::OnWindowResize(E.GetWidth(), E.GetHeight());
		return false;
	}
	bool App::OnFramebufferResize(FramebufferResizeEvent& E)
	{
		Renderer::OnFramebufferResize(E.GetWidth(), E.GetHeight());
		m_FramebufferSize = {static_cast<float>(E.GetWidth()), static_cast<float>(E.GetHeight())};
		return false;
	}

	bool App::OnRendererChanged(RendererChangeEvent& E)
	{
		return false;
	}

	bool App::OnProjectCreated(ProjectCreatedEvent &E)
	{
		m_AssetManager = CreateScope<AssetManager>(m_AppConfig.GameContentPath);
		bBlockThisFrame = true;
		LoadAssets();
		bShowNewProjectMenu = false;
		Layer* NewProjLayer = m_LayerStack.GetLayerByName("NewProjectLayer");
		m_LayerStack.PopLayer(NewProjLayer);
		return false;
	}

	bool App::OnProjectLoaded(ProjectLoadedEvent &E)
	{
		m_AssetManager = CreateScope<AssetManager>(m_AppConfig.GameContentPath);
		bBlockThisFrame = true;
		LoadAssets();
		bShowNewProjectMenu = false;
		Layer* NewProjLayer = m_LayerStack.GetLayerByName("NewProjectLayer");
		m_LayerStack.PopLayer(NewProjLayer);
		InitLayers();
		return false;
	}
}
