#pragma once
#include <string>
#include <vector>
#include <GameFramework.h>
#include <imgui.h>

namespace AGE
{
	class QuestManagerWindow
	{
	public:
		QuestManagerWindow();

		void OnImGuiRender();

		void DrawSelection(const std::string& CurrentQuestName);

		void OpenWindow();

		void DrawAddQuest();

		void ImportQuest();

		void RenderWindow(const char* WindowName, bool* IsOpen);

		void Sync();
	private:

		GameFramework::QuestInfo m_SelectionContext;
		std::string m_ItemToAdd;
		std::vector<std::string> m_QuestNameStrings;
		std::string m_CurrentQuestName;
		bool m_bIsOpen = false;
		bool m_bAddingNewQuest = false;
		AGE::Ref<GameFramework::QuestManager> m_QuestManager;
	};
}