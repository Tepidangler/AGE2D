//
// Created by gdmgp on 2/1/2026.
//

#ifndef AGE2D_BUTTONCOMPONENT_H
#define AGE2D_BUTTONCOMPONENT_H
#pragma once
#include "Events/Public/KeyEvent.h"

#include "UI/Public/UiComponent.h"

namespace AGE
{
	class ButtonComponent : public UIComponent
	{
	public:
		ButtonComponent();

		void OnEvent(Event& Event) override;

	private:
		bool OnKeyPressed(KeyPressedEvent& E);
		bool OnClicked(MouseButtonPressedEvent& E);
	};
} // AGE

#endif //AGE2D_BUTTONCOMPONENT_H