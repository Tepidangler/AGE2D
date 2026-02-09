//
// Created by gdmgp on 12/3/2025.
//

#pragma once
#ifndef AGE2D_WIDGETSTACK_H
#define AGE2D_WIDGETSTACK_H
#include "UI/Public/ScriptableWidget.h"
#include "Core/Public/Core.h"
#include "Core/Public/DeltaTime.h"

namespace AGE
{
	class WidgetStack
	{
	public:
		WidgetStack() = default;
		~WidgetStack() = default;

		void PushWidgetToStack(Ref<ScriptableWidget> Widget);
		void PopWidgetFromStack();

		Ref<ScriptableWidget> GetActiveWidget() {return m_Widgets.front();}

		void OnTopUpdate(TimeStep DeltaTime);

		void ActivateWidget();
		void DeactivateWidget();

		std::deque<Ref<ScriptableWidget>>::iterator begin() {return m_Widgets.begin();}
		std::deque<Ref<ScriptableWidget>>::iterator end() {return m_Widgets.end();}
		std::deque<Ref<ScriptableWidget>>::const_iterator begin() const {return m_Widgets.cbegin();}
		std::deque<Ref<ScriptableWidget>>::const_iterator end() const {return m_Widgets.cend();}


	private:
		std::deque<Ref<ScriptableWidget>> m_Widgets;
		Entity m_Entity;
	};
} // AGE

#endif //AGE2D_WIDGETSTACK_H