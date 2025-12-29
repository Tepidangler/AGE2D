#pragma once
#include "entt/entt.hpp"
#include "Core/Public/DeltaTime.h"
#include "Core/Public/UUID.h"
#include "Camera/Public/EditorCamera.h"
#include "TileMap/Public/TileMapImporter.h"
#include "Serializers/Public/DataWriter.h"
#include "Serializers/Public/DataReader.h"

namespace AGE
{
	class Entity;
	class ScriptableEntity;
	class World;
	class Physics2D;

	struct SceneInfo
	{
		size_t Size = 0;
		std::string Flags = "";
		const char* AssetMap;

		static void Serialize(DataWriter* Serializer, const SceneInfo& Data)
		{
			Serializer->WriteRaw<size_t>(sizeof(*Data.AssetMap));
			Serializer->WriteString(Data.Flags);
			Serializer->WriteRaw<const char*>(Data.AssetMap);
		}

		static void Deserialize(DataReader* Deserializer, SceneInfo& Data)
		{
			Deserializer->ReadRaw<size_t>(Data.Size);
			Deserializer->ReadString(Data.Flags);
			Deserializer->ReadRaw<const char*>(Data.AssetMap);
		}
	};



	class Scene : public std::enable_shared_from_this<Scene>
	{
	public:

		Scene();
		Scene(const Scene& Other) = default;
		Scene(UUID ID)
			:m_AssetID(ID) {}
		Scene(const std::string& Name)
			:m_Name(Name), m_AssetID(UUID()) {}
		~Scene();

		UUID& GetAssetID() { return m_AssetID; }
		std::string& GetName() { return m_Name; }
		Entity CreateEntity(const std::string Name = "");
		Entity CreateEntityWithUUID(UUID uuid, const std::string& Name = std::string());

		Entity GetEntityFromUUID(const uint64_t uuid);

		Entity GetPrimaryCameraEntity();

		void OnRuntimeUpdate(TimeStep DeltaTime);
		void OnEditorUpdate(TimeStep DeltaTime, EditorCamera& Camera);

		void OnViewportResize(uint32_t Width, uint32_t Height);

		void DestoryEntity(Entity E);

		void BuildScene(const std::filesystem::path& ProjectPath);

		void SetSceneName(const std::string& Name) { m_Name = Name; }

		static Ref<Scene> LoadScene(const std::filesystem::path& Path);

		static void BuildAllScenes();

		Ref<Scene> Copy(Ref<Scene> Other);
		void DuplicateEntity(Entity entity);
		void OnRuntimeStart();
		void OnRuntimeStop();

		template<typename... Components>
		auto GetAllEntitiesWith()
		{
			return m_Registry.view<Components...>();
		}

		inline void SetEventCallback(const std::function<void(Event&)>& Callback)
		{
			m_SceneEvent = Callback;
		}

		inline void BroadcastEvent(Event& Event)
		{
			m_SceneEvent(Event);
		}


	private:
		template<typename T>
		void OnComponentAdded(Entity E, T& Component);

	private:
		entt::registry m_Registry;

		std::string m_Name;
		uint32_t m_ViewportWidth = 0;
		uint32_t m_ViewportHeight = 0;

		Ref<Physics2D> m_Physics;
		TileMapImporter m_Importer;
		UUID m_AssetID = UUID();

		SceneInfo m_SceneInfo;

		std::function<void(Event&)> m_SceneEvent;

		friend struct TileMapRendererComponent;
		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
		friend struct AGEPin;

	public:

		static void Serialize(DataWriter* Serializer, const Scene& Data)
		{
			Serializer->WriteRaw<size_t>(Data.m_Name.size());
			Serializer->WriteString(Data.m_Name);
			Serializer->WriteRaw<uint32_t>(Data.m_ViewportWidth);
			Serializer->WriteRaw<uint32_t>(Data.m_ViewportHeight);
			Serializer->WriteObject<SceneInfo>(Data.m_SceneInfo);
		}

		static void Deserialize(DataReader* Deserializer, Scene& Data)
		{
			Deserializer->ReadString(Data.m_Name);
			Deserializer->ReadRaw<uint32_t>(Data.m_ViewportWidth);
			Deserializer->ReadRaw<uint32_t>(Data.m_ViewportHeight);
			Deserializer->ReadObject<SceneInfo>(Data.m_SceneInfo);
		}

	};



}