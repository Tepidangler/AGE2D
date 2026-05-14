#pragma once

#include "Core/Public/InputBinding.h"
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
		std::vector<Ref<InputBinding>> AxisBindings;
		std::vector<Ref<InputBinding>> ActionBindings;

		/**
 * @brief Sets the quest file path.
 *
 * This function sets the QuestFilepath member variable to a new value, which represents the path of the quest file.
 * The parameter 'Filepath' is used as input for setting this member variable.
 * 
 * @param Filepath A const reference to std::filesystem::path representing the new quest file path.
 */
void SetQuestFilepath(const std::filesystem::path& Filepath)
		{
			QuestFilepath = Filepath;
		}

		/**
 * @brief Updates the action bindings with new input bindings.
 * 
 * This function takes a vector of references to InputBinding objects and appends them to the existing ActionBindings list.
 * The purpose is to update or extend the current set of actions that can be performed by the user.
 * 
 * @param Bindings A constant reference to a vector of InputBinding objects, which represent new bindings to add.
 * Each element in this vector represents an action and its associated input binding.
 * 
 * @return void No return value is expected as all changes are made directly on the ActionBindings list.
 */
void UpdateActionBindings(const std::vector<Ref<InputBinding>>& Bindings)
		{
			std::ranges::copy(Bindings, std::back_inserter(ActionBindings));
		}
		/**
 * @brief Updates the Axis bindings with new input bindings.
 * 
 * This function takes a vector of InputBinding references and adds them to the existing Axis Bindings.
 * The new bindings are appended at the end of the current list.
 * 
 * @param[in] Bindings - A const reference to a std::vector of InputBinding references. Each element in this vector represents an input binding that will be added to the existing set of axis bindings.
 * 
 * @return void
 */
void UpdateAxisBindings(const std::vector<Ref<InputBinding>>& Bindings)
		{
			std::ranges::copy(Bindings, std::back_inserter(AxisBindings));
		}
	};

	class Project
	{
	public:
		/**
 * @brief Returns the project directory.
 *
 * This function returns a reference to the filesystem path of the active project's directory. 
 * It is crucial for any operations related to files and directories within the project.
 *
 * @return A constant reference to the filesystem path of the active project's directory.
 */
static const std::filesystem::path& GetProjectDirectory()
		{
			CoreLogger::Assert((s_ActiveProject != nullptr), "No Active Project!");

			return s_ActiveProject->m_ProjectDirectory;
		}

		/**
 * @brief Returns the path to the asset directory of the active project.
 * 
 * This function retrieves the path to the asset directory of the currently active project. It first asserts that there is an active project, and if not, it throws an error message "No Active Project!". Then it returns the path by appending the asset directory name from the active project's configuration to the project directory.
 * 
 * @return std::filesystem::path The path to the asset directory of the active project.
 */
static std::filesystem::path GetAssetDirectory()
		{
			CoreLogger::Assert((s_ActiveProject != nullptr), "No Active Project!");

			return GetProjectDirectory() / s_ActiveProject->m_Config.AssetDirectory;
		}

		/**
 * @brief This function returns the directory path of the quest file for the active project.
 * 
 * The function first checks if there is an active project by verifying that s_ActiveProject is not nullptr. If no active project exists, it throws an assertion error with a message "No Active Project!".
 * It then retrieves the directory path of the quest file from the active project's information and returns this path. The function uses the '/' operator to concatenate the project directory path and the quest filepath.
 * 
 * @return std::filesystem::path The directory path of the quest file for the active project.
 */
static std::filesystem::path GetQuestDirectory()
		{
			CoreLogger::Assert((s_ActiveProject != nullptr), "No Active Project!");

			return GetProjectDirectory() / s_ActiveProject->m_Info.QuestFilepath;
		}

		/**
 * @brief Returns the path to the configuration directory of the active project.
 * 
 * This function retrieves the path to the configuration directory of the currently active project. It first checks if there is an active project by verifying that `s_ActiveProject` is not null, and throws an exception with a message "No Active Project!" if it's null. Then, it returns the path to the configuration file of the active project relative to the project directory using the '/' operator from the C++17 filesystem library.
 * 
 * @return std::filesystem::path The path to the configuration directory.
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
 * The provided path is appended to the asset directory of the active project.
 * 
 * @param Path A const reference to the relative path to the asset.
 * @return std::filesystem::path Returns the complete filesystem path for the given asset.
 */
static std::filesystem::path GetAssetFileSystemPath(const std::filesystem::path& Path)
		{
			CoreLogger::Assert((s_ActiveProject != nullptr), "No Active Project!");
			return GetAssetDirectory() / Path;
		}

		/**
 * @brief This function returns the project configuration object.
 * @return A reference to the ProjectConfig object.
 */
ProjectConfig& GetConfig() { return m_Config; }
		/**
 * @brief Returns the ProjectInfo object associated with this class instance.
 * @return A reference to the ProjectInfo object.
 */
ProjectInfo& GetInfo() { return m_Info; }

		static void WriteProjectConfig(const std::filesystem::path& Path, const std::string& ProjectName);
		static void WriteEditorConfig(const std::filesystem::path& Path, const std::string& ProjectName);
		static void ReadProjectConfig(const std::filesystem::path& Path);
		static void ReadEditorConfig(const std::filesystem::path& Path);


		void AddBuiltScenes();

		/**
 * @brief This function returns the currently active project.
 * @return A reference to the current Project object. If no project is currently active, this will be a nullptr.
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
		static std::array<std::string, 6> m_GameContDirNames;
		inline static Ref<Project> s_ActiveProject;

	};
}