#include "AGEpch.hpp"
#include "Core/Public/ScriptableComponentStack.h"


namespace GameFramework
{
	/**
 * @brief Constructor for the ScriptableCompStack class. 
 * Initializes an empty stack of components.
 */
ScriptableCompStack::ScriptableCompStack()
	{
	}
	/**
 * @brief Destructor for the ScriptableCompStack class. It iterates over all elements in the vector 'm_Entitys' and deletes each one using the destructor of the ScriptableEntity class.
 */
ScriptableCompStack::~ScriptableCompStack()
	{
		for (AGE::ScriptableEntity* E : m_Entitys)
		{
			E->~ScriptableEntity();
		}
	}
	/**
 * @brief Pushes a ScriptableEntity onto the stack at the specified index.
 * 
 * This function inserts a new ScriptableEntity into the m_Entitys vector at the position indicated by m_EntityInsertIndex. The entity is then incremented for the next push operation.
 * 
 * @param Entt Pointer to the ScriptableEntity that will be pushed onto the stack.
 * @return void No return value.
 */
void ScriptableCompStack::PushComponent(AGE::ScriptableEntity* Entt)
	{
		m_Entitys.emplace(m_Entitys.begin() + m_EntityInsertIndex, Entt);
		m_EntityInsertIndex++;
	}
	/**
 * @brief Removes a ScriptableEntity from the stack of components.
 * 
 * This function searches for the provided ScriptableEntity in the m_Entitys vector and removes it if found. It also decrements the m_EntityInsertIndex by one to ensure that new entities are inserted at the correct position.
 * 
 * @param Entt Pointer to the ScriptableEntity to be removed from the stack.
 * 
 * @return void
 */
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