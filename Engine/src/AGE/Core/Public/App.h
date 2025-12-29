#pragma once

#include "Core.h"
#include "DeltaTime.h"
#include "Events/Public/Event.h"
#include "Events/Public/ApplicationEvent.h"
#include "Events/Public/GameEvent.h"
#include "Events/Public/RendererEvent.h"
#include "ImGui/Public/ImGuiLayer.h"
#include "Scene/Public/ScriptableEntity.h"
#include "Core/Public/ScriptableComponentStack.h"
#include "Assets/Public/AssetManager.h"

#include "LayerStack.h"
#include "Project/Public/Project.h"
#include "Render/Public/GraphicsContext.h"
#include "DeviceManager.h"
#include "VisualScripting/Public/NodeEditorManager.h"


namespace AGE
{



	enum TargetPlatform : uint8_t
	{
		Windows = 0,
		Linux,
		Mac,
		Swtich,
		PlayStation4,
		PlayStation5
	};

	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			CoreLogger::Info("Argument Count: {}", Count);
			if (index > Count)
			{
				CoreLogger::Error("Array out of Index!");
				return nullptr;
			}

			return Args[index];
		}
	};

	struct AppConfig
	{
		std::filesystem::path ProjectBasePath;
		std::filesystem::path CurrentProjectPath;
		std::filesystem::path EditorAssetPath;
		std::filesystem::path LogPath;
		std::filesystem::path GameContentPath;
		std::filesystem::path DefaultFontPath;

	};

	class AGE_API App
	{

	public:
		App(const std::string& name = "AGE App", ApplicationCommandLineArgs Args = ApplicationCommandLineArgs());
		virtual ~App();

		void Init();
		void InitRenderer();
		void InitLayers();
		void LoadAssets();
		void Shutdown();

		void Run();

		void Close();

		void OnEvent(Event& E);

		void PushLayer(Layer* Layer);
		
		void PushOverlay(Layer* Layer);

		void PushScriptableComp(ScriptableEntity* Comp);


		inline DeviceManager& GetDeviceManager() { return *m_DeviceManager; }

		inline static App& Get() { return *s_Instance; }
		
		ApplicationCommandLineArgs GetCommandLineArgs() const { return m_CommandLineArgs; }

		inline ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		uint16_t GetTargetPlatform() { return m_Target; }
		void SetTargetPlatform(uint16_t Target) { m_Target = (TargetPlatform)Target; }

		AppConfig& GetAppConfig() {return m_AppConfig;}

		Ref<Project>& GetProject() { return m_Project; }

		void SetProject(Ref<Project> Proj) { m_Project = Proj; }

		void GetDirectXErrorMessages();
	private:
		
		bool OnWindowClose(WindowCloseEvent& E);
		bool OnWindowResize(WindowResizeEvent& E);
		bool OnFramebufferResize(FramebufferResizeEvent& E);
		bool OnRendererChanged(RendererChangeEvent& E);
		bool OnProjectCreated(ProjectCreatedEvent& E);
		bool OnProjectLoaded(ProjectLoadedEvent& E);

		void LoadScenes();
		void LoadShaders();
		void LoadFonts();
		void LoadTextures();
		void LoadSoundBanks();
		void LoadAsepriteFiles();

	private:

		Scope<DeviceManager> m_DeviceManager;
		ImGuiLayer* m_ImGuiLayer;


		bool m_Running = false;

		bool m_Minimized = false;

		LayerStack m_LayerStack;

		GameFramework::ScriptableCompStack m_CompStack;

		AppConfig m_AppConfig;

		static App* s_Instance;

		float m_CurrentFrame;
		TimeStep m_DeltaTime;
		float m_LastFrame = 0.f;

		bool m_PlayedTheme = false;
		bool bShowNewProjectMenu = true;
		bool bBlockThisFrame = false;
		const uint64_t MAIN_MENU_GAME_OBJECT = 100;

		std::vector<std::thread> m_Threads;

		TargetPlatform m_Target = TargetPlatform::Windows;
		Ref<Project> m_Project = nullptr;
		ApplicationCommandLineArgs m_CommandLineArgs;

		Scope<AssetManager> m_AssetManager = nullptr;
		std::vector<std::thread> m_AssetLoadThreads;
		std::mutex Mutex;
	};
	// Defined in CLIENT
	App* CreateApp(ApplicationCommandLineArgs Args);
}


