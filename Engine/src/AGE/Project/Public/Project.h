#pragma once

#include "Core/Public/Pointers.h"

namespace AGE
{
	struct ProjectConfig
	{
		std::string Name = "Untitled";
		std::filesystem::path StartScene;
		std::filesystem::path AssetDirectory;
		std::string CppNameSpace = "";
		std::string CopyrightNotice = "ADD YOUR COPYRIGHT NOTICE IN THE EDITOR WINDOW VIA PROJECT SETTINGS";

	};

	struct ProjectInfo
	{
		uint16_t AudioEngine = 0;
		int Renderer = 1;
		std::filesystem::path QuestFilepath;
		std::filesystem::path ConfigFilepath;
		std::vector<std::filesystem::path> BuiltScenes;
		//Probably set input Bindings here too

		std::vector<std::pair<std::string, std::vector<uint8_t>>> AxisBindings;
		std::vector<std::pair<std::string, std::vector<uint8_t>>> ActionBindings;

		void UpdateAxisBindings(std::vector<std::pair<std::string, std::vector<uint8_t>>>& Bindings)
		{
			AxisBindings = Bindings;
		}

		void UpdateActionBindings(std::vector<std::pair<std::string, std::vector<uint8_t>>>& Bindings)
		{
			ActionBindings = Bindings;
		}

		void SetQuestFilepath(const std::filesystem::path& Filepath)
		{
			QuestFilepath = Filepath;
		}
	};

	class Project
	{
	public:
		static const std::filesystem::path& GetProjectDirectory()
		{
			CoreLogger::Assert((s_ActiveProject != nullptr), "No Active Project!");

			return s_ActiveProject->m_ProjectDirectory;
		}

		static std::filesystem::path GetAssetDirectory()
		{
			CoreLogger::Assert((s_ActiveProject != nullptr), "No Active Project!");

			return GetProjectDirectory() / s_ActiveProject->m_Config.AssetDirectory;
		}

		static std::filesystem::path GetQuestDirectory()
		{
			CoreLogger::Assert((s_ActiveProject != nullptr), "No Active Project!");

			return GetProjectDirectory() / s_ActiveProject->m_Info.QuestFilepath;
		}

		static std::filesystem::path GetConfigDirectory()
		{
			CoreLogger::Assert((s_ActiveProject != nullptr), "No Active Project!");

			return GetProjectDirectory() / s_ActiveProject->m_Info.ConfigFilepath;
		}

		static std::filesystem::path GetAssetFileSystemPath(const std::filesystem::path& Path)
		{
			CoreLogger::Assert((s_ActiveProject != nullptr), "No Active Project!");
			return GetAssetDirectory() / Path;
		}

		ProjectConfig& GetConfig() { return m_Config; }
		ProjectInfo& GetInfo() { return m_Info; }

		static void WriteProjectConfig(const std::filesystem::path& Path, const std::string& ProjectName);
		static void WriteEditorConfig(const std::filesystem::path& Path, const std::string& ProjectName);
		static void ReadProjectConfig(const std::filesystem::path& Path);
		static void ReadEditorConfig(const std::filesystem::path& Path);


		void AddBuiltScenes();

		static Ref<Project> GetActive() { return s_ActiveProject; }

		static Ref<Project> New(const std::string& ProjectName);

		static Ref<Project>Load(const std::filesystem::path& Path);
		static bool SaveActive(const std::filesystem::path& Path, uint16_t AudioEngine, int Renderer, const std::filesystem::path& ScenePath, const std::filesystem::path& QuestPath = std::filesystem::path(), const std::filesystem::path& ConfigPath = std::filesystem::path());

		static bool Package(const std::filesystem::path& Path, int TargetPlatform);

		static void CompileProject();

	private:

		ProjectConfig m_Config;
		ProjectInfo m_Info;
		std::filesystem::path m_ProjectDirectory;
		static std::array<std::string, 14> m_DirectoryNames;
		static std::array<std::string, 5> m_GameContDirNames;
		inline static Ref<Project> s_ActiveProject;

	};
}