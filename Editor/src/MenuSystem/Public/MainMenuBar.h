#pragma once
#if !AG_DIST
#include "imgui.h"
#include <Age.h>

namespace AGE
{
	struct AxisBindingData
	{
		std::string ActionName;
		std::string Name;
		Binding::Type Type = Binding::Axis;
		uint16_t Axis;
		int Index = 8;
	};

	struct ActionBindingData
	{
		std::string ActionName;
		std::string Name;
		Binding::Type Type = Binding::Action;
		uint16_t Button;
		int Index = 8;
	};

	class MainMenuBar : public AGE::Layer
	{
	public:

		MainMenuBar();
		virtual ~MainMenuBar() {};

		void OnEvent(AGE::Event& E) override;

		bool OnKeyPressed(AGE::KeyPressedEvent& E);
		void OnDuplicateEntity();

		void OnImGuiRender(AGE::TimeStep DeltaTime) override;

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
		void SaveInputIni();
		void LoadInputIni();
		void OpenNodeEditor();
		std::filesystem::path LoadQuestFile();

		void PackageGame();

		[[nodiscard]] bool IsShowingPhysicsColliders() const { return bShowPhysicsColliders; }

		void DrawAxisBindings();
		void DrawActionBindings();

		void DrawAxisCombo(int i);
		void DrawActionCombo(int i);

		void OpenQuestManager();

		void OpenInventoryDatabase();

		void OpenDatabase();

		void SyncBindings();

	private:
		std::string m_SceneFilePath;
		std::filesystem::path m_ProjectFilePath;
		std::filesystem::path m_QuestFilePath;

		std::vector<std::string> m_SceneNames;
		std::array<std::string,9> m_AxisBindingStrings{ "Left Joystick X", "Left Joystick Y", "Right Joystick X", "Right Joystick Y", "DPad Left", "DPad Up", "DPad Right", "DPad Down", "None" };
		std::array<std::string,11> m_ActionBindingStrings{ "Face Button Bottom", "Face Button Right", "Face Button Left", "Face Button Top", "Left Bumper Button", "Right Bumper Button", "Select Button", "Start Button", "Guide Button", "Left Thumbstick", "Right Thumbstick"};

		bool bShowPhysicsColliders = false;
		bool bChooseAudioEngine = false;
		bool bCreateProject = false;
		bool bEditProjectSettings = false;
		bool bAxisBindingsSynced = false;
		bool bActionBindingsSynced = false;

		std::vector<Ref<InputBinding>> m_AxisBindings;
		std::vector<Ref<InputBinding>> m_ActionBindings;
		std::vector<AxisBindingData> m_AxisBindingData;
		std::vector<ActionBindingData> m_ActionBindingData;

		std::string m_CurrentAxisBindingString{};
		std::string m_CurrentActionBindingString{};

		Ref<Scene> m_ActiveScene;
	};
}
#endif //AG_DIST