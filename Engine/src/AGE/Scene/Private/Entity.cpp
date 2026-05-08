#include "AGEpch.hpp"
#include "Scene/Public/Entity.h"


namespace AGE
{
	/** 
 * @brief Constructs an Entity object with the given handle and scene pointer.
 * 
 * @param Handle The entity handle to be associated with this Entity.
 * @param ScenePtr Pointer to the Scene that this Entity belongs to.
 */
Entity::Entity(entt::entity Handle, Scene* ScenePtr)
		:m_EntityHandle(Handle), m_Scene(ScenePtr)
	{
	}
}