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

	class AGE_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

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
		EventDispatcher(Event& Event)
			: m_Event(Event) {}


		template<typename T>
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

	

	inline std::ostream& operator<<(std::ostream& OS, const Event& E)
	{
		return OS << E.ToString();
	}




}

