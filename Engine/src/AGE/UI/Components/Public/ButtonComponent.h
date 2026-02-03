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
		ButtonComponent(const std::string& Name);

		void DrawContent() override;
		void OnUpdate(TimeStep DeltaTime) override;
		void OnEvent(Event& Event) override;
		void CallSerialize(DataWriter* Serializer) override
		{
			//Serializer->WriteObject<VerticalBoxComponent>(*this);
		}
		void CallDeserialize(DataReader* Serializer) override
		{
			//Serializer->ReadObject<VerticalBoxComponent>(*this);
		}
		void SetOnClickFunc(const std::function<void()>& func) { m_OnClick = func; }

		RTTR_ENABLE(UIComponent)
		RTTR_REGISTRATION_FRIEND

	protected:
		bool IsButtonHovered();

	private:
		bool OnKeyPressed(KeyPressedEvent& E);
		bool OnClicked(MouseButtonPressedEvent& E);

		bool bIsPressed = false;
		bool bIsHovered = false;

		BoxProperties m_BoxProperties;
		Vector2 m_Bounds[2]; // [lx,ly] [rx,ry]

		std::function<void()> m_OnClick;

	};
} // AGE

#endif //AGE2D_BUTTONCOMPONENT_H