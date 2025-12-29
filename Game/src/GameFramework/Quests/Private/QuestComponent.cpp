#include <Core/Public/AGEpch.hpp>
#include <Age.h>
#include "Quests/Public/QuestComponent.h"
#include <rttr/registration>

RTTR_REGISTRATION
{
	rttr::registration::class_<GameFramework::QuestComponent>("Quest Component")
	.constructor<>()
	.method("GetQuestManager", &GameFramework::QuestComponent::GetQuestManager);
}

namespace GameFramework
{
	void QuestComponent::OnCreate()
	{
		m_GameState = GameState::Get()->GetSharedPtr(); // I know this looks kind of crazy getting a shared ptr from a singleton, but there cannot be multiple game states

		if (m_GameState->GetQuestManager()->GetQuests().size() > 0)
		{
			for (auto& Q : m_GameState->GetQuestManager()->GetQuests())
			{
				if (Q.second->QuestName == m_Name)
				{
					m_ID = Q.second->ID;
					break;
				}
			}
		}

	}
	void QuestComponent::OnDestroy()
	{
	}
	void QuestComponent::OnUpdate(AGE::TimeStep DeltaTime)
	{
		//Do some stuff on Tick
		if (bShouldAdvance)
		{
			m_GameState->GetQuestManager()->AdvanceQuest(m_ID);
		}
	}
	void QuestComponent::OnEvent(AGE::Event& E)
	{
	}
	AGE::Ref<QuestManager>& QuestComponent::GetQuestManager()
	{
		return m_GameState->GetQuestManager();
	}
	int QuestComponent::GetQuest()
	{
		int index = 0;
		for (auto& Q : m_GameState->GetQuestManager()->GetQuests())
		{
			if (Q.second->QuestName == m_Name)
			{
				return index;
			}
			index++;
		}

		return 0;
	}
	void QuestComponent::SetQuestID(const std::string& QuestName)
	{

		for (auto& Q : m_GameState->GetQuestManager()->GetQuests())
		{
			if (Q.second->QuestName == QuestName)
			{
				m_ID = Q.second->ID;
				break;
			}
		}
	}
}