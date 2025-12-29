//
// Created by gdmgp on 12/3/2025.
//

#include "AGEpch.hpp"
#include "../Public/WidgetStack.h"


namespace AGE
{
	void WidgetStack::PushWidgetToStack(Ref<Widget> Widget)
	{
		m_Widgets.emplace_front(Widget);
	}

	void WidgetStack::PopWidgetFromStack(Ref<Widget> Widget)
	{
		m_Widgets.pop_front();
	}

	void WidgetStack::OnUpdate(TimeStep DeltaTime)
	{
		if (m_Widgets.size() > 0)
		{
			m_Widgets.front()->OnUpdate(DeltaTime);
		}
	}
} // AGE