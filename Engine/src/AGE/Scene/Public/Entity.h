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
		/**
 * @brief Default constructor for the Entity class.
 */
/**
 * @brief Default constructor for the Entity class.
 */
Entity() = default;
		Entity(entt::entity Handle, Scene* ScenePtr);
		/**
 * @brief Copy constructor for the Entity class.
 *
 * This function creates a new instance of an Entity by copying all data from another existing Entity object.
 * It uses the '= default' syntax to delegate the copy construction task to the compiler, which is efficient and safe.
 * 
 * @param other The Entity object to be copied.
 */
/**
 * @brief Copy constructor for the Entity class.
 *
 * This function creates a new instance of an Entity by copying all data from another existing Entity object.
 * It uses the 'default' keyword to allow the compiler to generate its own copy constructor if one is not provided.
 * 
 * @param other The Entity object to be copied.
 */
Entity(const Entity& other) = default;
		//~Entity() = default;

		template<typename T, typename ... Args>
		/**
 * @brief Adds a component of type T to the entity.
 * 
 * This function adds a new component of type T to the entity represented by m_EntityHandle. The arguments are forwarded to the emplace function, allowing for variadic template parameters.
 * 
 * @tparam T The type of the component to be added.
 * @tparam Args The types of the arguments to be passed to the emplace function.
 * @param args The arguments to be passed to the emplace function.
 * 
 * @return A reference to the newly created component.
 * 
 * @pre The entity does not already have a component of type T.
 * @post The new component is added to the entity and an OnComponentAdded event is triggered for this scene.
 */
/**
 * @brief Adds a component of type T to the entity.
 * 
 * This function adds a new component of type T to the entity represented by m_EntityHandle. The arguments are forwarded to the emplace function, allowing for variadic template parameters. If the entity already has a component of this type, an assertion will fail.
 * 
 * @tparam T Type of the component to be added.
 * @tparam Args Variadic template parameter representing the types and/or values of arguments that are forwarded to emplace function.
 * @param args Arguments to be forwarded to emplace function.
 * @return Reference to the newly created component.
 */
T& AddComponent(Args&& ... args)
		{
			CoreLogger::Assert(!HasComponent<T>(), "Entity already has component!");
			T& Component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, Component);
			return Component;
		}

		template<typename T>
		/**
 * @brief Checks if the entity has a specific component in its registry.
 * 
 * This function uses the any_of method from entt's registry to check if an entity has a certain type of component.
 * It returns true if the entity has at least one instance of the specified component, and false otherwise.
 * 
 * @return True if the entity has the component, False otherwise.
 */
/**
 * @brief Checks if the entity has a specific component of type T.
 * 
 * This function uses the any_of method from entt's registry to check if an entity has a certain component of type T.
 * It returns true if the entity has at least one instance of the specified component, and false otherwise.
 * 
 * @return True if the entity has the component, False otherwise.
 */
bool HasComponent()
		{
			
			return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
		}

		template<typename T>
		/**
 * @brief Checks if the entity has a specific component.
 * 
 * This function checks whether an entity in the scene possesses a certain type of component. It does this by using the any_of method from the entt library, which returns true if at least one instance of the given component is associated with the entity.
 * 
 * @return A boolean value indicating whether or not the entity has the specified component. True means it possesses the component, while false signifies its absence.
 */
/**
 * @brief Checks if the entity has a specific component.
 * 
 * This function checks whether an entity in the scene possesses a certain type of component. It does this by using the `any_of` method from the registry associated with the scene, specifically checking for the presence of the specified template parameter 'T' within the components attached to the entity represented by m_EntityHandle.
 * 
 * @return A boolean value indicating whether or not the entity has the component. True if it does, false otherwise.
 */
bool HasComponent() const
		{

			return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
		}

		template<typename T, typename... Args>
		/**
 * @brief Adds or replaces a component of type T in the scene.
 * 
 * This function emplaces an instance of type T into the registry associated with the entity represented by m_EntityHandle, using variadic template arguments for constructor parameters. If a component of type T already exists for this entity, it will be replaced; otherwise, a new one is created. After adding or replacing the component, OnComponentAdded function from the scene class is called to notify any listeners about the change in component state.
 * 
 * @tparam T The type of the component to add or replace.
 * @tparam Args The types of arguments for constructing a new instance of T.
 * @param args Variadic template parameters forwarded to emplace_or_replace function.
 * @return A reference to the added/replaced component.
 */
/**
 * @brief Adds or replaces a component of type T in the scene.
 * 
 * This function emplaces or replaces a component of type T with given arguments into the entity represented by m_EntityHandle. It then calls OnComponentAdded for this component type and returns a reference to it.
 * @tparam T The type of the component to be added or replaced.
 * @tparam Args The types of the arguments to be forwarded to emplace_or_replace function.
 * @param args The arguments to be forwarded to emplace_or_replace function.
 * @return A reference to the newly added or replaced component.
 */
T& AddOrReplaceComponent(Args&&... args)
		{
			T& Component = m_Scene->m_Registry.emplace_or_replace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, Component);
			return Component;
		}

		template<typename T>
		/**
 * @brief Get the Component object of type T associated with this Entity.
 * 
 * This function retrieves a component of type T from the entity. If the entity does not have such a component, an assertion will fail and the program will terminate.
 * The returned reference can be used to modify or access the component's data.
 * 
 * @return T& Reference to the Component object of type T associated with this Entity.
 */
/**
 * @brief Get the Component object of type T associated with this Entity.
 * 
 * This function retrieves a component of type T from the entity. It first checks if the entity has such a component, and throws an exception if it doesn't.
 * The retrieved component is then returned by reference.
 * 
 * @return T& Reference to the Component object.
 */
T& GetComponent()
		{
			CoreLogger::Assert(HasComponent<T>(), "Entity does not have component!");
				return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		/**
 * @brief Get the Component object of type T associated with this entity.
 * 
 * This function retrieves a component of type T from the entity. If the entity does not have such a component, an assertion will be triggered and the program will terminate.
 * 
 * @return const reference to the component of type T
 */
/**
 * @brief Get the Component object of type T associated with this entity.
 * 
 * This function retrieves a component of type T from the entity. If the entity does not have such a component, an assertion will fail and the program will terminate.
 * 
 * @return T& Reference to the component of type T.
 */
T& GetComponent() const
		{
			CoreLogger::Assert(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		/**
 * @brief Removes a component of type T from the entity associated with this handle in the scene's registry.
 * 
 * This function removes a component of type T from the entity represented by m_EntityHandle within the scene's ECS (entity-component-system) registry. The removal is performed using the remove() method provided by the entt library, which expects an instance of the Entity class and a type to be removed.
 * 
 * @return void
 */
/**
 * @brief Removes a component of type T from the entity associated with this handle in the scene's registry.
 * 
 * This function removes a specific instance of a component of type T from the entity represented by m_EntityHandle within the scene's ECS (entity-component system). The removal is performed using the remove function provided by the entt library, which ensures that the component is properly removed and no memory leaks occur.
 * 
 * @return void
 */
void RemoveComponent()
		{
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}


		/**
 * @brief Checks whether the entity handle is not null.
 *
 * This function returns true if the entity handle is not equal to `entt::null`, indicating that an entity exists in the system.
 *
 * @return True if the entity handle is not null (i.e., an entity exists), false otherwise.
 */
/**
 * @brief Checks whether the entity handle is valid (i.e., not null).
 *
 * This function checks if the `m_EntityHandle` member variable of the current object is different from `entt::null`, which represents an invalid or non-existent entity in some context. The function returns true if the handle is valid and false otherwise.
 *
 * @return True if the entity handle is not null; false otherwise.
 */
operator bool() const { return m_EntityHandle != entt::null; }
		/**
 * @brief Converts the entity handle to an `entt` entity.
 *
 * This function returns the underlying `entt::entity` object that this EntityHandle wraps around.
 * It is used internally by various parts of the codebase and should not be called directly by user code.
 * 
 * @return The wrapped `entt::entity` object.
 */
/**
 * @brief Converts the entity handle to an entt::entity object.
 *
 * This function returns the underlying `entt::entity` object that this EntityWrapper is wrapping. It provides a direct access to the actual entity, allowing for operations and manipulations on it.
 *
 * @return The wrapped `entt::entity` object.
 */
operator entt::entity() const { return m_EntityHandle; }
		/**
 * @brief Converts the entity handle to a uint32_t value.
 *
 * This function returns the underlying uint32_t representation of the entity handle. It is used for interoperability with other systems that expect uint32_t values, such as rendering engines or physics engines. 
 *
 * @return The uint32_t representation of the entity handle.
 */
/**
 * @brief Converts the entity handle to a uint32_t value.
 *
 * This function returns the `m_EntityHandle` member variable as a `uint32_t` value. It is used for casting or conversion purposes, allowing it to be treated like an unsigned 32-bit integer.
 *
 * @return The `m_EntityHandle` member variable casted to a uint32_t.
 */
operator uint32_t() const { return (uint32_t)m_EntityHandle; }

		/**
 * @brief This function returns the UUID of an object.
 * 
 * The function uses a component-based system where each object has components associated with it. It retrieves the IDComponent from the object and then returns its UUID.
 * 
 * @return A UUID value representing the unique identifier of the object.
 */
/**
 * @brief This function returns the UUID of the object.
 * @return The UUID of the object as a UUID type.
 */
UUID GetUUID() { return GetComponent<IDComponent>().ID; }
		/**
 * @brief This function returns the name of a component associated with this object.
 * @return A constant reference to the tag string of the TagComponent attached to this object. If no such component exists, an empty string is returned.
 */
/**
 * @brief Returns the name of the component associated with this object.
 * @return A constant reference to a string representing the name of the component.
 */
const std::string& GetName() { return GetComponent<TagComponent>().Tag; }

		/**
 * @brief Compares two entities for equality based on their entity handle and scene.
 * @param Other The Entity to compare with this one.
 * @return True if the other entity has the same entity handle and scene as this one, false otherwise.
 */
/**
 * @brief Compares two entities for equality based on their entity handle and scene.
 * @param Other The Entity to compare with this one.
 * @return True if the other entity has the same entity handle and scene as this one, false otherwise.
 */
bool operator==(const Entity& Other) const
		{
			return m_EntityHandle == Other.m_EntityHandle && m_Scene == Other.m_Scene;
		}

		/**
 * @brief Compares two entities for inequality.
 *
 * This function compares the current entity with another one to determine if they are not equal. It uses the '==' operator to compare the entities and returns the opposite result.
 *
 * @param Other The other Entity object to be compared with this one.
 * @return True if the two entities are not equal, false otherwise.
 */
/**
 * @brief Compares two entities for inequality.
 *
 * This function compares the current entity with another one to determine if they are not equal. It uses the equality operator (`operator==`) to perform the comparison and returns the opposite result.
 *
 * @param Other The other entity to compare with.
 * @return True if the entities are not equal, false otherwise.
 */
bool operator !=(const Entity& Other) const
		{
			return !(*this == Other);
		}

		/**
 * @brief This function serializes an Entity object into a DataWriter object. 
 * The data includes the ID, Tag, Camera, Transform, Sprite, TileMap, Circle, NativeScript, AudioComponent, RigidBody2D, BoxCollider2D, CapsuleCollider2D, and SegmentCollider2D of the Entity. 
 * If an entity does not contain a certain component, it will skip writing that data to avoid errors.
 * @param Serializer A pointer to the DataWriter object where the serialized data will be written.
 * @param Data The Entity object to be serialized.
 */
/**
 * @brief This function is responsible for writing entity data into a serialization format. 
 * It checks if the entity has certain components and writes their data if they exist.
 * 
 * @param[in] Serializer Pointer to an object that can write raw data types.
 * @param[in] Data Const reference to an Entity object which contains various components.
 */
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
				//Serializer->WriteString("TileMap");
				//Serializer->WriteObject<TileMapRendererComponent>(Data.GetComponent<TileMapRendererComponent>());
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

		/**
 * @brief This function deserializes data from a source into an entity object.
 * 
 * The function takes in a pointer to a `DataReader` and a reference to an `Entity` object. It does not return anything, but it modifies the `Entity` object by reading its state from the `DataReader`.
 *
 * @param Deserializer A pointer to the DataReader that provides the serialized data.
 * @param Data The Entity object which will be populated with deserialized data.
 */
/**
 * @brief This function deserializes data from a DataReader into an Entity object.
 * 
 * The function reads the necessary information from the DataReader and populates the Entity object with it.
 * It does not return anything as it directly modifies the passed Entity object.
 * 
 * @param Deserializer A pointer to a DataReader object that contains the serialized data.
 * @param Data The Entity object where the deserialized data will be stored.
 */
static void Deserialize(DataReader* Deserializer, Entity& Data)
		{

		}
	private:

		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;		

	};
};