#include "AGEpch.hpp"
#include "Core/Public/App.h"
#include "Project/Public/Project.h"
#include "Serializers/Public/IniReader.h"
#include "Serializers/Public/IniWriter.h"
#include "Utils/Public/Serializers.h"

namespace AGE
{
	std::array<std::string, 9> Project::m_DirectoryNames = { "/Assets", "/Assets/Quests", "/Assets/InventoryDatabase", "/Assets/VisualScripting", "/Scenes", "/Shaders", "/Saves", "/src","/Config"};
	std::array<std::string, 5> Project::m_GameContDirNames = { "/Textures", "Sounds/Banks", "/Aesprite", "/Shaders", "/UI"};

	void Project::WriteProjectConfig(const std::filesystem::path& Path, const std::string& ProjectName)
	{
		IniWriter Writer(Path.string() + "/ProjectConfig.ini");
		Writer.Write("Paths", "GameContentPath", std::vformat("/{}/GameContent/Assets/", std::make_format_args(ProjectName)));
		Writer.SaveFile();

	}

	void Project::WriteEditorConfig(const std::filesystem::path& Path, const std::string& ProjectName)
	{
		std::string CWD = std::filesystem::current_path().string();

		IniWriter Writer(Path.string() + "/EditorConfig.ini");
		Writer.Write("Paths", "LogPath", std::vformat("/{}/Logs/", std::make_format_args(ProjectName)));
		Writer.Write("Paths", "EditorAssetsPath", std::vformat("/{}/Assets/", std::make_format_args(CWD)));
		Writer.SaveFile();
	}

	void Project::ReadProjectConfig(const std::filesystem::path &Path)
	{
		AppConfig& Config = App::Get().GetAppConfig();
		IniReader Reader(Path.string() + "/ProjectConfig.ini");
		bool HasMulti;
		std::string Result = Reader.Read("Paths", "GameContentPath", HasMulti);
		if (HasMulti)
		{
			std::vector<std::string> Values = Reader.ReadAll("Paths", "GameContentPath");
		}
		else
		{
			Config.GameContentPath = std::filesystem::path(Result);
		}

	}

	void Project::ReadEditorConfig(const std::filesystem::path &Path)
	{
		AppConfig& Config = App::Get().GetAppConfig();
		IniReader Reader(Path.string() + "/EditorConfig.ini");
		bool HasMulti;
		std::string Result = Reader.Read("Paths", "LogPath", HasMulti);
		if (HasMulti)
		{
			std::vector <std::string> LogPaths = Reader.ReadAll("Paths", "LogPath");
		}
		else
		{
			Config.LogPath = std::filesystem::path(Result);
		}
		Result.clear();

		Result = Reader.Read("Paths", "EditorAssetsPath", HasMulti);
		if (HasMulti)
		{
			std::vector<std::string> AssetsPaths = Reader.ReadAll("Paths", "EditorAssetsPath");
		}
		else
		{
			Config.EditorAssetPath = std::filesystem::path(Result);
		}


	}

	void Project::AddBuiltScenes()
	{
		AppConfig Config = App::Get().GetAppConfig();
		if (std::filesystem::is_directory(Config.CurrentProjectPath.string() + "/"+s_ActiveProject->GetConfig().Name + "/BuiltScenes/"))
		{
			for (const auto& Scene : std::filesystem::directory_iterator(Config.CurrentProjectPath.string() + "/" + s_ActiveProject->GetConfig().Name+"/BuiltScenes/"))
			{
				auto it = std::find(m_Info.BuiltScenes.begin(), m_Info.BuiltScenes.end(), Scene.path());

				if (it == m_Info.BuiltScenes.end())
				{
					m_Info.BuiltScenes.push_back(Scene.path());
				}
			}
		}
		else
		{
			CoreLogger::Error("No Scenes have been built!");
			CoreLogger::Info("Checking for Scenes in Scenes folder...");

			if (std::filesystem::is_empty(Config.CurrentProjectPath.string() + "/Scenes/"))
			{
				CoreLogger::Warn("No Scenes present in Scenes folder!");
				return;
			}

			CoreLogger::Info("Building Scenes...");
			Scene::BuildAllScenes();
			for (const auto& Scene : std::filesystem::directory_iterator(Config.CurrentProjectPath.string() + "/BuiltScenes/"))
			{
				auto it = std::find(m_Info.BuiltScenes.begin(), m_Info.BuiltScenes.end(), Scene.path());

				if (it == m_Info.BuiltScenes.end())
				{
					m_Info.BuiltScenes.push_back(Scene.path());
				}
			}


		}


	}

	Ref<Project> AGE::Project::New(const std::string& ProjectName)
	{
		AppConfig Config = App::Get().GetAppConfig();
		if (ProjectName == "Untitled")
		{
			s_ActiveProject = CreateRef<Project>();
			return s_ActiveProject;
		}

		s_ActiveProject = CreateRef<Project>();

		for (auto& N : m_DirectoryNames)
		{
			std::filesystem::path DirPath = Config.CurrentProjectPath.string() + N;
			std::filesystem::create_directories(DirPath);
			if (N.find("Config") != std::string::npos)
			{
				WriteProjectConfig(DirPath, ProjectName);
				WriteEditorConfig(DirPath, ProjectName);
			}
		}
		if (!std::filesystem::is_directory(Config.GameContentPath))
		{
			std::filesystem::create_directories(Config.GameContentPath);
			s_ActiveProject->GetConfig().AssetDirectory = Config.GameContentPath;

			for (auto& N : m_GameContDirNames)
			{
				std::filesystem::create_directories(Config.GameContentPath.string() + N);
			}
		}
		return s_ActiveProject;
	}
	Ref<Project> Project::Load(const std::filesystem::path& Path)
	{
		AppConfig& Config = App::Get().GetAppConfig();
		if (Path.string().find("GAMENAMEHERE",0) != std::string::npos)
		{
			return nullptr;
		}
		Ref<Project> Proj = CreateRef<Project>();
		Config.CurrentProjectPath = Path.parent_path();
		ReadProjectConfig(Config.CurrentProjectPath.string() + "/Config");
		ProjectSerializer Serializer(Proj);
		if (Serializer.Deserialize(Path))
		{
			Proj->m_ProjectDirectory = Path.parent_path();
			s_ActiveProject = Proj;
			Config.GameContentPath = GetAssetDirectory();
			CoreLogger::Info("Loaded Project {0}", Path.string());
			return s_ActiveProject;
		}
		CoreLogger::Info("Could not Load Project!\n\tProject File Path {0}", Path.string());
		return nullptr;
	}
	bool Project::SaveActive(const std::filesystem::path& Path, uint16_t AudioEngine, int Renderer, const std::filesystem::path& ScenePath, const std::filesystem::path& QuestPath, const std::filesystem::path& ConfigPath)
	{
		ProjectSerializer Serializer(s_ActiveProject);
		s_ActiveProject->m_ProjectDirectory = Path;
		s_ActiveProject->GetConfig().Name = Path.filename().replace_extension().string();
		s_ActiveProject->GetConfig().StartScene = ScenePath;
		s_ActiveProject->GetInfo().AudioEngine = AudioEngine;
		s_ActiveProject->GetInfo().Renderer = Renderer;
		if (s_ActiveProject->GetInfo().QuestFilepath.empty())
		{
			s_ActiveProject->GetInfo().QuestFilepath = QuestPath;
		}
		if (s_ActiveProject->GetInfo().ConfigFilepath.empty())
		{
			s_ActiveProject->GetInfo().ConfigFilepath = ConfigPath;
		}

		s_ActiveProject->AddBuiltScenes();

		if (Serializer.Serialize(Path))
		{
			return true;
		}
		return false;
	}
	bool Project::Package(const std::filesystem::path& Path, int TargetPlatform)
	{
		switch (TargetPlatform)
		{
			case 0: // Windows
			{
				if (std::filesystem::is_directory(Path.parent_path()))
				{
					std::string NewPath = Path.parent_path().string() + "/Windows/" + s_ActiveProject->GetConfig().Name + ".apak";
					ProjectSerializer Serializer(s_ActiveProject);

					Serializer.SerializeBinary(NewPath);
					CompileProject();
				}
				else
				{
					std::string NewPath = Path.parent_path().string() + "/Windows/";
					std::filesystem::create_directories(NewPath);
					ProjectSerializer Serializer(s_ActiveProject);
					NewPath = NewPath + s_ActiveProject->GetConfig().Name + ".apak";
					Serializer.SerializeBinary(NewPath);
					CompileProject();
				}
				break;
			}
			default:
			{
				CoreLogger::Error("Target Platform Not Supported!");
			}
		}
		return false;
	}
	void Project::CompileProject()
	{
		AppConfig Config = App::Get().GetAppConfig();
#ifdef AG_PLATFORM_WINDOWS

		CoreLogger::Info("Building Executeable!\n\tPlease Do Not Close Window!");

		auto f = [Config](const std::filesystem::path& ProjectPath, const std::filesystem::path& PathToPackagedGame, const std::string ProjectName) {
#ifdef AG_DEBUG
			std::wstring path = Config.EditorAssetPath.wstring() + L"/../../BuildScripts/PackageGameScripts/OpenVSCMD.bat";
#elif AG_RELEASE
			std::wstring path = g_EditorAssetPath.wstring() + L"/../PackageGameScripts/OpenVSCMD.bat";

#endif

			std::wstring cmd = std::wstring(L" /p:Configuration=Dist ") + std::wstring(L"/p:Platform=x64 ") +ProjectPath.wstring();
			std::wstring full = path + cmd;

		STARTUPINFOW Info;
		PROCESS_INFORMATION PInfo;

		memset(&Info, 0, sizeof(STARTUPINFO));
		Info.cb = sizeof(Info);
		memset(&PInfo, 0, sizeof(PROCESS_INFORMATION));


		CreateProcessW(NULL,
			full.data(),
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&Info,
			&PInfo);

		WaitForSingleObject(PInfo.hProcess, INFINITE);
		CloseHandle(PInfo.hProcess);
		CloseHandle(PInfo.hThread);

		if (std::filesystem::exists(ProjectPath.string() + "/bin/Dist-windows-x86_64/Game/Game.exe"))
		{
			std::filesystem::copy(ProjectPath.string() + "/bin/Dist-windows-x86_64/Game/Game.exe", PathToPackagedGame);
			CoreLogger::Info("Game Sucessfully Packaged!");
			return;
		}
		CoreLogger::Error("Failed to execute compilation Command!");
		
		};

		std::filesystem::path PPath = Project::GetActive()->GetProjectDirectory();
		std::filesystem::path PackagedGamePath = Project::GetActive()->GetProjectDirectory().string() + "/PackagedBuilds";

		std::thread th(f,PPath,PackagedGamePath,Project::GetActive()->GetConfig().Name);

		th.detach();




#endif
	}
}