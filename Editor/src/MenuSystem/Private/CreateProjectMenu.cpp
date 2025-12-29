#include "MenuSystem/Public/CreateProjectMenu.h"
#include "Editor_Core/Public/EditorLayer.h"
#include <Age.h>
#include <imgui.h>

#include "Serializers/Public/IniReader.h"

namespace AGE
{
	void ProjectMenu::OnImGuiRender()
	{
		if (ImGui::Begin("Project Menu"))
		{
			if (ImGui::Button("Create Project"))
			{
				bCreateProject = true;
				ImGui::CloseCurrentPopup();
				bMakeChoice = false;
			}

			if (ImGui::Button("LoadProject"))
			{
				bCreateProject = false;
				ImGui::CloseCurrentPopup();
				bMakeChoice = false;
			}

			if (ImGui::Button("Exit"))
			{
				App::Get().Close();
			}

			if (bMakeChoice)
			{
				ImGui::OpenPopup("Make Project");
			}

			ImGui::End();
		}

		switch (bCreateProject)
		{
		case -1:
			break;

		case 0:
		{
			ImGui::OpenPopup("Load Project");
			LoadProject();
			break;
		}
		case 1:
		{
			ImGui::OpenPopup("Create New Project");
			CreateProject();
			break;
		}
		}


	}

	void ProjectMenu::NewProject(const std::string& ProjectName)
	{
		AppConfig& Config = App::Get().GetAppConfig();
		std::string FilePath = ProjectName;
		if (!FilePath.empty())
		{
			m_ProjectFilePath = std::filesystem::path(Config.ProjectBasePath.string() +"/"+ ProjectName + "/" + ProjectName + ".AGEProject");
			Config.CurrentProjectPath = m_ProjectFilePath.parent_path();
			Config.GameContentPath = m_ProjectFilePath.parent_path().string() + "/GameContent/Assets/";
			std::string ScenesPath = m_ProjectFilePath.parent_path().string() + "/Scenes";
			Project::New(ProjectName);
			NewScene();
			EditorLayer::Get().m_EditorScenePath = ScenesPath;
			SaveScene("Untitled Scene");
			SaveProject();
#ifdef AG_PLATFORM_WINDOWS
	#if AG_RELEASE
			std::filesystem::copy(g_EditorAssetPath.string() + "/../Game", m_ProjectFilePath.parent_path().string() + "/" + Project::GetActive()->GetConfig().Name, std::filesystem::copy_options::recursive);
			CoreLogger::Warn("In order to generate a Visual Studio, go to your projects directory and run Setup.bat");
	#endif
	#if AG_DEBUG
			CoreLogger::Warn("In order to generate a Visual Studio, go to your projects directory and run Setup.bat");
	#endif
#endif
		}
	}

	void ProjectMenu::SaveProject()
	{
		if (Project::SaveActive(m_ProjectFilePath, App::Get().GetDeviceManager().GetAudioManager().GetAudioEngineType(), RendererAPI::GetAPI(), Project::GetActive()->GetConfig().StartScene, Project::GetActive()->GetAssetDirectory().string() + "Quests", m_ProjectFilePath.parent_path().string() + "/Config"))
		{
			EditorLayer::Get().bShowProjectMenu = false;
			ProjectCreatedEvent Event{};
			App::Get().OnEvent(Event);
		}

	}

	void ProjectMenu::CreateProject()
	{
		if (ImGui::BeginPopup("Create New Project"))
		{
			static char Input[128];
			ImGui::Text("ProjectName");
			ImGui::InputText("##ProjectName", Input, IM_ARRAYSIZE(Input));
			if (ImGui::Button("Create Project"))
			{
				std::string ProjectName(Input);
				NewProject(ProjectName.data());
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::Button("Back"))
			{
				bMakeChoice = true;
				bCreateProject = -1;
			}
			ImGui::EndPopup();
		}
	}

	void ProjectMenu::LoadProject()
	{
		AppConfig Config = App::Get().GetAppConfig();
		if (ImGui::BeginPopup("Load Project"))
		{
			std::vector<std::string> ProjectStrings;
			std::string CurrentProjectString = "";
			for (auto& F : std::filesystem::directory_iterator(Config.ProjectBasePath))
			{
				ProjectStrings.push_back(F.path().filename().string());
			}




			if (ImGui::BeginCombo("Projects", CurrentProjectString.data()))
			{
				for (int i = 0; i < ProjectStrings.size(); i++)
				{
					bool IsSelected = CurrentProjectString == ProjectStrings[i];

					if (ImGui::Selectable(ProjectStrings[i].c_str(), IsSelected))
					{
						CurrentProjectString = ProjectStrings[i];
						OpenProject(CurrentProjectString);
						ImGui::CloseCurrentPopup();
					}

					if (IsSelected)
					{
						ImGui::SetItemDefaultFocus();
					}


				}

				ImGui::EndCombo();
			}
			if (ImGui::Button("Back"))
			{
				bMakeChoice = true;
				bCreateProject = -1;
			}
				ImGui::EndPopup();
		}
	}

	void ProjectMenu::NewScene()
	{
		EditorLayer::Get().m_ActiveScene = CreateRef<Scene>();
		//EditorLayer::Get().m_ActiveScene->OnViewportResize(EditorLayer::Get().m_FrameBuffer->GetSpecification().Width, EditorLayer::Get().m_FrameBuffer->GetSpecification().Height);
		//EditorLayer::Get().m_SceneHierarchyPanel->SetContext(EditorLayer::Get().m_ActiveScene);
	}

	void ProjectMenu::OpenProject(const std::string& ProjectName)
	{
		if (!ProjectName.empty())
		{
			AppConfig Config = App::Get().GetAppConfig();
			std::string filename = "/" + ProjectName + "/" + ProjectName + ".AGEProject";
			Project::Load(Config.ProjectBasePath.string() + filename);
			m_ProjectFilePath = filename;
			auto StartScenePath = Project::GetActive()->GetConfig().StartScene;
			App::Get().GetDeviceManager().GetAudioManager().SwitchAudioEngine((AudioEngineType)Project::GetActive()->GetInfo().AudioEngine);
			RendererAPI::SetAPI((RendererAPI::API)Project::GetActive()->GetInfo().Renderer);
			App::Get().SetProject(Project::GetActive());
			CoreLogger::Info("Project Successfully Opened!");
			ProjectLoadedEvent Event{};
			App::Get().OnEvent(Event);
			std::string Name = ProjectName;
			Name.append("_Quests.json");
			GameFramework::GameState::Get()->GetQuestManager()->LoadQuests(Project::GetActive()->GetAssetDirectory().string() + "/Quests/" + Name);
			EditorLayer::Get().m_QuestManagerWindow->Sync();

			EditorLayer::Get().m_InventoryDatabase->LoadDatabase();

			OpenScene(StartScenePath);
		}
	}

	void ProjectMenu::OpenScene(const std::filesystem::path& FilePath)
	{
		if (EditorLayer::Get().m_Toolbar->GetSceneState() != SceneState::Edit)
		{
			EditorLayer::Get().m_Toolbar->OnSceneStop();
		}

		if (FilePath.extension().string() != ".AGEScene")
		{
			CoreLogger::Warn("Could not load {0} - not a scene file", FilePath.filename().string());
		}
		AppConfig Config = App::Get().GetAppConfig();
		Config.GameContentPath = Project::GetActive()->GetAssetDirectory();

		EditorLayer::Get().bShowProjectMenu = false;
		Ref<Scene> NewScene = CreateRef<Scene>();
		AGE::SceneSerializer Serializer(NewScene);
		if (Serializer.Deserialize(FilePath.string()))
		{
			EditorLayer::Get().m_EditorScene = NewScene;
			EditorLayer::Get().m_EditorScene->OnViewportResize((uint32_t)EditorLayer::Get().m_ViewportSize.x, (uint32_t)EditorLayer::Get().m_ViewportSize.y);
			EditorLayer::Get().m_SceneHierarchyPanel->SetContext(EditorLayer::Get().m_EditorScene);
			EditorLayer::Get().m_ActiveScene = EditorLayer::Get().m_EditorScene;
			EditorLayer::Get().m_EditorScenePath = FilePath;

		}
	}
	void ProjectMenu::SaveScene(const std::string& SceneName)
	{
		if (!m_ProjectFilePath.empty())
		{
			std::string Path = m_ProjectFilePath.parent_path().string();
			Path.append("/Scenes/");
			Path.append(SceneName);
			Path.append(".AGEScene");
			Project::GetActive()->GetConfig().StartScene = Path;
			SceneSerializer Serializer(EditorLayer::Get().m_ActiveScene);
			Serializer.Serialize(Path);
		}
	}
}

