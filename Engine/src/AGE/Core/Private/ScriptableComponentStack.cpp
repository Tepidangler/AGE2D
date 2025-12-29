#include "AGEpch.hpp"
#include "Core/Public/ScriptableComponentStack.h"


namespace GameFramework
{
	ScriptableCompStack::ScriptableCompStack()
	{
	}
	ScriptableCompStack::~ScriptableCompStack()
	{
		for (AGE::ScriptableEntity* E : m_Entitys)
		{
			E->~ScriptableEntity();
		}
	}
	void ScriptableCompStack::PushComponent(AGE::ScriptableEntity* Entt)
	{
		m_Entitys.emplace(m_Entitys.begin() + m_EntityInsertIndex, Entt);
		m_EntityInsertIndex++;
	}
	void ScriptableCompStack::PopComponent(AGE::ScriptableEntity* Entt)
	{
		auto it = std::find(m_Entitys.begin(), m_Entitys.end(), Entt);

		if (it != m_Entitys.end())
		{
			m_Entitys.erase(it);
			m_EntityInsertIndex--;
		}
	}
}