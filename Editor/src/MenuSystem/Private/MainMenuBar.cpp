#if !AG_DIST
#include <Age.h>
#include "MenuSystem/Public/MainMenuBar.h"
#include "Editor_ImGui/Public/SceneHierarchyPanel.h"
#include "Editor_Core/Public/EditorLayer.h"
#include "Render/Public/Renderer2D.h"
#include "Parser/Public/FbxParser.h"
#include <misc/cpp/imgui_stdlib.h>
#include <cstdlib>
#include "Editor_Core/Public/CodeGen.h"

namespace AGE
{
	namespace Utils
	{
		std::string ConvertToAudioEngineName(uint16_t Engine)
		{
			switch (Engine)
			{
			case 0:
			{
				return std::string("AGESound");
			}
			case 1:
			{
				return std::string("Wwise");
			}
			case 2:
			{
				return std::string("FMod Engine");
			}
			default:
			{
				CoreLogger::Error("Invalid Audio Engine Type");
				break;
			}
			}

			return std::string("UNDEFINED");
		}

		std::string ConvertToRendererName(int Renderer)
		{
			switch (Renderer)
			{
			case 0:
			{
				return std::string("Headless (No Renderer)");
			}
			case 1:
			{
				return std::string("OpenGL");
			}
			case 2:
			{
				return std::string("DirectX11");
			}
			case 3:
			{
				return std::string("DirectX12");
			}
			default:
			{
				CoreLogger::Error("Invalid Audio Engine Type");
				break;
			}
			}

			return std::string("UNDEFINED");
		}

		uint16_t ConvertToAxisKeyBinding(const std::string& String)
		{
			if (String == "Left Joystick X")
			{
				return GamePad::Axes::GamePadAxisLeftX;
			}

			if (String == "Left Joystick Y")
			{
				return GamePad::Axes::GamePadAxisLeftY;
			}

			if (String == "Right Joystick X")
			{
				return GamePad::Axes::GamePadAxisRightX;
			}

			if (String == "Right Joystick Y")
			{
				return GamePad::Axes::GamePadAxisRightY;
			}

			if (String == "DPad Left")
			{
				return GamePad::GamePadButtonDpadLeft;
			}

			if (String == "DPad Up")
			{
				return GamePad::GamePadButtonDpadUp;
			}

			if (String == "DPad Right")
			{
				return GamePad::GamePadButtonDpadRight;
			}

			if (String == "DPad Down")
			{
				return GamePad::GamePadButtonDpadDown;
			}

			return 0xff;

		}

		uint16_t ConvertToActionKeyBinding(const std::string& String)
		{

			if (String == "Face Button Bottom")
			{
				return GamePad::GamePadButtonA;
			}

			if (String == "Face Button Right")
			{
				return GamePad::GamePadButtonB;
			}

			if (String == "Face Button Left")
			{
				return GamePad::GamePadButtonX;
			}

			if (String == "Face Button Top")
			{
				return GamePad::GamePadButtonY;
			}

			if (String == "Left Bumper Button")
			{
				return GamePad::GamePadButtonLB;
			}

			if (String == "Right Bumper Button")
			{
				return GamePad::GamePadButtonRB;
			}

			if (String == "Select Button")
			{
				return GamePad::GamePadButtonBack;
			}

			if (String == "Start Button")
			{
				return GamePad::GamePadButtonStart;
			}
			if (String == "Guide Button")
			{
				return GamePad::GamePadButtonGUIDE;
			}
			if (String == "Left Thumbstick")
			{
				return GamePad::GamePadButtonLeftThumb;
			}
			if (String == "Right Thumbstick")
			{
				return GamePad::GamePadButtonRightThumb;
			}

			return 0xff;
		}


	}

	MainMenuBar::MainMenuBar()
	{
	}
	void MainMenuBar::OnEvent(AGE::Event& E)
	{
		AGE::EventDispatcher Dispatcher(E);

		Dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(MainMenuBar::OnKeyPressed));
	}

	bool MainMenuBar::OnKeyPressed(KeyPressedEvent& E)
	{
		if (E.GetRepeatCount() > 0)
		{
			return false;
		}

		bool Control = Input::IsKeyPressed(Key::LEFT_CONTROL) || Input::IsKeyPressed(Key::RIGHT_CONTROL);
		bool Shift = Input::IsKeyPressed(Key::LEFT_SHIFT) || Input::IsKeyPressed(Key::RIGHT_SHIFT);

		switch (E.GetKeyCode())
		{
		case Key::D:
		{
			if (Control)
			{
				OnDuplicateEntity();
				break;
			}
			break;
		}
		case Key::O:
		{
			if (Control)
			{
				OpenScene();
			}
			break;
		}

		case Key::S:
		{
			if (Control)
			{
				if (Shift)
				{
					SaveAsScene();
					break;
				}
				else
				{
					SaveScene();
					break;
				}
			}
			break;
		}
		case Key::N:
		{
			if (Control)
			{
				NewScene();
			}
			break;
		}
		case Key::W:
		{

			if (Control)
			{
				App::Get().Close();
			}
		}
			break;
		}

		return false;
	}

	void MainMenuBar::OnDuplicateEntity()
	{
		if (EditorLayer::Get().m_Toolbar->GetSceneState() != SceneState::Edit)
		{
			return;
		}

		Entity SelectedEntity = EditorLayer::Get().m_SceneHierarchyPanel->GetSelectedEntity();
		if (SelectedEntity)
		{
			EditorLayer::Get().m_EditorScene->DuplicateEntity(SelectedEntity);
		}
	}

	void MainMenuBar::OnImGuiRender(AGE::TimeStep DeltaTime)
	{
		MakeMainMenuBar();
	}

	void MainMenuBar::MakeMainMenuBar()
	{

		if (ImGui::BeginMainMenuBar())
		{

			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New Project", "Ctrl+N"))
				{
					bCreateProject = true;

				}
				if (ImGui::MenuItem("New Scene", "Ctrl+Alt+N"))
				{
					NewScene();
				}
				if (ImGui::MenuItem("Open Project", "Ctrl+O"))
				{
					OpenProject();

				}
				if (ImGui::MenuItem("Open Scene", "Ctrl+Alt+O"))
				{
					OpenScene();
	
				}
				if (ImGui::MenuItem("Save Scene", "Ctrl+Alt+S"))
				{
					SaveScene();
				}
				if (ImGui::MenuItem("Save Scene As", "Ctrl+Shift+S"))
				{
					SaveAsScene();
				}
				if (ImGui::MenuItem("Close AGE Editor", "Ctrl+W"))
				{
					App::Get().Close();
				}
				ImGui::EndMenu();

			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "Ctrl+Z"))
				{

				}
				if (ImGui::MenuItem("Redo", "Ctrl+Y"))
				{

				}
				if (ImGui::MenuItem("Cut", "Ctrl+X"))
				{

				}
				if (ImGui::MenuItem("Copy", "Ctrl+C"))
				{

				}
				if (ImGui::MenuItem("Paste", "Ctrl+V"))
				{

				}
				if (ImGui::MenuItem("Duplicate", "Ctrl+D"))
				{

				}
				if (ImGui::MenuItem("Delete", "DELETE"))
				{

				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Project"))
			{
				if (ImGui::MenuItem("Change Audio Engine"))
				{
					bChooseAudioEngine = true;

				}
				if (ImGui::MenuItem("Edit Project Settings"))
				{
					bEditProjectSettings = true;
				}
				if (ImGui::MenuItem("Open Asset Registry"))
				{
					EditorLayer::Get().m_AssetRegistryWindow->RestoreWindow();
				}
				//if (ImGui::MenuItem("Import Quest File"))
				//{
				//	std::filesystem::path Path = LoadQuestFile();
				//	if (!Path.empty())
				//	{
				//		EditorLayer::Get().m_GameState->GetQuestManager()->LoadQuests(Path);
				//		if (Project::GetActive())
				//		{
				//			Project::GetActive()->GetInfo().SetQuestFilepath(Path);
				//			m_QuestFilePath = Path;
				//			SaveProject();
				//		}
				//		else
				//		{
				//			CoreLogger::Error("No Active Project, could not load Quest File!");
				//		}
				//
				//	}
				//	
				//}

				if (ImGui::MenuItem("Create Widget")) {
					CodeGen::CreateAsset("Test",AssetType::Widget);
				}
				if (ImGui::MenuItem("Build All Scenes"))
				{
					Scene::BuildAllScenes();
				}

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Window"))
			{
				if (ImGui::MenuItem("Node Editor"))
				{
					OpenNodeEditor();
				}

				if (ImGui::MenuItem("Quest Manager"))
				{
					OpenQuestManager();
				}

				if (ImGui::MenuItem("Inventory Database"))
				{
					OpenInventoryDatabase();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Tools"))
			{
				if (ImGui::Checkbox("Show Physics Colliders", &bShowPhysicsColliders))
				{
					
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Debug"))
			{
#if 0
				if (ImGui::MenuItem("Start Profiler, Ctrl+Shift+P"))
				{

				}
				if (ImGui::MenuItem("Stop Profiler, Ctrl+Alt+P"))
				{

				}
#endif
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Build"))
			{
				if (ImGui::MenuItem("Build Level"))
				{
					m_ActiveScene->BuildScene(m_ProjectFilePath);
				}
				if (ImGui::MenuItem("Build All Levels"))
				{
					Scene::BuildAllScenes();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Packaging"))
			{
				const char* TargetPlatformStrings[] = { "Windows", "Linux", "MacOS", "Nintendo Switch", "PlayStation 4", "PlayStation 5"};
				const char* CurrentTargetPlatformString = TargetPlatformStrings[(int)App::Get().GetTargetPlatform()];

				if (ImGui::BeginCombo("Target Platform", CurrentTargetPlatformString))
				{
					for (int i = 0; i < 6; i++)
					{
						bool IsSelected = CurrentTargetPlatformString == TargetPlatformStrings[i];

						if (ImGui::Selectable(TargetPlatformStrings[i], IsSelected))
						{
							CurrentTargetPlatformString = TargetPlatformStrings[i];
							App::Get().SetTargetPlatform((uint16_t)i);
						}

						if (IsSelected)
						{
							ImGui::SetItemDefaultFocus();
						}
					}

					ImGui::EndCombo();
				}

				if (ImGui::MenuItem("Package Game"))
				{
					PackageGame();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Select"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Actor"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Database"))
			{
				if (ImGui::MenuItem("Open Database"))
				{
					OpenDatabase();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Help"))
			{
				ImGui::EndMenu();
			}


			ImGui::EndMainMenuBar();

			if (bChooseAudioEngine)
			{
				ImGui::OpenPopup(ImGui::GetID("Audio Engine"));

				if (ImGui::BeginPopup("Audio Engine"))
				{
					if (ImGui::MenuItem("AGESound"))
					{
						if (App::Get().GetDeviceManager().GetAudioManager().GetAudioEngineType() != 0)
						{
							App::Get().GetDeviceManager().GetAudioManager().SwitchAudioEngine((AudioEngineType)0);
						}
						ImGui::CloseCurrentPopup();
						bChooseAudioEngine = false;
					}
					if (ImGui::MenuItem("WWise"))
					{
						if (App::Get().GetDeviceManager().GetAudioManager().GetAudioEngineType() != 1)
						{
							App::Get().GetDeviceManager().GetAudioManager().SwitchAudioEngine((AudioEngineType)1);
						}
						ImGui::CloseCurrentPopup();
						bChooseAudioEngine = false;
					}
					if (ImGui::MenuItem("FMod"))
					{
						if (App::Get().GetDeviceManager().GetAudioManager().GetAudioEngineType() != 2)
						{
							App::Get().GetDeviceManager().GetAudioManager().SwitchAudioEngine((AudioEngineType)2);
						}
						ImGui::CloseCurrentPopup();
						bChooseAudioEngine = false;
					}
					ImGui::EndPopup();
				}
			}

			if (bCreateProject)
			{
				if (ImGui::Begin("Create New Project", &bCreateProject))
				{
					ImGui::InputText("Project Name", &Project::GetActive()->GetConfig().Name);
					if (ImGui::Button("Create Project"))
					{
						bCreateProject = false;
						std::string ProjectName(Project::GetActive()->GetConfig().Name);
						NewProject(ProjectName.data());
					}
					ImGui::End();
				}

			}

			if (bEditProjectSettings)
			{
				MakeProjectConfigMenu();
			}
		}
	}

	void MainMenuBar::MakeProjectConfigMenu()
	{
		if (ImGui::Begin("Project Settings", &bEditProjectSettings))
		{
			bAxisBindingsSynced = false;
			bActionBindingsSynced = false;
			if (ImGui::CollapsingHeader("Project Data"))
			{
				ImGui::Text("Project Name"); ImGui::SameLine();
				ImGui::InputText("##ProjectName", &Project::GetActive()->GetConfig().Name);
				ImGui::Text("Audio Engine: %s", Utils::ConvertToAudioEngineName(Project::GetActive()->GetInfo().AudioEngine).c_str());
				ImGui::Text("Graphics Renderer: %s", Utils::ConvertToRendererName(Project::GetActive()->GetInfo().Renderer).c_str());
				ImGui::Text("Game Code C++ Namespace"); ImGui::SameLine();
				ImGui::InputText("##GCCN", &Project::GetActive()->GetConfig().CppNameSpace);
				ImGui::Text("Copyright Notice"); ImGui::SameLine();
				ImGui::InputText("##CN", &Project::GetActive()->GetConfig().CopyrightNotice);
				std::string CurrentSceneSelection;
				if (m_SceneNames.empty())
				{
					m_SceneNames.emplace_back(std::string("None"));
				}
				CurrentSceneSelection = m_SceneNames.front();
				ImGui::Text("Start Scene "); ImGui::SameLine();
				if (ImGui::BeginCombo("##SelectedScene", CurrentSceneSelection.c_str()))
				{
					for (size_t i = 0; i < m_SceneNames.size(); i++)
					{
						bool IsSelected = CurrentSceneSelection == m_SceneNames[i];
						if (ImGui::Selectable(m_SceneNames[i].c_str(), IsSelected))
						{
							CurrentSceneSelection = m_SceneNames[i];
						}
					}

					ImGui::EndCombo();
				}
			}
			ImGui::Separator();
			if (ImGui::CollapsingHeader("Input Bindings"))
			{
				if (ImGui::Button("Add Axis Binding"))
				{
					size_t Size = m_AxisBindingData.size();
					m_AxisBindingData.resize(Size + 1);
				}
				ImGui::SameLine();
				if (ImGui::Button("Save Axis Binding"))
				{
					SyncBindings();
				}
				DrawAxisBindings();
				ImGui::Separator();
				if (ImGui::Button("Add Action Binding"))
				{
					size_t Size = m_ActionBindingData.size();
					m_ActionBindingData.resize(Size + 1);
				}
				ImGui::SameLine();
				if (ImGui::Button("Save Action Binding"))
				{
					SyncBindings();
				}
				DrawActionBindings();
			}
			ImGui::End();
		}
	}

	void MainMenuBar::SerializeScene(Ref<Scene> scene, const std::filesystem::path& Path)
	{
		SceneSerializer Serializer(scene);
		Serializer.Serialize(Path.string());
	}

	void MainMenuBar::NewScene()
	{
		EditorLayer::Get().m_ActiveScene = CreateRef<Scene>("NewScene");
		SaveAsScene();
		EditorLayer::Get().m_ActiveScene->OnViewportResize(EditorLayer::Get().m_FrameBuffer->GetSpecification().Width, EditorLayer::Get().m_FrameBuffer->GetSpecification().Height);
		EditorLayer::Get().m_SceneHierarchyPanel->SetContext(EditorLayer::Get().m_ActiveScene);
	}


	void MainMenuBar::OpenScene()
	{
		std::string FilePath = AGE::FileDialogs::OpenFile({"Open Scene"},AssetManager::Get().GetGameContentPath(),
			{"AGE Scene", "*.AGEScene"
			});
		if (!FilePath.empty())
		{
			OpenScene(FilePath);
		}
	}
	void MainMenuBar::OpenScene(const std::filesystem::path& FilePath)
	{
		if (EditorLayer::Get().m_Toolbar->GetSceneState() != SceneState::Edit)
		{
			EditorLayer::Get().m_Toolbar->OnSceneStop();
		}

		if (FilePath.extension().string() != ".AGEScene")
		{
			CoreLogger::Warn("Could not load {0} - not a scene file", FilePath.filename().string());
		}

		if (AssetManager::Get().IsSceneLoaded(FilePath.string()))
		{
			std::filesystem::path Path = FilePath;

			EditorLayer::Get().m_EditorScene = AssetManager::Get().GetScene(Utils::EngineStatics::GetFilename(Path));
			m_ActiveScene = AssetManager::Get().GetScene(Utils::EngineStatics::GetFilename(Path));
			EditorLayer::Get().m_EditorScene->OnViewportResize((uint32_t)EditorLayer::Get().m_ViewportSize.x, (uint32_t)EditorLayer::Get().m_ViewportSize.y);
			EditorLayer::Get().m_SceneHierarchyPanel->SetContext(EditorLayer::Get().m_EditorScene);
			EditorLayer::Get().m_ActiveScene = EditorLayer::Get().m_EditorScene;
			EditorLayer::Get().m_EditorScenePath = FilePath;
			m_SceneFilePath = FilePath.string();
			SceneChangedEvent Event(EditorLayer::Get().m_ActiveScene);
			EditorLayer::Get().m_ActiveScene->BroadcastEvent(Event);

			return;
		}
		//TODO: This needs to be deleted as soon there should be absolutely no reason this code is even applicable because all of the scenes
		// are loaded when the editor starts up.
		Ref<Scene> NewScene = CreateRef<Scene>();
		AGE::SceneSerializer Serializer(NewScene);
		if (Serializer.Deserialize(FilePath.string()))
		{
			EditorLayer::Get().m_EditorScene = NewScene;
			m_ActiveScene = NewScene;
			EditorLayer::Get().m_EditorScene->OnViewportResize((uint32_t)EditorLayer::Get().m_ViewportSize.x, (uint32_t)EditorLayer::Get().m_ViewportSize.y);
			EditorLayer::Get().m_SceneHierarchyPanel->SetContext(EditorLayer::Get().m_EditorScene);
			EditorLayer::Get().m_ActiveScene = EditorLayer::Get().m_EditorScene;
			EditorLayer::Get().m_EditorScenePath = FilePath;
			SceneChangedEvent Event(EditorLayer::Get().m_ActiveScene);
			EditorLayer::Get().m_ActiveScene->BroadcastEvent(Event);
		}
		m_SceneFilePath = FilePath.string();
	}
	void MainMenuBar::SaveScene()
	{

		if (!m_ProjectFilePath.empty())
		{
			std::string Path = m_ProjectFilePath.string();
			Path.append("/Scenes/");
			SerializeScene(EditorLayer::Get().m_ActiveScene, Path);
		}
		else
		{
			SaveAsScene();
		}
	}

	void MainMenuBar::SaveAsScene()
	{
		std::string FilePath = AGE::FileDialogs::SaveFile("Save Scene As",AssetManager::Get().GetGameContentPath(),
			{"AGE Scene (*.AGEScene)","*.AGEScene"});
		if (!FilePath.empty())
		{
			//TODO: TEMP
			SerializeScene(EditorLayer::Get().m_ActiveScene, FilePath);
			std::filesystem::path Path = FilePath;
			EditorLayer::Get().m_ActiveScene->SetSceneName(Utils::EngineStatics::GetFilename(Path));
			EditorLayer::Get().m_ActiveScene = AssetManager::Get().LoadScene(Path);
			EditorLayer::Get().m_EditorScenePath = FilePath;
		}
	}
	void MainMenuBar::NewProject(const std::string& ProjectName)
	{
		std::string FilePath = ProjectName;
		if (!FilePath.empty())
		{
			Project::New(ProjectName);
			NewScene();
			AppConfig Config = App::Get().GetAppConfig();
			m_ProjectFilePath = std::filesystem::path(Config.ProjectBasePath.string() + ProjectName + "/" + ProjectName + ".AGEProject");
			SaveScene();
			SaveProject();
		}
	}
	void MainMenuBar::OpenProject()
	{

		std::string FilePath = AGE::FileDialogs::OpenFile("", AssetManager::Get().GetGameContentPath(),
			{"AGE Project (*.AGEProject)", "*.AGEProject"});
		if (!FilePath.empty())
		{
			Project::Load(FilePath);
			m_ProjectFilePath = FilePath;
			auto StartScenePath = Project::GetActive()->GetConfig().StartScene;
			App::Get().GetDeviceManager().GetAudioManager().SwitchAudioEngine((AudioEngineType)Project::GetActive()->GetInfo().AudioEngine);
			RendererAPI::SetAPI((RendererAPI::API)Project::GetActive()->GetInfo().Renderer);

			OpenScene(StartScenePath);
			LoadInputIni();
		}

#ifdef AG_PLATFORM_WINDOWS
		std::wstring ProjName = m_ProjectFilePath.filename();
		SetEnvironmentVariable(L"AGEPROJECTNAME", ProjName.c_str());
#else
		std::string ProjName = m_ProjectFilePath.filename();
		setenv("AGEPROJECTNAME", ProjName.c_str(), 1);
#endif

		std::string ScenesDirectory = m_ProjectFilePath.string();
		ScenesDirectory.append("/Scenes");
		if (!std::filesystem::exists(ScenesDirectory))
		{
			std::filesystem::create_directories(ScenesDirectory);
		}
	}
	void MainMenuBar::SaveProject()
	{
		Project::SaveActive(m_ProjectFilePath, App::Get().GetDeviceManager().GetAudioManager().GetAudioEngineType(), RendererAPI::GetAPI(), EditorLayer::Get().m_EditorScenePath, m_QuestFilePath);
	}
	void MainMenuBar::SaveInputIni()
	{
		AppConfig& Config = App::Get().GetAppConfig();
		if (!Config.CurrentProjectPath.empty())
		{
			if (!std::filesystem::exists(Config.CurrentProjectPath/ "Config/Input.ini"))
			{
				std::ofstream newfile(std::filesystem::path(Config.CurrentProjectPath/ "Config/Input.ini"));
				if (newfile.is_open())
				{
					newfile.close();
					CoreLogger::Trace("File successfully created at {}", std::filesystem::path(Config.CurrentProjectPath/ "Config/Input.ini").string());
				}
				else
				{
					CoreLogger::Trace("Failed to create file at {}", std::filesystem::path(Config.CurrentProjectPath/ "Config/Input.ini").string());
				}
			}
			IniWriter Writer(Config.CurrentProjectPath / "Config/Input.ini");
			std::ranges::for_each(m_AxisBindings.begin(), m_AxisBindings.end(),[&](const Ref<InputBinding>& Binding )
			{
				Writer.Write(Binding->GetInputType(),Binding->GetName(),std::to_string(Binding->GetKey()));

			});

			std::ranges::for_each(m_ActionBindings.begin(), m_ActionBindings.end(),[&](const Ref<InputBinding>& Binding)
			{
				Writer.Write(Binding->GetInputType(),Binding->GetName(),std::to_string(Binding->GetKey()));
			});

			Writer.SaveFile();
		}


	}
	void MainMenuBar::LoadInputIni()
	{
		AppConfig& Config = App::Get().GetAppConfig();

		IniReader Reader(Config.CurrentProjectPath / "Config/Input.ini");

		//TODO: Extend Ini reader to handle a use case where we don't know what's in the file ahead of time and we need to just read the entire file and parse it
		bool HasMultiVal = false;
		Reader.Read("Gamepad", "Move Forward", HasMultiVal);
#if 0
		IniSerializer Serializer(m_AxisBindings, m_ActionBindings);
		Serializer.Deserialize(Project::GetActive()->GetInfo().ConfigFilepath.string(), "/Input.ini");
		m_AxisBindings.resize(Project::GetActive()->GetInfo().AxisBindings.size());
		m_ActionBindings.resize(Project::GetActive()->GetInfo().ActionBindings.size());
		std::copy(Project::GetActive()->GetInfo().AxisBindings.begin(), Project::GetActive()->GetInfo().AxisBindings.end(), m_AxisBindings.begin());
		std::copy(Project::GetActive()->GetInfo().ActionBindings.begin(), Project::GetActive()->GetInfo().ActionBindings.end(), m_ActionBindings.begin());
#endif

		AssetManager::Get().GetSceneNames(m_SceneNames);
	}
	void MainMenuBar::OpenNodeEditor()
	{
		EditorLayer::Get().m_NodeEditorManager->CreateContextAndWindow(std::filesystem::path(std::filesystem::current_path().string()+ "Sample.json"), "Node Editor");
	}
	std::filesystem::path MainMenuBar::LoadQuestFile()
	{
		std::filesystem::path Filepath(FileDialogs::OpenFile("Load Quest File", AssetManager::Get().GetGameContentPath(),
			{"JSON(*.json)","*.json"}));
		return Filepath;
	}
	void MainMenuBar::PackageGame()
	{
		Project::Package(Project::GetActive()->GetProjectDirectory().string() + "/PackagedBuilds/", App::Get().GetTargetPlatform());
	}

	void MainMenuBar::DrawAxisBindings()
	{
		if (ImGui::CollapsingHeader("AxisBindings"))
		{
			if (ImGui::BeginTable("Axis KeyBindings", 1))
			{
				for (size_t i = 0; i < m_AxisBindingData.size(); i++)
				{
					std::string InputTextName = "##KeyBinding" + std::to_string(i);
					std::string DeleteName = "Delete Axis Binding## " + std::to_string(i);
					ImGui::TableNextColumn();
					ImGui::InputText(InputTextName.c_str(), &m_AxisBindingData[i].ActionName); // The name of the Axis which should be binded to
					ImGui::SameLine();
					if (ImGui::Button(DeleteName.c_str()))
					{
						if (!m_AxisBindingData.empty())
						{
							m_AxisBindingData.resize(m_AxisBindingData.size() - 1);
							m_AxisBindingData.shrink_to_fit();
						}
					}
					std::string KeyName = "Keys##" + std::to_string(i);
					if (ImGui::CollapsingHeader(KeyName.c_str()))
					{
						DrawAxisCombo((int)i);
						ImGui::Separator();
					}
					Project::GetActive()->GetInfo().UpdateAxisBindings(m_AxisBindings);
				}
				ImGui::EndTable();
			}
		}
	}

	void MainMenuBar::DrawActionBindings()
	{
		if (ImGui::CollapsingHeader("Action Bindings"))
		{
			if (ImGui::BeginTable("Action KeyBindings", 1))
			{
				for (size_t i = 0; i < m_ActionBindingData.size(); i++)
				{
					ImGui::TableNextColumn();
					std::string InputTextName = "##ActionBinding" + std::to_string(i);
					std::string DeleteName = "Delete Action Binding## " + std::to_string(i);
					ImGui::InputText(InputTextName.c_str(), &m_ActionBindingData[i].ActionName); // The name of the Axis which should be binded to
					ImGui::SameLine();
					if (ImGui::Button(DeleteName.c_str()))
					{
						if (!m_ActionBindingData.empty())
						{
							m_ActionBindings.resize(m_ActionBindings.size() - 1);
							m_ActionBindings.shrink_to_fit();
						}
					}
					std::string KeyName = "Keys##" + std::to_string(i);
					if (ImGui::CollapsingHeader(KeyName.c_str()))
					{
						DrawActionCombo((int)i);
						ImGui::Separator();
					}
					Project::GetActive()->GetInfo().UpdateActionBindings(m_ActionBindings);
				}
				ImGui::EndTable();
			}
		}
	}

	void MainMenuBar::DrawAxisCombo(int i)
	{
		m_CurrentAxisBindingString = m_AxisBindingStrings[m_AxisBindingData[i].Index];
		std::string ComboName = "Binding## " + std::to_string(i);

		if (ImGui::BeginCombo(ComboName.c_str(), m_CurrentAxisBindingString.c_str()))
		{
			for (int y = 0; y < 8; y++)
			{
				bool IsSelected = m_CurrentAxisBindingString == m_AxisBindingStrings[y];

				if (ImGui::Selectable(m_AxisBindingStrings[y].c_str(), IsSelected))
				{
					m_CurrentAxisBindingString = m_AxisBindingStrings[y];
					m_AxisBindingData[i].Axis = Utils::ConvertToAxisKeyBinding(m_CurrentAxisBindingString);
					m_AxisBindingData[i].Index = y;
				}

				if (IsSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}


			ImGui::EndCombo();
		}
	}

	void MainMenuBar::DrawActionCombo(int i)
	{
		m_CurrentActionBindingString = m_ActionBindingStrings[m_ActionBindingData[i].Index];
		std::string ComboName = "Binding## " + std::to_string(i) ;

		if (ImGui::BeginCombo(ComboName.c_str(), m_CurrentActionBindingString.c_str()))
		{
			for (int y = 0; y < 11; y++)
			{
				bool IsSelected = m_CurrentActionBindingString == m_ActionBindingStrings[y];

				if (ImGui::Selectable(m_ActionBindingStrings[y].c_str(), IsSelected))
				{
					m_CurrentActionBindingString = m_ActionBindingStrings[y];
					m_ActionBindingData[i].Name = Utils::ConvertToActionKeyBinding(m_CurrentActionBindingString);
					m_ActionBindingData[i].Index = y;
				}

				if (IsSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
	}

	void MainMenuBar::OpenQuestManager()
	{
		EditorLayer::Get().m_QuestManagerWindow->OpenWindow();
	}

	void MainMenuBar::OpenInventoryDatabase()
	{
		EditorLayer::Get().m_InventoryDatabase->RestoreWindow();
	}

	void MainMenuBar::OpenDatabase()
	{
		EditorLayer::Get().m_DatabaseWindow->RestoreWindow();
	}

	void MainMenuBar::SyncBindings()
	{
		if (m_ActionBindingData.size() > m_ActionBindings.size())
		{
			size_t diff = m_ActionBindingData.size() - m_ActionBindings.size();
			std::ranges::for_each(m_ActionBindingData.begin() + diff -1, m_ActionBindingData.end(), [&](const ActionBindingData& Data)
			{
				m_ActionBindings.emplace_back(InputBinding::CreateGamepadBinding(Data.ActionName, (GamePad::Buttons)Data.Button,Data.Type));
				m_ActionBindings.back()->SetInputType("Gamepad");
			});
		}

		if (m_AxisBindingData.size() > m_AxisBindings.size())
		{
			size_t diff = m_AxisBindingData.size() - m_AxisBindings.size();
			std::ranges::for_each(m_AxisBindingData.begin() + diff -1, m_AxisBindingData.end(), [&](const AxisBindingData& Data)
			{
				m_AxisBindings.emplace_back(InputBinding::CreateGamepadBinding(Data.ActionName, (GamePad::Axes)Data.Axis,Data.Type));
				m_AxisBindings.back()->SetInputType("Gamepad");
			});
		}

		SaveInputIni();
	}
}
#endif //AG_DIST
