//
// Created by gdmgp on 12/30/2025.
//

#ifndef AGE2D_UIEVENT_H
#define AGE2D_UIEVENT_H
#include "Events/Public/Event.h"

namespace AGE
{
	class WidgetConstructedEvent : public Event
	{
	public:
		/**
 * @brief Constructs a new instance of WidgetConstructedEvent.
 * 
 * This constructor initializes the event with a reference to the ScriptableWidget that was constructed, and the stack depth at which it was created.
 * 
 * @param UIWidget A const reference to the ScriptableWidget that was constructed.
 * @param Stack The stack depth at which the widget was constructed.
 */
/**
 * @brief Constructs a new instance of WidgetConstructedEvent.
 * This event is triggered when a widget has been constructed with the given UIWidget and Stack values.
 * @param UIWidget A reference to the ScriptableWidget that was constructed.
 * @param Stack The stack value associated with this event.
 */
WidgetConstructedEvent(const Ref<ScriptableWidget> UIWidget, uint8_t Stack)
			:m_Stack(Stack), m_ScriptableWidget(UIWidget) {}

		/**
 * @brief This function returns the current value of the stack variable.
 * @return uint8_t Returns the current value of the stack variable as a uint8_t type.
 */
/**
 * @brief This function returns the current value of the member variable 'm_Stack'.
 * @return uint8_t Returns the current value of 'm_Stack' as a uint8_t.
 */
uint8_t GetStack() const { return m_Stack; }
		/**
 * @brief Returns the ScriptableWidget object associated with this instance.
 * @return A reference to the ScriptableWidget object. If no such object exists, returns an empty Ref<ScriptableWidget>.
 */
/**
 * @brief Returns the ScriptableWidget object associated with this instance.
 * @return A reference to the ScriptableWidget object. If no such object exists, an empty reference is returned.
 */
Ref<ScriptableWidget> GetWidget() const { return m_ScriptableWidget; }

		EVENT_CLASS_TYPE(WidgetConstructed)
		EVENT_CLASS_CATEGORY(EventCategoryUI)
	private:
		uint8_t m_Stack;
		Ref<ScriptableWidget> m_ScriptableWidget;
	};

	class WidgetActivatedEvent : public Event
	{
	public:
		/**
 * @brief Constructs a new instance of WidgetActivatedEvent.
 * @param UIWidget A reference to the ScriptableWidget that triggered this event.
 * @param Stack The stack depth at which the widget was activated.
 * @return An instance of WidgetActivatedEvent with the provided parameters.
 */
/**
 * @brief Constructs a new instance of WidgetActivatedEvent.
 * 
 * This constructor initializes the object with a reference to a ScriptableWidget and a stack index.
 * The ScriptableWidget is used for interacting with the UI, while the stack index is used to track which widget in the stack this event corresponds to.
 * @param UIWidget A reference to the ScriptableWidget that this event pertains to.
 * @param Stack The index of the widget in the stack that this event corresponds to.
 */
WidgetActivatedEvent(const Ref<ScriptableWidget> UIWidget, uint8_t Stack)
			:m_Stack(Stack), m_ScriptableWidget(UIWidget) {}

		/**
 * @brief This function returns the current value of the stack variable.
 * @return The current value of the stack as a uint8_t.
 */
/**
 * @brief This function returns the value of member variable 'm_Stack'.
 * @return uint8_t Returns the current value of 'm_Stack' as a uint8_t.
 */
uint8_t GetStack() const { return m_Stack; }
		/**
 * @brief Returns the ScriptableWidget instance associated with this object.
 * @return A reference to the ScriptableWidget instance. If no such instance exists, a default-constructed one is returned.
 */
/**
 * @brief Returns the ScriptableWidget object associated with this instance.
 * @return A reference to the ScriptableWidget object. If no such object exists, an empty Ref<ScriptableWidget> is returned.
 */
Ref<ScriptableWidget> GetWidget() const { return m_ScriptableWidget; }

		EVENT_CLASS_TYPE(WidgetActivated)
		EVENT_CLASS_CATEGORY(EventCategoryUI)
	private:
		uint8_t m_Stack;
		Ref<ScriptableWidget> m_ScriptableWidget;
	};

	class WidgetDeactivatedEvent : public Event
	{
	public:
		/**
 * @brief Constructs a new instance of WidgetDeactivatedEvent.
 * 
 * This constructor initializes the object with the given parameters. It sets the stack level and the scriptable widget reference.
 * 
 * @param UIWidget A reference to the ScriptableWidget that is deactivating.
 * @param Stack The stack level of the deactivated widget.
 */
/**
 * @brief Constructs a new instance of Widget Deactivated Event.
 * 
 * This constructor initializes the event with a reference to the Scriptable Widget and the stack number.
 * 
 * @param UIWidget A const reference to the Scriptable Widget that is deactivating.
 * @param Stack The stack number of the widget being deactivated.
 */
WidgetDeactivatedEvent(const Ref<ScriptableWidget> UIWidget, uint8_t Stack)
			:m_Stack(Stack), m_ScriptableWidget(UIWidget) {}

		/**
 * @brief This function returns the current value of the stack variable.
 * @return uint8_t Returns the current value of the stack variable as a uint8_t type.
 */
/**
 * @brief This function returns the current value of the stack variable.
 * @return uint8_t The current value of the stack variable.
 */
uint8_t GetStack() const { return m_Stack; }
		/**
 * @brief Returns the ScriptableWidget object associated with this instance.
 * @return A reference to the ScriptableWidget object. If no such object exists, returns an empty Ref<ScriptableWidget>.
 */
/**
 * @brief Returns the ScriptableWidget object associated with this instance.
 * @return A reference to the ScriptableWidget object. If no such object exists, an empty Ref will be returned.
 */
Ref<ScriptableWidget> GetWidget() const { return m_ScriptableWidget; }

		EVENT_CLASS_TYPE(WidgetDeactivated)
		EVENT_CLASS_CATEGORY(EventCategoryUI)
	private:
		uint8_t m_Stack;
		Ref<ScriptableWidget> m_ScriptableWidget;
	};

}
#endif //AGE2D_UIEVENT_H
