//
// Created by gdmgp on 2/1/2026.
//

#include "../Public/ButtonComponent.h"

#include "Events/Public/KeyEvent.h"

namespace AGE
{
	ButtonComponent::ButtonComponent()
	{
	}

	void ButtonComponent::OnEvent(Event &Event)
	{
		AGE::EventDispatcher Dispatcher(Event);

		if (m_CompProperties.Focused)
		{
			Dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(ButtonComponent::OnKeyPressed));
		}
		Dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(ButtonComponent::OnClicked));
	}

	bool ButtonComponent::OnKeyPressed(KeyPressedEvent &E)
	{
		return false;
	}

	bool ButtonComponent::OnClicked(MouseButtonPressedEvent &E)
	{
		return false;
	}
} // AGE