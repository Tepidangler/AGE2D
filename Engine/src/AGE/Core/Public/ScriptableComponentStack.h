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



		/**
 * @brief Returns an iterator pointing to the beginning of the 'm_Entitys' vector.
 * @return An iterator to the start of the 'm_Entitys' vector.
 */
/**
 * @brief Returns an iterator pointing to the beginning of the 'm_Entitys' vector.
 * @return An iterator to the start of the 'm_Entitys' vector.
 */
std::vector<AGE::ScriptableEntity*>::iterator begin() { return m_Entitys.begin(); }

		/**
 * @brief Returns an iterator pointing to the theoretical element that follows the last element of the container.
 * This function returns an iterator pointing to one past the last element in the vector, which is considered as a valid position for insertion but does not point to any real data.
 * 
 * @return An iterator to the theoretical element that follows the end of the sequence.
 */
/**
 * @brief Returns an iterator pointing to the theoretical element that follows the last element of the vector.
 * @return An iterator to the theoretical element following the last element of the vector.
 */
std::vector<AGE::ScriptableEntity*>::iterator end() { return m_Entitys.end(); }

		/**
 * @brief Returns a constant iterator pointing to the beginning of the 'm_Entitys' vector.
 * @return A constant iterator to the beginning of the 'm_Entitys' vector. If the vector is empty, past-the-end (cend) iterator is returned.
 */
/**
 * @brief Returns a constant iterator pointing to the beginning of the 'm_Entitys' vector.
 * @return A constant iterator to the beginning of the 'm_Entitys' vector.
 */
std::vector<AGE::ScriptableEntity*>::const_iterator begin() const { return m_Entitys.cbegin(); }

		/**
 * @brief Returns a constant iterator pointing to the past-the-end element of the container.
 * @return A constant iterator pointing to the past-the-end element in the container.
 */
/**
 * @brief Returns a constant iterator pointing to the past-the-end element of the container.
 * @return A constant iterator pointing to the past-the-end element in the container.
 */
std::vector<AGE::ScriptableEntity*>::const_iterator end() const { return m_Entitys.cend(); }

	private:
		std::vector<AGE::ScriptableEntity*> m_Entitys;
		unsigned int m_EntityInsertIndex = 0;
	};
}