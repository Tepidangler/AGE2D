#pragma once
#if !AG_DIST
#include "imgui.h"
#include <Age.h>

namespace AGE
{
	class MainMenuBar : public AGE::Layer
	{
	public:

		MainMenuBar();
		virtual ~MainMenuBar() {};

		virtual void OnEvent(AGE::Event& E) override;

		bool OnKeyPressed(AGE::KeyPressedEvent& E);
		void OnDuplicateEntity();

		virtual void OnImGuiRender(AGE::TimeStep DeltaTime) override;

		void MakeMainMenuBar();

		void MakeProjectConfigMenu();

		void SerializeScene(Ref<Scene> scene, const std::filesystem::path& Path);

		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& FilePath);
		void SaveScene();
		void SaveAsScene();
		void NewProject(const std::string& ProjectName);
		void OpenProject();
		void SaveProject();
		void SaveProjectIniFile();
		void LoadProjectIniFile();
		void OpenNodeEditor();
		std::filesystem::path LoadQuestFile();

		void PackageGame();

		bool IsShowingPhysicsColliders() { return bShowPhysicsColliders; }

		void DrawAxisCombo(int i, int x);
		void DrawActionCombo(int i, int x);

		void OpenQuestManager();

		void OpenInventoryDatabase();

		void OpenDatabase();

	private:
		std::string m_SceneFilePath;
		std::filesystem::path m_ProjectFilePath;
		std::filesystem::path m_QuestFilePath;

		std::vector<std::string> m_SceneNames;
		
		bool bShowPhysicsColliders = false;
		bool bChooseAudioEngine = false;
		bool bCreateProject = false;
		bool bEditProjectSettings = false;
		bool bAxisBindingsSynced = false;
		bool bActionBindingsSynced = false;

		std::vector<std::pair<std::string, std::vector<uint8_t>>> m_AxisBindings;
		std::vector<std::pair<std::string, std::vector<uint8_t>>> m_ActionBindings;

		Ref<Scene> m_ActiveScene;
	};
}
#endif //AG_DIST