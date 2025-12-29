#pragma once
#include "Core/Public/UUID.h"
#include "Scene/Public/Scene.h"
#include "Scene/Public/Components.h"
#include "entt/entt.hpp"

namespace AGE
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity Handle, Scene* ScenePtr);
		Entity(const Entity& other) = default;
		//~Entity() = default;

		template<typename T, typename ... Args>
		T& AddComponent(Args&& ... args)
		{
			AGE_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			T& Component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, Component);
			return Component;
		}

		template<typename T>
		bool HasComponent()
		{
			
			return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent() const
		{

			return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
		}

		template<typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args)
		{
			T& Component = m_Scene->m_Registry.emplace_or_replace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, Component);
			return Component;
		}

		template<typename T>
		T& GetComponent()
		{
			AGE_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
				return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		T& GetComponent() const
		{
			AGE_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}


		operator bool() const { return m_EntityHandle != entt::null; }
		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }

		UUID GetUUID() { return GetComponent<IDComponent>().ID; }
		const std::string& GetName() { return GetComponent<TagComponent>().Tag; }

		bool operator==(const Entity& Other) const
		{
			return m_EntityHandle == Other.m_EntityHandle && m_Scene == Other.m_Scene;
		}

		bool operator !=(const Entity& Other) const
		{
			return !(*this == Other);
		}

		static void Serialize(DataWriter* Serializer, const Entity& Data)
		{

			if (!Data.HasComponent<IDComponent>())
			{
				CoreLogger::Error("Entity Does Not Contain and ID!");
				CoreLogger::Error("Moving On to Next Entity!");
				return;
			}

			Serializer->WriteString("ID");
			Serializer->WriteRaw<uint64_t>(Data.GetComponent<IDComponent>().ID);


			if (Data.HasComponent<TagComponent>())
			{
				Serializer->WriteString("Tag");
				Serializer->WriteString(Data.GetComponent<TagComponent>().Tag);
			}

			if (Data.HasComponent<CameraComponent>())
			{
				Serializer->WriteString("Camera");

				Serializer->WriteObject<CameraComponent>(Data.GetComponent<CameraComponent>());


			}

			if (Data.HasComponent<TransformComponent>())
			{
				Serializer->WriteString("Transform");
				Serializer->WriteObject<TransformComponent>(Data.GetComponent<TransformComponent>());
			}

			if (Data.HasComponent<SpriteRendererComponent>())
			{

				Serializer->WriteString("Sprite");
				
				Serializer->WriteObject<SpriteRendererComponent>(Data.GetComponent<SpriteRendererComponent>());

			}

			if (Data.HasComponent<TileMapRendererComponent>())
			{
				Serializer->WriteString("TileMap");
				Serializer->WriteObject<TileMapRendererComponent>(Data.GetComponent<TileMapRendererComponent>());
			}
			if (Data.HasComponent<CircleRendererComponent>())
			{
				Serializer->WriteString("Circle");

				Serializer->WriteObject<CircleRendererComponent>(Data.GetComponent<CircleRendererComponent>());
			}

			if (Data.HasComponent<NativeScriptComponent>())
			{
				Serializer->WriteString("NativeScript");
				Serializer->WriteObject<NativeScriptComponent>(Data.GetComponent<NativeScriptComponent>());
			}

			if (Data.HasComponent<AudioComponent>())
			{
				Serializer->WriteString("AudioComponent");
				Serializer->WriteObject<AudioComponent>(Data.GetComponent<AudioComponent>());
			}

			if (Data.HasComponent<RigidBody2DComponent>())
			{

				Serializer->WriteString("RigidBody2D");

				Serializer->WriteObject<RigidBody2DComponent>(Data.GetComponent<RigidBody2DComponent>());
			}

			if (Data.HasComponent<BoxCollider2DComponent>())
			{
				Serializer->WriteString("BoxCollider2D");

				Serializer->WriteObject<BoxCollider2DComponent>(Data.GetComponent<BoxCollider2DComponent>());
			}
			if (Data.HasComponent<CapsuleCollider2DComponent>())
			{
				Serializer->WriteString("CapsuleCollider2D");
				Serializer->WriteObject<CapsuleCollider2DComponent>(Data.GetComponent<CapsuleCollider2DComponent>());
			}
			if (Data.HasComponent<SegmentCollider2DComponent>())
			{
				Serializer->WriteString("SegmentCollider2D");
				Serializer->WriteObject<SegmentCollider2DComponent>(Data.GetComponent<SegmentCollider2DComponent>());
			}
		}

		static void Deserialize(DataReader* Deserializer, Entity& Data)
		{

		}
	private:

		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;		

	};
};