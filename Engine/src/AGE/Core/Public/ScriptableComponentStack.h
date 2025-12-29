#pragma once
#include "Core/Public/Core.h"
#include "Scene/Public/ScriptableEntity.h"

namespace GameFramework
{
	class ScriptableCompStack
	{
	public:
		ScriptableCompStack();
		~ScriptableCompStack();

		void PushComponent(AGE::ScriptableEntity* Entt);


		void PopComponent(AGE::ScriptableEntity* Entt);



		std::vector<AGE::ScriptableEntity*>::iterator begin() { return m_Entitys.begin(); }

		std::vector<AGE::ScriptableEntity*>::iterator end() { return m_Entitys.end(); }

		std::vector<AGE::ScriptableEntity*>::const_iterator begin() const { return m_Entitys.cbegin(); }

		std::vector<AGE::ScriptableEntity*>::const_iterator end() const { return m_Entitys.cend(); }

	private:
		std::vector<AGE::ScriptableEntity*> m_Entitys;
		unsigned int m_EntityInsertIndex = 0;
	};
}