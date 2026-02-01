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
		WidgetConstructedEvent(const Ref<ScriptableWidget> UIWidget, uint8_t Stack)
			:m_Stack(Stack), m_ScriptableWidget(UIWidget) {}

		uint8_t GetStack() const { return m_Stack; }
		Ref<ScriptableWidget> GetWidget() const { return m_ScriptableWidget; }

		EVENT_CLASS_TYPE(WidgetConstructed)
		EVENT_CLASS_CATEGORY(EventCategoryUI)
	private:
		Ref<ScriptableWidget> m_ScriptableWidget;
		uint8_t m_Stack;
	};

	class WidgetActivatedEvent : public Event
	{
	public:
		WidgetActivatedEvent(const Ref<ScriptableWidget> UIWidget, uint8_t Stack)
			:m_Stack(Stack), m_ScriptableWidget(UIWidget) {}

		uint8_t GetStack() const { return m_Stack; }
		Ref<ScriptableWidget> GetWidget() const { return m_ScriptableWidget; }

		EVENT_CLASS_TYPE(WidgetActivated)
		EVENT_CLASS_CATEGORY(EventCategoryUI)
	private:
		Ref<ScriptableWidget> m_ScriptableWidget;
		uint8_t m_Stack;
	};

	class WidgetDeactivatedEvent : public Event
	{
	public:
		WidgetDeactivatedEvent(const Ref<ScriptableWidget> UIWidget, uint8_t Stack)
			:m_Stack(Stack), m_ScriptableWidget(UIWidget) {}

		uint8_t GetStack() const { return m_Stack; }
		Ref<ScriptableWidget> GetWidget() const { return m_ScriptableWidget; }

		EVENT_CLASS_TYPE(WidgetDeactivated)
		EVENT_CLASS_CATEGORY(EventCategoryUI)
	private:
		Ref<ScriptableWidget> m_ScriptableWidget;
		uint8_t m_Stack;
	};

}
#endif //AGE2D_UIEVENT_H
