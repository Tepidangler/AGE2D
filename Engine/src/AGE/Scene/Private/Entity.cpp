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
/**
 * @brief Constructs an Entity object with the given handle and scene pointer.
 * 
 * This constructor initializes a new Entity instance with the provided entt::entity handle and Scene* pointer. The entity handle is used to identify this entity within its parent scene, while the Scene* pointer allows access to the rest of the scene's data.
 * @param Handle The unique identifier for this entity.
 * @param ScenePtr A pointer to the scene that contains this entity.
 */
Entity::Entity(entt::entity Handle, Scene* ScenePtr)
		:m_EntityHandle(Handle), m_Scene(ScenePtr)
	{
	}
}