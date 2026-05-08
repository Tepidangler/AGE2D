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

		/**
 * @brief Updates the Axis bindings with new data.
 *
 * This function takes a vector of pairs, where each pair consists of an axis name and a vector of uint8_t values representing the binding for that axis. 
 * The function updates the internal AxisBindings member variable with this new data.
 *
 * @param Bindings A reference to a vector of pairs containing strings (axis names) and vectors of uint8_t (binding data).
 */
void UpdateAxisBindings(std::vector<std::pair<std::string, std::vector<uint8_t>>>& Bindings)
		{
			AxisBindings = Bindings;
		}

		/**
 * @brief Updates the action bindings with a new set of bindings.
 * 
 * This function takes in a vector of pairs, where each pair contains an action name and its corresponding key binding. It then updates the ActionBindings member variable with this new data.
 * 
 * @param Bindings A vector of pairs containing the action names and their respective bindings.
 * @return void No return value.
 */
void UpdateActionBindings(std::vector<std::pair<std::string, std::vector<uint8_t>>>& Bindings)
		{
			ActionBindings = Bindings;
		}

		/**
 * @brief Sets the quest file path.
 *
 * This function sets the QuestFilepath member variable to a new value, which is provided as an argument.
 * The new file path should be a valid filesystem path.
 * 
 * @param Filepath A const reference to a std::filesystem::path object representing the new quest file path.
 */
void SetQuestFilepath(const std::filesystem::path& Filepath)
		{
			QuestFilepath = Filepath;
		}
	};

	class Project
	{
	public:
		/**
 * @brief Returns the project directory path.
 *
 * This function returns a constant reference to the project directory path of the currently active project. 
 * It is crucial that there exists an active project before calling this function, otherwise it will throw an assertion error with the message "No Active Project!".
 *
 * @return A constant reference to the project directory path of the active project.
 */
static const std::filesystem::path& GetProjectDirectory()
		{
			CoreLogger::Assert((s_ActiveProject != nullptr), "No Active Project!");

			return s_ActiveProject->m_ProjectDirectory;
		}

		/**
 * @brief Returns the path to the asset directory of the active project.
 * 
 * This function retrieves the path to the asset directory of the currently active project. It first checks if there is an active project, and throws an error if none exists. Then it returns the path by appending the asset directory name to the project's directory.
 *
 * @return std::filesystem::path The path to the asset directory.
 */
static std::filesystem::path GetAssetDirectory()
		{
			CoreLogger::Assert((s_ActiveProject != nullptr), "No Active Project!");

			return GetProjectDirectory() / s_ActiveProject->m_Config.AssetDirectory;
		}

		/**
 * @brief Returns the directory path of the quest file for the currently active project.
 * 
 * This function retrieves the directory path of the quest file associated with the current active project. It ensures that there is an active project before proceeding, and throws an exception if not. The returned path is a concatenation of the project's directory and the quest filepath stored in the project info.
 * 
 * @return std::filesystem::path The directory path of the quest file for the currently active project.
 */
static std::filesystem::path GetQuestDirectory()
		{
			CoreLogger::Assert((s_ActiveProject != nullptr), "No Active Project!");

			return GetProjectDirectory() / s_ActiveProject->m_Info.QuestFilepath;
		}

		/**
 * @brief Returns the configuration directory path of the active project.
 *
 * This function retrieves the configuration directory path for the currently active project. It ensures that there is an active project by asserting that `s_ActiveProject` is not null, and throws an exception with a message "No Active Project!" if it is. 
 * The function then returns the result of concatenating the project's directory with its configuration file path.
 *
 * @return std::filesystem::path - The configuration directory path for the active project.
 */
static std::filesystem::path GetConfigDirectory()
		{
			CoreLogger::Assert((s_ActiveProject != nullptr), "No Active Project!");

			return GetProjectDirectory() / s_ActiveProject->m_Info.ConfigFilepath;
		}

		/**
 * @brief Returns the filesystem path for an asset.
 * 
 * This function takes a relative path to an asset and returns its full filesystem path, based on the active project's directory.
 * The function asserts that there is an active project before proceeding. If no active project exists, it throws an exception with the message "No Active Project!".
 * 
 * @param Path A const reference to a std::filesystem::path object representing the relative path of the asset.
 * @return A std::filesystem::path object representing the full filesystem path for the given asset.
 */
static std::filesystem::path GetAssetFileSystemPath(const std::filesystem::path& Path)
		{
			CoreLogger::Assert((s_ActiveProject != nullptr), "No Active Project!");
			return GetAssetDirectory() / Path;
		}

		/**
 * @brief Returns the project configuration object.
 *
 * This function returns a reference to the ProjectConfig object that contains all of the configuration settings for the project.
 * The returned object can be used to modify the configuration as needed.
 *
 * @return A reference to the ProjectConfig object.
 */
ProjectConfig& GetConfig() { return m_Config; }
		/**
 * @brief This function returns a reference to the ProjectInfo object.
 * @return A reference to the ProjectInfo object (m_Info).
 */
ProjectInfo& GetInfo() { return m_Info; }

		static void WriteProjectConfig(const std::filesystem::path& Path, const std::string& ProjectName);
		static void WriteEditorConfig(const std::filesystem::path& Path, const std::string& ProjectName);
		static void ReadProjectConfig(const std::filesystem::path& Path);
		static void ReadEditorConfig(const std::filesystem::path& Path);


		void AddBuiltScenes();

		/**
 * @brief Retrieves the currently active project.
 *
 * This function returns a reference to the currently active project. The active project is typically set when loading or creating a new project, and remains active until it's explicitly deactivated.
 *
 * @return A reference to the currently active project. If no project is currently active, this will be an invalid reference.
 */
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