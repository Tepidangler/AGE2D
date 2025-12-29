#pragma once
#include <string>
#include <filesystem>
#include <array>	
namespace AGE
{
	class ProjectMenu
	{
	public:

		ProjectMenu() = default;

		void OnImGuiRender();
	private:
		void NewScene();
		void NewProject(const std::string& ProjectName);
		void OpenProject(const std::string& ProjectName);
		void OpenScene(const std::filesystem::path& FilePath);
		void SaveScene(const std::string& SceneName);
		void SaveProject();
		void CreateProject();
		void LoadProject();

	private:
		std::filesystem::path m_ProjectFilePath;
		int bCreateProject = -1;
		bool bMakeChoice = true;


	};
}
