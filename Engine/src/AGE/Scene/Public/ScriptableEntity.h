/**

    @file      ScriptableEntity.h
    @brief     
    @details   ~
    @author    De'Lano Wilcox
    @date      29.05.2025
    @copyright � Alcoy Game Studios, 2025. All right reserved.

**/
#pragma once
#include "Scene/Public/Entity.h"
#include "Structs/Public/Functions.h"
#include <rttr/type>
#ifdef __clang__
#pragma clang diagnostic push
#ifdef AG_PLATFORM_LINUX
#pragma clang diagnostic ignored "-Wunused-function"
#endif
#include "rttr/registration_friend.h"
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
#include "rttr/registration_friend.h"
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(push, 0)
#include "rttr/registration_friend.h"
#pragma warning(pop)
#else
#error "Compiler is not supported with AGE yet"
#endif



namespace AGE
{
	enum class MetaDataType
	{
		Scriptable,
	};
	struct AGENode;

	class ScriptableEntity : public std::enable_shared_from_this<ScriptableEntity>
	{
	public:

		vi/**
 * @brief Virtual destructor for the ScriptableEntity class.
 *
 * This function is a virtual destructor that cleans up any resources used by an instance of the class when it's no longer needed.
 * It does not take any parameters and returns nothing.
 */
rtual ~S/**
 * @brief Constructor for the CriptableEntity class.
 */
criptableEntity() {};

  /**
      @brief  
      @retval - bool 
      @author De'Lano Wilcox
  **/
		vi/**
 * @brief Checks whether the scriptable entity is of type "Character".
 *
 * This function compares the result of `GetScriptableEntityType` with the string literal "Character", and returns true if they match. Otherwise, it returns false.
 * 
 * @return True if the scriptable entity type equals "Character", False otherwise.
 */
rtual bo/**
 * @brief Checks whether the scriptable entity type is a character.
 *
 * This function compares the scriptable entity type to "Character". If they match, it returns true; otherwise, false.
 *
 * @return True if the scriptable entity type is "Character", false otherwise.
 */
ol IsCharacter()
		{
			return GetScriptableEntityType() == "Character";
		}
  /**
      @brief  
      @tparam T - Represents Component within the Entity Component System
      @retval   - T
      @author De'Lano Wilcox
  **/
		template<typename T>
		T&/**
 * @brief Retrieves the component of type T from the entity.
 *
 * This function retrieves a component of type T from the entity using the GetComponent method from the m_Entity object, which is assumed to provide this functionality. If the component exists, it returns it; otherwise, it returns a default value for type T.
 *
 * @return The component of type T if it exists, or a default value for type T if it does not exist.
 */
/**
 * @brief Gets the component of type T from the entity.
 * 
 * This function retrieves a component of type T from the entity. It uses the GetComponent method from the m_Entity object, which is assumed to be an instance of some class that provides this functionality.
 *
 * @return The component of type T if it exists, otherwise it returns a default value for type T.
 */
 GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

		template<typename T, typename ... Args>
		T&/**
 * @brief This function adds a component of type T to the entity.
 * @tparam T The type of the component to be added.
 * @tparam Args The types of any additional arguments required by the AddComponent method.
 * @param args Any additional arguments required by the AddComponent method.
 * @return Returns the result of calling m_Entity's AddComponent method with template parameter T and provided arguments.
 */
/**
 * @brief This function adds a component of type T to the entity.
 * @tparam T The type of the component to be added.
 * @tparam Args The types of any additional arguments required by the AddComponent method.
 * @param args Any additional arguments required by the AddComponent method.
 * @return Returns the result of calling m_Entity's AddComponent method with template parameter T and provided arguments.
 */
 AddComponent(Args&& ... args)
		{
			return m_Entity.AddComponent<T>();
		}

		vi/**
 * @brief This function returns the scriptable entity type as a string.
 * @return A string representing the scriptable entity type, or "Unknown" if not known.
 */
rtual st/**
 * @brief This function returns the scriptable entity type as a string.
 * @return A string representing the scriptable entity type, or an empty string if no specific type is set.
 */
d::string GetScriptableEntityType() { return ""; }
		virtual void OnEvent(Event& E) {};
		vi/**
 * @brief This function is called when an overlap starts between two objects.
 *
 * The exact behavior of this function depends on the specific implementation in any derived classes. It's assumed that it will be overridden by those classes to provide their own functionality.
 *
 * @return void
 */
rtual vo/**
 * @brief This function is called when an overlap starts.
 *
 * @return Unknown
 */
id OnOverlapStart() {}
		vi/**
 * @brief This function is called when an overlap stops.
 *
 * Detailed explanation of what this function does goes here. It should be concise and clear, explaining the purpose and behavior of the function in a way that's understandable to someone unfamiliar with the codebase. 
 *
 * @return void
 */
rtual vo/**
 * @brief This function is called when an overlap occurs between two objects. The exact behavior of this function is not known as it has not been implemented yet.
 * @return Unknown
 */
id OnOverlapStop() {}
		vi/**
 * @brief This function is called when an object gets hit by another object.
 * 
 * @return None
 */
rtual vo/**
 * @brief This function is called when an object gets hit by another object.
 * 
 * @return void
 */
id OnHit() {}

		virtual void AddBeginPlayFunctions(AGEFunction< AGENode, ScriptableEntity> Func) {};
		virtual void AddTickFunctions(AGEFunction< AGENode, ScriptableEntity> Func) {};

		virtual void ClearFunctions() {};
		vi/**
 * @brief Returns the name of the object.
 *
 * This function returns a string that represents the name of the object. It is designed to be overridden in derived classes, so it will return an empty string by default.
 * 
 * @return A std::string representing the name of the object. In this case, it will always return an empty string.
 */
rtual st/**
 * @brief This function returns the name of an object.
 * @return A string representing the name of the object. In this case, it will always be an empty string as there is no specific name set for the object.
 */
d::string GetName() { return ""; };
		viCOMMENT:
/**
 * @brief Returns the current location of the object.
 * @return A Vector3 representing the current location of the object. If no specific location is set, it returns an empty vector.
 */
CONFIDENCE: 1.0;

rt/**
 * @brief Returns the location of an object in a three-dimensional space.
 * @return A Vector3 object representing the location of the object. If no specific location is set, it returns a default constructed one.
 */
ual Vector3 GetLocation() { return {}; }
		vi/**
 * @brief Sets the location of an object.
 *
 * This function sets the location of an object in a three-dimensional space. The location is represented by a Vector3 structure, which contains x, y and z coordinates.
 *
 * @param Location A const reference to an AGE::Vector3 representing the new location of the object.
 * @return void
 */
rtual vo/**
 * @brief Sets the location of an object.
 *
 * This function sets the location of an object in a 3D space. The location is represented by a Vector3 structure, which contains x, y and z coordinates.
 *
 * @param Location A const reference to an AGE::Vector3 representing the new location of the object.
 * @return Unknown
 */
id SetLocation(const AGE::Vector3& Location) {}

		vi/**
 * @brief Returns the unique identifier of the entity.
 *
 * This function retrieves and returns the unique identifier (UUID) associated with an entity. The UUID is a universally unique identifier that is used to identify entities in a system. 
 *
 * @return A UUID representing the identity of the entity.
 */
rtual UU/**
 * @brief This function returns the ID of an entity.
 * @return The UUID (Universally Unique Identifier) of the entity.
 */
ID GetID() { return m_Entity.GetUUID(); }

	protected:
		virtual void OnCreate() {};
		virtual void OnBeginPlay() {};
		virtual void OnDestroy() {};
		virtual void OnUpdate(TimeStep DeltaTime) {};
		virtual void Reset() {};
		vi/**
 * @brief This function returns a reference to the entity object.
 * @return A reference to the entity object (m_Entity).
 */
rtual En/**
 * @brief This function returns a reference to the entity object.
 * @return A reference to the entity object (m_Entity).
 */
tity& GetEntityHandle() { return m_Entity; }
		virtual void PushComp();

	private:
		Entity m_Entity;
		friend class Scene;
		RTTR_ENABLE()
		RTTR_REGISTRATION_FRIEND
	};
}
