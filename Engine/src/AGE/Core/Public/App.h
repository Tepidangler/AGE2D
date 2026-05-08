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
//#include "VisualScripting/Public/NodeEditorManager.h"


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

		/**
 * @brief This function returns the argument at a given index.
 * 
 * The function takes an integer as input and checks if it is within the valid range of indices for the array. If the index is out of bounds, it logs an error message and returns nullptr. Otherwise, it returns the argument at the specified index.
 * 
 * @param index The zero-based index of the argument to be returned.
 * @return A pointer to a constant character string representing the argument at the given index. If the index is out of bounds, this function will return nullptr.
 */
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
		std::filesystem::path GameSourcePath;
		std::filesystem::path GameShadersPath;
		std::filesystem::path GameScenesPath;
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


		/**
 * @brief Returns a reference to the device manager instance.
 *
 * This function returns a reference to the device manager instance that is currently in use by the application. The returned object can be used to interact with the hardware devices managed by the system.
 * 
 * @return A reference to the DeviceManager instance.
 */
inline DeviceManager& GetDeviceManager() { return *m_DeviceManager; }

		/**
 * @brief This function returns a reference to the singleton instance of the App class.
 * @return A reference to the singleton instance of the App class.
 */
inline static App& Get() { return *s_Instance; }
		
		/**
 * @brief Retrieves the command line arguments of the application.
 * @return An instance of ApplicationCommandLineArgs containing all the command line arguments.
 */
ApplicationCommandLineArgs GetCommandLineArgs() const { return m_CommandLineArgs; }

		/**
 * @brief This function returns the ImGui layer of the application.
 * @return Pointer to the ImGuiLayer object if it exists, nullptr otherwise.
 */
inline ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		/**
 * @brief This function returns the target platform.
 *
 * @return uint16_t The target platform as a uint16_t value.
 */
uint16_t GetTargetPlatform() { return m_Target; }
		/**
 * @brief Sets the target platform to a specified value.
 *
 * This function sets the member variable `m_Target` of the class to a new value, which represents the target platform.
 * The parameter `Target` is an unsigned 16-bit integer that specifies the new target platform.
 *
 * @param Target The new target platform as an unsigned 16-bit integer.
 */
void SetTargetPlatform(uint16_t Target) { m_Target = (TargetPlatform)Target; }

		/**
 * @brief Returns the application configuration object.
 *
 * This function returns a reference to the AppConfig object that holds all the configurations for the application.
 * The returned object can be used to modify the application's settings.
 * 
 * @return A reference to the AppConfig object.
 */
AppConfig& GetAppConfig() {return m_AppConfig;}

		/**
 * @brief Returns a reference to the Project object.
 *
 * This function returns a reference to the Project object stored in the member variable 'm_Project'. It allows for direct manipulation of this data if required.
 *
 * @return A reference to the Project object.
 */
Ref<Project>& GetProject() { return m_Project; }

		/**
 * @brief Returns the framebuffer size of the application.
 * @return A constant reference to a Vector2 object representing the current framebuffer size.
 */
const Vector2& GetFramebufferSize() {return m_FramebufferSize; }

		/**
 * @brief Sets the project object.
 *
 * This function sets the value of the member variable 'm_Project' to the input parameter 'Proj'. It takes a reference to a Project object and assigns it to 'm_Project'. 
 *
 * @param Proj A Ref<Project> object representing the new project.
 */
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

		Vector2 m_FramebufferSize = {1280.f, 720.f};

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


