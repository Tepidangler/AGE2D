//
// Created by gdmgp on 12/3/2025.
//

#pragma once
#ifndef AGE2D_WIDGETSTACK_H
#define AGE2D_WIDGETSTACK_H
#include "UI/Public/Widget.h"
#include "Core/Public/Core.h"

namespace AGE
{
	class WidgetStack
	{
	public:
		WidgetStack() = default;
		~WidgetStack() = default;

		void PushWidgetToStack(Ref<Widget> Widget);
		void PopWidgetFromStack(Ref<Widget> Widget);

		Ref<Widget> GetActiveWidget() {return m_Widgets.front();}

		void OnUpdate(TimeStep DeltaTime);

		std::deque<Ref<Widget>>::iterator begin() {return m_Widgets.begin();}
		std::deque<Ref<Widget>>::iterator end() {return m_Widgets.end();}
		std::deque<Ref<Widget>>::const_iterator begin() const {return m_Widgets.cbegin();}
		std::deque<Ref<Widget>>::const_iterator end() const {return m_Widgets.cend();}


	private:
		std::deque<Ref<Widget>> m_Widgets;
	};
} // AGE

#endif //AGE2D_WIDGETSTACK_H