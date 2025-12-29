
#pragma once
#include "GameState/Public/GameState.h"
#include "Quests/Public/QuestManager.h"
#include <rttr/registration>


namespace GameFramework
{
	class  QuestComponent final
	{
	public:
		QuestComponent()
		{
			OnCreate();
		}
		QuestComponent(const QuestComponent&) = default;
		QuestComponent(const QuestComponent&&) = delete;
		~QuestComponent() = default;

		void OnCreate();
		void OnDestroy();
		void OnUpdate(AGE::TimeStep DeltaTime);
		void OnEvent(AGE::Event& E);

		AGE::Ref<QuestManager>& GetQuestManager();

		std::string& GetQuestName() { return m_Name; }

		int GetQuest();

		AGE::UUID GetID() { return m_ID; }

		int& GetCheckpointNumber() { return m_CheckpointNumber; }

		void SetQuestID(const std::string& QuestName);

	private:

		AGE::Ref<GameState> m_GameState;

		std::vector<AGE::Ref<Item>> m_ItemRewards;

		AGE::UUID m_ID;

		std::string m_Name = "None";

		bool bShouldAdvance = false;

		int m_CheckpointNumber = 0;

		RTTR_ENABLE()
		RTTR_REGISTRATION_FRIEND
	};
}