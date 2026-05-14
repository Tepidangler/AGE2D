#include "AGEpch.hpp"
#include "App.h"
#include "Render/Public/Renderer.h"
#include "Video/Public/AGEVideo.h"
#include "Debug/Public/Instrumentor.h"
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

	/**
 * Constructor for the App class. Initializes an instance of the application with a name and command line arguments.
 *
 * @param name The name of the application.
 * @param Args Command line arguments provided when starting the application.
 * 
 * @return None
 */
/**
 * Constructor for the App class. Initializes an instance of the application with a name and command line arguments.
 * 
 * @param name The name of the application.
 * @param Args Command line arguments provided when starting the application.
 * 
 * @return None
 */
App::App(const std::string& name, ApplicationCommandLineArgs Args)
	{
		AGE_PROFILE_FUNCTION();

		CoreLogger::Assert(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_CommandLineArgs = Args;
#ifdef AG_PLATFORM_WINDOWS
		char** Buffer = new char*;
		size_t BufferCount = 0;
		_dupenv_s(Buffer, &BufferCount, "USERPROFILE");
		m_AppConfig.ProjectBasePath = std::string(Buffer[0]) + "/OneDrive/Documents/AGEProjects";
		delete Buffer;
#elif defined(AG_PLATFORM_LINUX)
		std::string BasePath{std::getenv("HOME")};
		m_AppConfig.ProjectBasePath = std::string{ BasePath + "/ageprojects"};
#elif defined(AG_PLATFORM_MACOS)
		std::string BasePath{std::getenv("HOME")};
		m_AppConfig.ProjectBasePath = std::string{ BasePath + "/AGEProjects"};
#endif

		if (m_CommandLineArgs.Count < 3)
		{
			bShowNewProjectMenu = true;
		}

		if (!m_CommandLineArgs.Args[1])
		{

		}
		else
		{
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



	}



	/**
 * @brief Destructor for the App class.
 * 
 * This function is responsible for cleaning up any resources that were acquired during the lifetime of an instance of this class, such as memory or file handles. It calls the Shutdown() method to perform these cleanups.
 */
/**
 * @brief Destructor for the App class.
 * 
 * This function is responsible for cleaning up any resources that were acquired during the lifetime of an instance of this class. In this case, it calls the Shutdown() method to ensure all system resources are properly released and cleaned up.
 * 
 * @return void
 */
App::~App()
	{
		Shutdown();
	}

	/**
 * @brief Initializes the application. This function sets up various components of the app such as device manager, asset manager and ImGui layer.
 * 
 * It creates a DeviceManager instance with an AudioEngineType of AGESoundEngine. The event callback for this is set to App::OnEvent.
 * 
 * In non-distribution builds, no further setup is performed. However, in distribution builds, it initializes the AssetManager and loads a .AGEpak file.
 * 
 * It then pushes an ImGuiLayer onto the layer stack and attaches it to the NewProjectLayer if bShowNewProjectMenu is true. Finally, it sets m_Running to true.
 */

void App::Init()
	{
		m_DeviceManager = CreateScope<DeviceManager>(AudioEngineType::AGESoundEngine);
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

	/**
 * @brief Initializes the renderer.
 * 
 * This function is used to initialize the Renderer by calling its Init method. It sets up any necessary resources for rendering, such as shaders and textures.
 * 
 * @return void
 */
/**
 * @brief Initializes the Renderer module.
 * 
 * This function is used to initialize the Renderer module by calling the Init() function from the Renderer class.
 * It sets up any necessary resources for rendering, such as setting up OpenGL context or initializing shaders and textures.
 *
 * @return void
 */
void App::InitRenderer()
	{
		Renderer::Init();
	}

	/**
 * @brief Initializes and attaches all layers in the layer stack.
 * 
 * This function iterates over each layer in the m_LayerStack, checks if its name is either "NewProjectLayer" or "ImGuiLayer",
 * and skips these two special layers. For other layers, it calls their Init() method to initialize them and then OnAttach() to attach them. 
 * The variable bBlockThisFrame is also set to false at the end of this function.
 * 
 * @return void
 */
/**
 * @brief Initializes and attaches all layers in the layer stack.
 * 
 * This function iterates over each layer in the m_LayerStack vector, checks if its name is either "NewProjectLayer" or "ImGuiLayer",
 * and skips these two special layers. For other layers, it calls Init() to initialize them and OnAttach() to attach them to the application. 
 * It also sets bBlockThisFrame to false at the end of this function.
 * 
 * @return void
 */
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

	/**
 * @brief Loads assets asynchronously in separate threads.
 * 
 * This function starts three additional threads to load scenes, sound banks and Aseprite files respectively. After starting the threads, it detaches them so that they run independently of the main thread. Finally, it calls `LoadTextures` and `LoadShaders` functions to load textures and shaders.
 * 
 * @return void
 */
/**
 * @brief Loads assets in separate threads for concurrent loading.
 * 
 * This function starts three additional threads to load scenes, sound banks and Aseprite files concurrently. It then detaches these threads so they run independently of the main thread. After that, it calls `LoadTextures` and `LoadShaders` functions to finish the asset loading process.
 * 
 * @return void
 */
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

	/** 
 * @brief This function is used to shutdown the application. It sets a flag indicating that the program is no longer running, and then shuts down the renderer.
 * 
 * @param None
 * @return void
 */
/** 
 * @brief This function is used to shutdown the application. It sets a flag indicating that the program is no longer running, and then shuts down the renderer.
 * @return void
 */
void App::Shutdown()
	{
		bProgramRunning.store(false);
		std::unique_lock<std::mutex> Lock(Mutex);

		Renderer::Shutdown();
	}

	/**
 * @brief Handles an event dispatched by the application.
 * 
 * This function is responsible for dispatching events to all layers and components in the application. It uses an EventDispatcher object to handle different types of events, such as WindowCloseEvent, WindowResizeEvent, FramebufferResizeEvent, RendererChangeEvent, ProjectCreatedEvent, and ProjectLoadedEvent.
 * 
 * @param E Reference to the event that needs to be handled.
 */
/**
 * @brief Handles an event dispatched by the application.
 *
 * This function is responsible for dispatching events to all layers and components in the application's layer stack. 
 * It uses an EventDispatcher object to handle different types of events such as WindowCloseEvent, WindowResizeEvent, FramebufferResizeEvent, RendererChangeEvent, ProjectCreatedEvent, and ProjectLoadedEvent.
 * The function also checks for specific conditions like if the NewProjectLayer is shown or if event handling should be blocked in the current frame. 
 * It iterates over the layer stack from back to front and calls OnEvent on each layer until an event has been handled. 
 * Similarly, it does this for components as well. If an event gets handled during any of these iterations, the loop breaks early.
 *
 * @param E The event to be dispatched.
 */
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

	/**
 * @brief Pushes a layer onto the stack and attaches it.
 * 
 * This function pushes a given Layer object onto the m_LayerStack, which is essentially a stack of layers used in an application. The OnAttach() method for this layer will be called to initialize it.
 * @param Layer Pointer to the Layer that needs to be pushed and attached.
 */
/** 
 * @brief Pushes a layer onto the application's layer stack.
 * 
 * This function pushes a given Layer object into the m_LayerStack of the App class. The layer is added at the top of the stack, and will be processed last during rendering.
 * 
 * @param[in] Layer Pointer to the Layer object that needs to be pushed onto the stack.
 */
void App::PushLayer(Layer* Layer)
	{
		AGE_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(Layer);
		//Layer->OnAttach();
	}

	/** 
 * @brief Pushes an overlay layer onto the stack and calls its OnAttach() function.
 * 
 * This function pushes a given Layer object into the m_LayerStack, which is assumed to be of type LayerStack. The Layer's OnAttach() function is then called.
 * 
 * @param[in] Layer Pointer to the Layer object that will be pushed onto the stack and its OnAttach() function will be called.
 */
/** 
 * @brief Pushes an overlay layer onto the stack and calls its OnAttach function.
 * 
 * This function pushes a given Layer object into the m_LayerStack, which is assumed to be of type LayerStack. It then calls the OnAttach() function on this Layer object.
 * The AGE_PROFILE_FUNCTION macro is used for profiling purposes and should not affect the functionality of the application.
 * 
 * @param[in] Layer Pointer to a Layer object that will be pushed onto the stack.
 */
void App::PushOverlay(Layer* Layer)
	{
		AGE_PROFILE_FUNCTION();
		m_LayerStack.PushOverlay(Layer);
		Layer->OnAttach();
	}

	/** 
 * @brief Pushes a ScriptableEntity component onto the stack.
 * 
 * This function pushes a given ScriptableEntity component onto the m_CompStack, which is likely to be a stack of components for some kind of scripting system or similar use case. The parameter Comp should be an instance of a class that inherits from the ScriptableEntity base class.
 * 
 * @param Comp Pointer to the ScriptableEntity component to push onto the stack.
 * @return void No return value.
 */
/** 
 * @brief Pushes a ScriptableEntity component onto the stack.
 * 
 * This function takes in a pointer to a ScriptableEntity object and pushes it into the m_CompStack, which is likely a stack of components for some kind of application.
 * 
 * @param Comp A pointer to the ScriptableEntity component that will be pushed onto the stack.
 */
void App::PushScriptableComp(ScriptableEntity* Comp)
	{
		m_CompStack.PushComponent(Comp);
	}

	/**
 * @brief This function retrieves DirectX error messages.
 * 
 * The function does not take any parameters and returns void. It is designed to handle the retrieval of error messages from the DirectX API, which can be useful for debugging purposes. However, it doesn't provide any specific information about the errors that might occur during its execution. For more detailed error handling, consider using other functions or classes provided by the DirectX SDK.
 * 
 * @return void
 */
/**
 * @brief This function retrieves DirectX error messages.
 * 
 * The function does not take any parameters and returns void. It is designed to handle the retrieval of error messages from the DirectX library, which can be useful for debugging purposes. However, it doesn't provide specific information about the errors that have occurred. For this, additional functions or methods might be needed.
 * 
 * @return Void
 */
void App::GetDirectXErrorMessages()
	{

	}

	

void App::Run()
	{
		Init();
		Layer* NewProjLayer = m_LayerStack.GetLayerByName("NewProjectLayer");
		AGE_PROFILE_FUNCTION();
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
	/**
 * @brief Loads and initializes all shader files from specified directories.
 * @return void
 */
/**
 * @brief LoadShaders function loads shader programs based on the current RendererAPI.
 * It initializes the renderer and then loads all vertex shaders from a specified directory. 
 * If the RendererAPI is not OpenGL, it asserts false with an error message indicating that the RendererAPI is not currently implemented.
 * @return void
 */
void App::LoadShaders()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::OpenGL:
		{
			InitRenderer();
			//for (auto& S : std::filesystem::recursive_directory_iterator(m_AppConfig.EditorAssetPath.string() + "Shaders/GLSL/Vertex"))
			//{
			//	if (!S.is_directory())
			//	{
			//		AssetManager::Get().LoadShader(S.path().string());
			//	}
			//}
			break;
		}
		default:
		{
			CoreLogger::Assert(false, "Renderer is not currently Implemented!");
		}
		}
	}
	/**
 * @brief Loads all textures from the game content directory.
 * 
 * This function iterates over all files in the "Textures" subdirectory of the game content path, and loads each one as a texture using AssetManager::LoadTexture().
 * If bProgramRunning is true (i.e., if the program is currently running), it will load textures; otherwise, it will break out of the loop early.
 * 
 * @return void
 */
/**
 * @brief Loads all textures from the game content directory.
 * 
 * This function iterates over every file in the "Textures" subdirectory of the game content path, and loads each texture into the AssetManager if the program is currently running (i.e., bProgramRunning is true). If the program is not running, it stops loading textures immediately.
 * 
 * @return void
 */
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
	/**
 * @brief Loads all Aseprite files from the game content directory.
 * 
 * This function iterates over all files in the "Aesprite" subdirectory of the game content path, and loads each one using AssetManager::LoadAsepriteFile().
 * It currently does not handle loading directories or recursive traversal, so it only loads files directly under the "Aesprite" directory. 
 * If there are no Aseprite files in this location, it will do nothing and return immediately.
 * 
 * @return void
 */
/**
 * @brief Loads all Aseprite files from the game content directory.
 * 
 * This function iterates over each file in the "Aesprite" subdirectory of the game content path, and loads them using AssetManager::LoadAsepriteFile().
 * It currently does not handle loading directories or recursive traversal, so it only loads files directly under the "Aesprite" directory. 
 * If more complex behavior is needed in the future, this function should be updated accordingly.
 */
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

	/**
 * @brief Closes the application by setting m_Running to false.
 *
 * This function sets the member variable m_Running to false, effectively closing the application.
 * It does not return anything and has no parameters.
 * 
 * @return void
 */
/**
 * @brief Closes the application by setting m_Running to false.
 *
 * This function sets the member variable m_Running of an instance of the App class to false, effectively closing the application.
 * It does not return any value and has no parameters.
 *
 * @return void
 */
void App::Close()
	{
		m_Running = false;
	}

	/**
 * @brief This function is called when a window close event occurs. It sets the running flag to false, indicating that the application should stop running.
 * 
 * @param E A reference to the WindowCloseEvent object representing the event.
 * @return Returns true if the operation was successful, otherwise it returns false. In this case, since we always return true, the confidence level is 1.0.
 */
/**
 * @brief Handles the window close event.
 * 
 * This function is called when a window is closed by the user or system. It sets the running flag to false, indicating that the application should terminate.
 * 
 * @param E The WindowCloseEvent object containing information about the event.
 * @return Returns true if the operation was successful, otherwise returns false. In this case, it always returns true as there are no operations that could fail.
 */
bool App::OnWindowClose(WindowCloseEvent& E)
	{
		m_Running = false;
		//WwiseObj->UnregisterGameObj((uint64_t)10);
		//WwiseObj->UnloadBank(AK::BANKS::INIT);
		//WwiseObj->UnloadBank(AK::BANKS::MM);
		//WwiseObj->~Wwise();
		return true;
	}
	/**
 * @brief Handles the window resize event.
 *
 * This function is triggered when the size of the application's window changes. It checks if the new width or height are zero, 
 * indicating a minimized state. If so, it sets `m_Minimized` to true and returns false. Otherwise, it sets `m_Minimized` to false 
 * and calls Renderer::OnWindowResize with the new dimensions before returning false.
 *
 * @param E The window resize event object.
 * @return Always returns false as per current implementation.
 */
/**
 * @brief Handles the window resize event.
 *
 * This function is called when the size of the application's window changes. It checks if the new width or height are zero, 
 * indicating a minimized state. If so, it sets `m_Minimized` to true and returns false. Otherwise, it sets `m_Minimized` to false 
 * and calls Renderer::OnWindowResize with the new dimensions before returning false.
 *
 * @param E The window resize event object.
 * @return Always returns false as per current implementation.
 */
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
	/**
 * @brief Handles the framebuffer resize event.
 *
 * This function is called when the application's framebuffer size changes, such as when the window is resized. 
 * It updates the renderer and the m_FramebufferSize member variable with the new width and height.
 *
 * @param E The FramebufferResizeEvent that triggered this function.
 * @return Always returns false. This function does not handle errors or exceptions, so it always returns false.
 */
/**
 * @brief Handles the framebuffer resize event by updating the renderer and storing the new size in m_FramebufferSize.
 * 
 * This function is triggered when the window's framebuffer (the actual pixels on screen) gets resized. It updates the Renderer with the new width and height, then stores these values in m_FramebufferSize for later use.
 * 
 * @param E The FramebufferResizeEvent that was fired. Contains information about the new size of the framebuffer.
 * @return Always returns false as there are no errors to handle in this function.
 */
bool App::OnFramebufferResize(FramebufferResizeEvent& E)
	{
		Renderer::OnFramebufferResize(E.GetWidth(), E.GetHeight());
		m_FramebufferSize = {static_cast<float>(E.GetWidth()), static_cast<float>(E.GetHeight())};
		return false;
	}

	/**
 * @brief Handles the event of a renderer change.
 * 
 * This function is triggered when the application's current renderer changes. It receives an instance of RendererChangeEvent as its parameter, which contains information about the new renderer.
 * 
 * @param E An instance of RendererChangeEvent containing details about the new renderer.
 * @return Returns false to indicate that no further action is needed after this event.
 */
/**
 * @brief Handles the event of a renderer change.
 * 
 * This function is called when the application's current renderer changes. The event details are passed as an argument.
 *
 * @param E A reference to the RendererChangeEvent that describes the change.
 * @return Returns true if the event was handled successfully, false otherwise.
 */
bool App::OnRendererChanged(RendererChangeEvent& E)
	{
		return false;
	}

	/**
 * @brief This function is triggered when a new project is created. It initializes the AssetManager, loads assets, and sets up the layer stack for the newly created project.
 * 
 * @param E A reference to the ProjectCreatedEvent object containing information about the newly created project.
 * 
 * @return Returns false as this function does not have a meaningful return value in this context.
 */
/**
 * @brief This function is triggered when a new project is created. It initializes the AssetManager, loads assets, and sets up the layer stack for the newly created project.
 * 
 * @param E A reference to the ProjectCreatedEvent object containing information about the newly created project.
 * 
 * @return Returns false as no further action is needed after this function call.
 */
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

	/**
 * @brief This function is triggered when a project is loaded. It sets up the AssetManager, loads assets, and initializes layers.
 * 
 * @param E A reference to the ProjectLoadedEvent that contains information about the loaded project.
 * 
 * @return Returns false as this function does not have any meaningful return value in the context of its purpose.
 */
/**
 * @brief This function is triggered when a project is loaded. It sets up the AssetManager, loads assets, and initializes layers.
 * 
 * @param E A reference to the ProjectLoadedEvent that contains information about the loaded project.
 * 
 * @return Returns false as this function does not have any meaningful return value in this context.
 */
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
