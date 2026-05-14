//
// Created by gdmgp on 12/30/2025.
//

#ifndef AGE2D_SCRIPTABLEWIDGET_H
#define AGE2D_SCRIPTABLEWIDGET_H
#pragma once
#include "Core/Public/Core.h"
#include "Scene/Public/Entity.h"
#include "Core/Public/DeltaTime.h"
#include "UI/Public/UiComponent.h"


namespace AGE
{

	enum EWidgetStack : uint8_t
	{
		Menu,
		Modal,
		Splash,
		Game,
		INVALID
	};

	class ScriptableWidget : public std::enable_shared_from_this<ScriptableWidget>
	{
	public:
		/**
 * @brief Virtual destructor for the ScriptableWidget class.
 *
 * This function is responsible for freeing any resources that were allocated by the widget, such as memory or file handles. It's a virtual function to allow subclasses of ScriptableWidget to override this behavior if necessary. 
 *
 * @return void
 */
/**
 * @brief Virtual destructor for the ScriptableWidget class.
 *
 * This function is responsible for freeing any resources that were allocated by the widget, such as memory or file handles. It's a virtual function to allow subclasses of ScriptableWidget to override this behavior if necessary.
 */
virtual ~ScriptableWidget() {}

		template<typename T>
		/**
 * @brief This function returns a reference to the component of type T associated with the entity.
 * 
 * @param None
 * 
 * @return A reference to the component of type T.
 */
/**
 * @brief This function returns a reference to the component of type T associated with an entity.
 * 
 * @param None
 * 
 * @return A reference to the component of type T.
 */
T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

		template<typename T, typename ... Args>
		/**
 * @brief This function adds a component of type T to the entity.
 * @tparam T The type of the component that is being added.
 * @tparam Args The types of any additional arguments required for the component's construction.
 * @param args The arguments necessary for constructing the new component.
 * @return A reference to the newly created component.
 */
/**
 * @brief Adds a component of type T to the entity.
 * @tparam T The type of the component to be added.
 * @tparam Args The types of any additional arguments required by the component's constructor.
 * @param args Any additional arguments required by the component's constructor.
 * @return A reference to the newly created component.
 */
T& AddComponent(Args&& ... args)
		{
			return m_Entity.AddComponent<T>();
		}

		virtual void OnEvent(Event& E) {};
		/**
 * @brief Returns the name of this object.
 *
 * This function returns the name of the object as a string. It is used to identify the object in various contexts.
 *
 * @return std::string - The name of the object.
 */
/**
 * @brief Returns the name of this object.
 *
 * @return The name as a string.
 */
virtual std::string GetName() { return m_Name; }
		/**
 * @brief This function returns the unique identifier (UUID) of an entity.
 * @return The UUID of the entity as a UUID object.
 */
/**
 * @brief This function returns the unique identifier (UUID) of an entity.
 * @return The UUID of the entity as a UUID object.
 */
virtual UUID GetID() { return m_Entity.GetUUID(); }
		/**
 * @brief This function checks whether the object is visible or not.
 * @return Returns true if the object is visible, false otherwise.
 */
/**
 * @brief This function checks whether the object is visible.
 * @return Returns true if the object is visible, false otherwise.
 */
virtual bool IsVisible() {return bIsVisible;}
		/**
 * @brief Sets the visibility of an object.
 *
 * This function sets the visibility state of an object to either visible or not visible (hidden).
 * The new visibility state is stored in the member variable 'bIsVisible'.
 *
 * @param Visibility A boolean value indicating whether the object should be visible (true) or hidden (false).
 * 
 * @return void
 */
/**
 * @brief Sets the visibility of an object.
 *
 * This function sets the visibility state of an object to either visible or not visible (hidden).
 * The new visibility state is stored in the member variable 'bIsVisible'.
 *
 * @param Visibility A boolean value indicating whether the object should be visible (true) or hidden (false).
 */
virtual void SetVisibility(bool Visibility) { bIsVisible = Visibility; }
		RTTR_ENABLE()
		RTTR_REGISTRATION_FRIEND

	protected:
		/**
 * @brief Initializes the object.
 *
 * This function is responsible for initializing the object and its internal state. It does not take any parameters and does not return anything.
 */
/**
 * @brief Initializes the object.
 *
 * This function is responsible for initializing the object and its internal state. It does not take any parameters and does not return anything.
 */
virtual void OnInit() {}
		/**
 * @brief This function is called when the object is being constructed.
 *
 * @return None
 */
/**
 * @brief This function is called when the object is being constructed.
 *
 * It does not take any parameters and does not return anything. The exact behavior of this function depends on its implementation in derived classes.
 */
virtual void OnConstruct() {}
		/**
 * @brief This function is called when the object is being destroyed.
 *
 * @return None
 */
/**
 * @brief This function is called when the object is being destroyed.
 *
 * @return None
 */
virtual void OnDestroy() {}
		/**
 * @brief This function is called every frame to update the game state based on the time elapsed since the last call.
 * 
 * @param DeltaTime The time step representing the amount of time that has passed since the previous frame.
 * @return void No return value expected as this function does not provide any meaningful result.
 */
/**
 * @brief This function is called every frame to update the game state.
 * 
 * @param DeltaTime The time elapsed since the last frame, used for smooth movement and animation.
 */
virtual void OnUpdate(TimeStep DeltaTime) {}
		/**
 * @brief This function is used to reset the state of an object or a system. It does not take any parameters and returns nothing.
 *        The exact effect depends on the specific implementation of the class that uses this method.
 * 
 * @return void
 */
/**
 * @brief This function resets the state of an object to its initial state.
 *
 * The exact behavior of this function depends on the specific implementation of the class that contains it. It may reset all internal data, set default values, or perform other actions as specified by the class's design.
 *
 * @return void
 */
virtual void Reset() {}
		/**
 * @brief Returns a reference to the entity object.
 *
 * This function returns a reference to the internal entity object, which can be used for further operations on it.
 *
 * @return A reference to the entity object (Entity&).
 */
/**
 * @brief This function returns a reference to the entity object.
 * @return A reference to the entity object (m_Entity).
 */
virtual Entity& GetEntityHandle() { return m_Entity; }
		std::string m_Name = "";
		bool bIsVisible = true;
		ScreenResolution m_Resolution;
		std::vector<Ref<UIComponent>> m_UIComponents;
		EWidgetStack m_Stack = EWidgetStack::INVALID;

	private:
		Entity m_Entity;
		friend class Scene;
		friend class WidgetStack;

	};
}



#endif //AGE2D_SCRIPTABLEWIDGET_H