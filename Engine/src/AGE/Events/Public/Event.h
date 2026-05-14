#pragma once

#include "Core/Public/AGEpch.hpp"
#include "Core/Public/Core.h"




namespace AGE
{
	// Events are currently blocking, which means when an event occurs it immediately gets dispatched and must be dealt with.
	// TODO: Buffer events in an event bus and update them during the event part of the update stage


	enum class EventType // Type of Events {Window, App, Key, Mouse}
	{
		None = 0,
		WindowClose,WindowResize,WindowFocus,WindowLostFocus,WindowMoved,
		ProjectCreated,ProjectLoaded,
		FramebufferResize,
		RendererChanged,RenderUI,
		AppTick,AppUpdate,AppRender,
		StringCopy,StringPaste,
		KeyPressed,KeyReleased,KeyTyped,
		MouseButtonPressed,MouseButtonReleased,MouseMoved,MouseScrolled,
		AxisMoved,
		GamepadButtonPressed,GamepadButtonReleased,
		SceneChanged,
		WidgetConstructed, WidgetActivated,WidgetDeactivated
	};

	enum EventCategory  // Used to Filter events if needed
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4),
		EventCategoryGame = BIT(5),
		EventCategoryUI = BIT(6)

	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::type; }\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category;}

	/**
 * @brief Abstract base class for an event.
 *
 * This is the abstract base class that represents a generic event in the system. It provides methods to get information about the type of the event, its category flags and whether it has been handled or not. 
 */
/**
 * @brief Represents an event in the system.
 *
 * This class represents a generic event that can be handled by various components of the system. It provides methods to get information about the type, category and name of the event. The ToString method returns the name of the event as default implementation but subclasses may override it with more meaningful representation.
 */
class AGE_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		/**
 * @brief Returns a string representation of the object.
 *
 * This function returns a string that represents the current object's state. It does this by calling the `GetName` method and returning its result.
 *
 * @return A string representing the current object's name.
 */
/**
 * @brief Converts the object into a string representation.
 *
 * This function returns a string that represents the current object's name. It uses the `GetName` method to get the name of the object.
 *
 * @return A string representing the current object's name.
 */
virtual std::string ToString() const { return GetName(); }

		/**
 * @brief Checks if an event is in a specific category.
 *
 * This function checks whether the provided EventCategory is set within the categories that are currently active.
 * The comparison is done by bitwise AND operation with GetCategoryFlags() and Category.
 * 
 * @param Category - The category to check against.
 * @return True if the event is in the specified category, false otherwise.
 */
/**
 * @brief Checks if an event is in a specific category.
 *
 * This function checks whether the given EventCategory (bitmask) is set within the result of GetCategoryFlags().
 * It uses bitwise AND operation to compare the Category flag with all flags.
 * 
 * @param Category The category to check against.
 * @return True if the event is in the specified category, false otherwise.
 */
inline bool IsInCategory(EventCategory Category)
		{
			return GetCategoryFlags() & Category; // Check Category flag against all flags
		}

	public:
		bool Handled = false;
	};

	class EventDispatcher
	{
		template <typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		/**
 * @brief Constructor for the EventDispatcher class.
 * @param Event The event to be dispatched.
 */
/**
 * @brief Constructs an instance of the EventDispatcher class with a reference to an event object.
 * @param Event The event object that this dispatcher will handle.
 */
EventDispatcher(Event& Event)
			: m_Event(Event) {}


		template<typename T>
		/**
 * @brief Dispatches an event of type T to the provided function if its type matches the static type of T.
 * 
 * This function takes a function object (or lambda) that accepts an argument of type T and returns void. It checks if the event's type is equal to the static type of T, then it calls the function with the event casted to type T. The function sets the 'Handled' member variable of the event to true if the event was handled by the provided function.
 * 
 * @param func A function object (or lambda) that accepts an argument of type T and returns void.
 * @return True if the event was dispatched, false otherwise.
 */
/**
 * @brief Dispatches an event of type T to the provided function if its type matches the static type of T.
 * 
 * This function takes a function object (func) as input and checks if the event's type is equal to the static type of T. If it is, the function object is invoked with the event casted to type T. The result of this operation is stored in the 'Handled' member of the event.
 * 
 * @param func Function object (event handler) that will be called if the event matches the static type of T.
 * @return True if the event was dispatched, false otherwise.
 */
bool Dispatch (EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	

	/**
 * @brief Overloads the << operator to print an event in a human-readable format.
 *
 * This function overloads the << operator so that it can be used with std::ostream objects 
 * and Event objects, printing out the details of the event in a readable format.
 *
 * @param OS The output stream to write to.
 * @param E The event object to print.
 * @return A reference to the modified output stream.
 */
/**
 * @brief Overloads the << operator to print an event object in a human-readable format.
 *
 * This function overloads the << operator so that it can be used with an output stream and an Event object. 
 * It prints out the details of the event, such as its type and time stamp.
 *
 * @param OS The output stream to print to.
 * @param E The event object to print.
 * @return A reference to the modified output stream.
 */
inline std::ostream& operator<<(std::ostream& OS, const Event& E)
	{
		return OS << E.ToString();
	}




}

