//
// Created by gdmgp on 12/3/2025.
//

#include "AGEpch.hpp"
#include "../Public/WidgetStack.h"


namespace AGE
{
	void WidgetStack::PushWidgetToStack(Ref<ScriptableWidget> Widget)
	{
		m_Widgets.emplace_front(Widget);
	}

	void WidgetStack::PopWidgetFromStack(Ref<ScriptableWidget> Widget)
	{
		m_Widgets.pop_front();
	}

	void WidgetStack::OnTopUpdate(TimeStep DeltaTime)
	{
		if (m_Widgets.size() > 0)
		{
			m_Widgets.front()->OnUpdate(DeltaTime);
		}
	}
} // AGE