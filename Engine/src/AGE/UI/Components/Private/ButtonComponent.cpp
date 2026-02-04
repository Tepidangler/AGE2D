//
// Created by gdmgp on 2/1/2026.
//

#include "../Public/ButtonComponent.h"
#include "Events/Public/KeyEvent.h"
#include "Core/Public/App.h"

RTTR_REGISTRATION{
	rttr::registration::class_<AGE::ButtonComponent>("ButtonComponent")
	.constructor<const std::string&>()
	.method("OnUpdate", &AGE::ButtonComponent::OnUpdate)
	.property("BoxProperties", &AGE::ButtonComponent::m_BoxProperties)(rttr::metadata("Description", "Properties related to box surrounding the text"));
}

namespace AGE
{
	ButtonComponent::ButtonComponent(const std::string& Name)
	{
		m_Name = Name;
		m_Type = UIComponentType::ButtonComponent;
		m_OnClick =[]() {
			CoreLogger::Info("Button Clicked!");
		};
	}

	void ButtonComponent::DrawContent() {
		ImGui::Text("Box Properties");
		DrawVec3Control("Screen Position", m_BoxProperties.Position);
		DrawVec3Control("Screen Rotation", m_BoxProperties.Rotation);
		DrawVec3Control("Screen Scale", m_BoxProperties.Scale);
		ImGui::ColorEdit4("Box Color", &m_BoxProperties.TintColor.x);
	}

	void ButtonComponent::OnUpdate(TimeStep DeltaTime) {
		UIComponent::OnUpdate(DeltaTime);

		if (m_CompProperties.Visible)
		{
			QuadProperties QuadProps;
			QuadProps.Transform = Math::MakeTransform(m_BoxProperties.Position,m_BoxProperties.Rotation,m_BoxProperties.Scale);
			QuadProps.Color = m_BoxProperties.TintColor;
			Renderer2D::DrawQuad(QuadProps);
		}
	}

	void ButtonComponent::OnEvent(Event &Event)
	{
		AGE::EventDispatcher Dispatcher(Event);

		if (m_CompProperties.Focused)
		{
			Dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(ButtonComponent::OnKeyPressed));
		}
		if (IsButtonHovered()) {
		Dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(ButtonComponent::OnClicked));
		}
	}

	bool ButtonComponent::IsButtonHovered()
	{
		Vector2 MousePos = App::Get().GetDeviceManager().GetWindow().GetMousePos();
		Vector2 FramebufferSize = App::Get().GetFramebufferSize();
		Vector2 NormalizedMousePos = (MousePos / FramebufferSize) * 2.f  - 1.f;
		NormalizedMousePos.y *= -1.f;
		return NormalizedMousePos.x > (m_Bounds[0].x - m_Bounds[1].x * .5f) && NormalizedMousePos.x < (m_Bounds[0].x + m_Bounds[1].x * .5f)
		&& NormalizedMousePos.y > (m_Bounds[0].y - m_Bounds[1].y * .5f) && NormalizedMousePos.y < (m_Bounds[0].y + m_Bounds[1].y * .5f);
	}

	bool ButtonComponent::OnKeyPressed(KeyPressedEvent &E)
	{
		if (!m_CompProperties.Focused) {
			return false;
		}
		switch (E.GetKeyCode())
		{
			case Key::ENTER: { // This in theory should be whatever key is 'ACCEPT' or 'CONFIRM'
				m_OnClick();
				return false;
			}
			default:
				return false;
		}
		return false;
	}

	bool ButtonComponent::OnClicked(MouseButtonPressedEvent &E)
	{
		m_OnClick();
		return false;
	}
} // AGE