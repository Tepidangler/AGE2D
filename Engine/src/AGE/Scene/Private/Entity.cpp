#include "AGEpch.hpp"
#include "Scene/Public/Entity.h"


namespace AGE
{
	Entity::Entity(entt::entity Handle, Scene* ScenePtr)
		:m_EntityHandle(Handle), m_Scene(ScenePtr)
	{
	}
}