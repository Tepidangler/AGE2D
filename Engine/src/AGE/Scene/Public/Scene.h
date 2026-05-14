#pragma once
#include "entt/entt.hpp"
#include "Core/Public/DeltaTime.h"
#include "Core/Public/UUID.h"
#include "Camera/Public/EditorCamera.h"
#include "TileMap/Public/TileMapImporter.h"

namespace AGE
{
	class DataReader;
	class DataWriter;
	class Entity;
	class ScriptableEntity;
	class World;
	class Physics2D;

	struct SceneInfo
	{
		size_t Size = 0;
		std::string Flags = "";
		const char* AssetMap;

		static void Serialize(DataWriter* Serializer, const SceneInfo& Data);

		static void Deserialize(DataReader* Deserializer, SceneInfo& Data);
	};



	class Scene : public std::enable_shared_from_this<Scene>
	{
	public:

		Scene();
		/**
 * @brief Copy constructor for the Scene class is deleted to prevent copying of objects.
 * 
 * The copy constructor for the Scene class is explicitly marked as deleted in order to prevent accidental copying of Scene objects. This is because the Scene class represents a complex data structure that should not be copied unintentionally, leading to unnecessary memory usage and potential issues with object state management.
 * 
 * @param Other The Scene object to copy from.
 */
Scene(const Scene& Other) = delete;
		/**
 * @brief Constructor for the Scene class.
 * @param ID The unique identifier of the scene.
 */
Scene(UUID ID)
			:m_AssetID(ID) {}
		/**
 * @brief Constructs a Scene object with the given name and generates an unique asset ID.
 * @param Name The name of the scene.
 */
Scene(const std::string& Name)
			:m_Name(Name), m_AssetID(UUID()) {}
		~Scene();

		/**
 * @brief Gets the Asset ID of the object.
 *
 * This function returns a reference to the private member variable 'm_AssetID'. It provides access to this data, but does not allow modification.
 *
 * @return A reference to UUID& representing the Asset ID.
 */
UUID& GetAssetID() { return m_AssetID; }
		/**
 * @brief Returns the name of the object.
 *
 * This function returns a reference to the internal string that holds the name of the object. The returned value can be modified by the caller, allowing for dynamic changes in the name.
 *
 * @return A reference to the internal string holding the name.
 */
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

		/**
 * @brief Sets the name of the scene.
 *
 * This function sets the name of the scene to a given string value. The new name is stored in member variable `m_Name`.
 *
 * @param[in] Name - A const reference to the string that will be used as the new name for the scene.
 */
void SetSceneName(const std::string& Name) { m_Name = Name; }

		static Ref<Scene> LoadScene(const std::filesystem::path& Path);

		static void BuildAllScenes();

		Ref<Scene> Copy(Ref<Scene> Other);
		void DuplicateEntity(Entity entity);
		void OnRuntimeStart();
		void OnRuntimeStop();

		template<typename... Components>
		/**
 * @brief Returns a view of all entities that have the specified components in the registry.
 * 
 * The function returns a view containing all entities that possess the types `Components...` as their component types.
 * This can be useful for iterating over these entities and performing operations on them.
 * 
 * @return A range of entity handles representing all entities with the specified components.
 */
auto GetAllEntitiesWith()
		{
			return m_Registry.view<Components...>();
		}

		/**
 * @brief This function sets the callback for handling events.
 * @param Callback The function to be called when an event occurs. It takes an Event& parameter and returns void.
 * @return Unknown
 */
inline void SetEventCallback(const std::function<void(Event&)>& Callback)
		{
			m_SceneEvent = Callback;
		}

		/**
 * @brief This function broadcasts an event to the scene.
 * 
 * @param Event The event that is being broadcasted.
 * @return void No return value expected.
 */
inline void BroadcastEvent(Event& Event)
		{
			m_SceneEvent(Event);
		}

		/**
 * @brief Copy assignment operator for the Scene class.
 * 
 * This function is used to assign the values of one Scene object to another. It takes a constant reference to a Scene object as its parameter, and returns a reference to the current Scene object.
 * 
 * @param Other The Scene object to copy from.
 * @return A reference to the current Scene object after copying.
 */
void operator=(const Scene& Other)
		{

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
		UUID m_AssetID = UUID();

		SceneInfo m_SceneInfo;

		std::function<void(Event&)> m_SceneEvent;

		friend struct TileMapRendererComponent;
		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
		friend struct AGEPin;

	public:

		static void Serialize(DataWriter* Serializer, const Scene& Data);

		static void Deserialize(DataReader* Deserializer, Scene& Data);

	};



}