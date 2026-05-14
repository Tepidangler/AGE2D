//
// Created by gdmgp on 2/1/2026.
//

#include "UI/Components/Public/ButtonComponent.h"
#include "Events/Public/KeyEvent.h"
#include "Core/Public/App.h"
#include "Render/Public/Renderer2D.h"
#include "Core/Public/Keycodes.h"

RTTR_REGISTRATION{
	rttr::registration::class_<AGE::ButtonComponent>("ButtonComponent")
	.constructor<const std::string&>()
	.method("OnUpdate", &AGE::ButtonComponent::OnUpdate)
	.property("BoxProperties", &AGE::ButtonComponent::m_BoxProperties)(rttr::metadata("Description", "Properties related to box surrounding the text"));
}

namespace AGE
{
	/**
 * @brief Constructs a ButtonComponent with the given name.
 * 
 * This function initializes a new instance of the ButtonComponent class, setting its name and type. It also sets up an anonymous lambda function as the onClick event handler that logs "Button Clicked!" to the console when invoked.
 * @param Name The name for this button component.
 */
/**
 * @brief Constructs a ButtonComponent with the given name.
 * 
 * This function initializes a new instance of the ButtonComponent class, setting its name and type. It also sets up an anonymous lambda function as the onClick event handler that logs "Button Clicked!" to the console when triggered.
 * @param Name The name for the button component.
 */
ButtonComponent::ButtonComponent(const std::string& Name)
	{
		m_Name = Name;
		m_Type = UIComponentType::ButtonComponent;
		m_OnClick =[]() {
			CoreLogger::Info("Button Clicked!");
		};
	}

	/**
 * @brief Draws the content of the ButtonComponent, including properties like position, rotation, scale and color.
 * 
 * This function uses ImGui to draw a series of controls for modifying the BoxProperties of the ButtonComponent. It includes fields for Screen Position, Screen Rotation, Screen Scale and Box Color. The @ref DrawVec3Control is used to handle Vector3 properties.
 * 
 * @return void
 */
/**
 * @brief Draws the content of the ButtonComponent, including box properties like position, rotation, scale and color.
 * 
 * This function uses ImGui to draw text fields for each property, a vector control for editing position, rotation and scale vectors,
 * and a color edit control for setting the tint color of the box. The @c DrawVec3Control function is used to handle the drawing
 * and input of these properties.
 * 
 * @return void
 */
void ButtonComponent::DrawContent() {
		ImGui::Text("Box Properties");
		DrawVec3Control("Screen Position", m_BoxProperties.Position);
		DrawVec3Control("Screen Rotation", m_BoxProperties.Rotation);
		DrawVec3Control("Screen Scale", m_BoxProperties.Scale);
		ImGui::ColorEdit4("Box Color", &m_BoxProperties.TintColor.x);
	}

	/**
 * @brief Updates the ButtonComponent based on the provided TimeStep.
 *
 * This function updates the ButtonComponent by calling UIComponent's OnUpdate method with the given DeltaTime. 
 * If the component is visible, it creates a QuadProperties object and sets its properties accordingly before passing it to Renderer2D::DrawQuad for rendering.
 *
 * @param DeltaTime The time step since the last frame.
 */
/**
 * @brief Updates the button component based on the provided time step.
 *
 * This function updates the button component by calling the base class's OnUpdate() method, then checks if the component is visible. If it is, 
 * a QuadProperties object is created to hold properties for rendering a quad (like its transform, color etc.). The properties are set based on 
 * the button component's box properties and then used with Renderer2D::DrawQuad() to render the button.
 *
 * @param DeltaTime The time step since the last frame.
 */
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

	/**
 * @brief This function handles events related to the button component. It dispatches different types of events based on the current state of the button and the event that has occurred.
 * 
 * @param Event The event object which contains information about the event that has occurred.
 */
/**
 * @brief Handles events related to the button component.
 * 
 * This function processes various types of events such as key presses and mouse clicks, which are dispatched based on certain conditions (like if the button is focused or if it's being hovered over).
 * 
 * @param Event The event object that contains information about the event.
 */
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

	/**
 * @brief Checks if the button is hovered by the mouse cursor.
 *
 * This function calculates the normalized position of the mouse cursor relative to the window size, and then checks whether this position falls within the bounds defined by the button's dimensions. 
 * The bounds are calculated as half the width and height of the button, with the center point being at (m_Bounds[0].x, m_Bounds[0].y).
 *
 * @return True if the mouse cursor is hovering over the button, false otherwise.
 */
/**
 * @brief Checks if the button is hovered by the mouse cursor.
 * 
 * This function calculates the normalized position of the mouse cursor relative to the framebuffer size, then checks if this position lies within the bounds defined by `m_Bounds`. If it does, the function returns true; otherwise, it returns false.
 * 
 * @return A boolean value indicating whether or not the button is hovered by the mouse cursor.
 */
bool ButtonComponent::IsButtonHovered()
	{
		Vector2 MousePos = App::Get().GetDeviceManager().GetWindow().GetMousePos();
		Vector2 FramebufferSize = App::Get().GetFramebufferSize();
		Vector2 NormalizedMousePos = (MousePos / FramebufferSize) * 2.f  - 1.f;
		NormalizedMousePos.y *= -1.f;
		return NormalizedMousePos.x > (m_Bounds[0].x - m_Bounds[1].x * .5f) && NormalizedMousePos.x < (m_Bounds[0].x + m_Bounds[1].x * .5f)
		&& NormalizedMousePos.y > (m_Bounds[0].y - m_Bounds[1].y * .5f) && NormalizedMousePos.y < (m_Bounds[0].y + m_Bounds[1].y * .5f);
	}

	/**
 * @brief Handles key press events.
 * 
 * This function is responsible for handling the KeyPressedEvent, specifically when a certain key (currently ENTER) has been pressed. If the component is currently focused and the event's key code matches the 'ENTER', it triggers an action defined by m_OnClick().
 * 
 * @param E The KeyPressedEvent to be handled.
 * @return bool Returns false if no special actions were taken, true otherwise. In this case, we only return true when ENTER is pressed and m_OnClick() is triggered, so it's always false.
 */
/**
 * @brief Handles key press events for the ButtonComponent.
 * 
 * This function is responsible for handling key press events and determining if they should be processed or ignored. The component only processes key presses when it has focus, indicated by `m_CompProperties.Focused`. If a key other than ENTER (Key::ENTER) is pressed, the function returns false without doing anything else.
 * 
 * @param E A reference to the KeyPressedEvent that was triggered.
 * @return True if the event was processed and should not be passed on to other components; False otherwise. In this case, it will return true only when ENTER key is pressed (Key::ENTER).
 */
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

	/**
 * @brief Handles the click event of the button.
 *
 * This function is triggered when a mouse button is pressed on this component. It executes the callback function associated with the button.
 *
 * @param E A reference to the MouseButtonPressedEvent object containing information about the event.
 * @return Always returns false, as no further action needs to be taken after clicking the button.
 */
/**
 * @brief Handles the OnClicked event.
 *
 * This function is triggered when a mouse button is pressed on this ButtonComponent. 
 * It executes the stored callback function, m_OnClick(), and returns false.
 *
 * @param E A reference to the MouseButtonPressedEvent that was fired.
 * @return Always returns false.
 */
bool ButtonComponent::OnClicked(MouseButtonPressedEvent &E)
	{
		m_OnClick();
		return false;
	}
} // AGE