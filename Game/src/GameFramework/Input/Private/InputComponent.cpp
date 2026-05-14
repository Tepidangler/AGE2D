#include <Core/Public/AGEpch.hpp>
#include <Age.h>
#include "Input/Public/InputComponent.h"


namespace GameFramework
{
	void InputComponent::OnCreate()
	{

	}
	void InputComponent::OnUpdate(AGE::TimeStep DeltaTime)
	{

		std::ranges::for_each(m_AxisBindings.begin(), m_AxisBindings.end(), [&](const auto& Binding)
		{
			if (std::abs(Binding->GetAxisValue()) == 1.f) // Consider changing this to check for a value greater than that of the Deadzone
			{
				if (!bBlockInput)
				{
					Binding->AxisExecute();
				}
			}
		});
	}
	void InputComponent::OnEvent(AGE::Event& E)
	{
		AGE::EventDispatcher Dispatcher(E);

		Dispatcher.Dispatch<AGE::AxisEvent>(BIND_EVENT_FN(GameFramework::InputComponent::OnAxisMoved));
		Dispatcher.Dispatch<AGE::GamepadButtonPressedEvent>(BIND_EVENT_FN(GameFramework::InputComponent::OnButtonPressed));
		Dispatcher.Dispatch<AGE::GamepadButtonReleasedEvent>(BIND_EVENT_FN(GameFramework::InputComponent::OnButtonReleased));

	}

	bool InputComponent::OnAxisMoved(AGE::AxisEvent& E)
	{
		//What will have to happen with this and the button calls

		auto& ProjectAxisBindings = AGE::Project::GetActive()->GetInfo().AxisBindings;

		if (std::abs(E.GetPosition()) < .002f)
		{
			return true;
		}

		if (auto it = std::ranges::find(ProjectAxisBindings,E.GetName(), &AGE::InputBinding::m_BindingName); it !=ProjectAxisBindings.end() && !bBlockInput)
		{
			it->get()->SetAxisValue(E.GetPosition());
			it->get()->AxisExecute();
		}
		return true;
#if  0
		switch(E.GetAxis())
		{
			case AGE::GamePad::Axes::GamePadAxisLeftX:
		{
			if (std::abs(E.GetPosition()) < .002f)
			{
				break;
			}

			if (auto it = std::ranges::find(ProjectAxisBindings,E.GetName(), &AGE::InputBinding::m_BindingName); it !=ProjectAxisBindings.end() && !bBlockInput)
			{
				it->get()->SetAxisValue(E.GetPosition());
				it->get()->AxisExecute();
				break;
			}

			break;
		}
		case AGE::GamePad::Axes::GamePadAxisLeftY:
		{
			for (auto& B : m_AxisBindings)
			{
				if (std::abs(E.GetPosition()) < .002f)
				{
					break;
				}

				if (B->GetName() == FindCorrespondingAxisName(ProjectAxisBindings, AGE::GamePad::Axes::GamePadAxisLeftY) && !bBlockInput) // This should check if whatever name is linked to the LeftY Axis as a button is the axis name here and it should be like this for everything else
				{
					B->SetAxisValue(E.GetPosition());
					B->AxisExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::Axes::GamePadAxisRightX:
		{
			for (auto& B : m_AxisBindings)
			{
				if (std::abs(E.GetPosition()) < .002f)
				{
					break;
				}

				if (B->GetName() == FindCorrespondingAxisName(ProjectAxisBindings, AGE::GamePad::Axes::GamePadAxisRightX) && !bBlockInput)
				{
					B->SetAxisValue(E.GetPosition());
					B->AxisExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::Axes::GamePadAxisRightY:
		{
			for (auto& B : m_AxisBindings)
			{
				if (std::abs(E.GetPosition()) < .002f)
				{
					break;
				}

				if (B->GetName() == FindCorrespondingAxisName(ProjectAxisBindings, AGE::GamePad::Axes::GamePadAxisRightY) && !bBlockInput)
				{
					B->SetAxisValue(E.GetPosition());
					B->AxisExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::Axes::GamePadAxisLeftTrigger:
		{
			for (auto& B : m_AxisBindings)
			{
				if (std::abs(E.GetPosition()) < .002f)
				{
					break;
				}

				if (B->GetName() == FindCorrespondingAxisName(ProjectAxisBindings, AGE::GamePad::Axes::GamePadAxisLeftTrigger) && !bBlockInput)
				{
					B->SetAxisValue(E.GetPosition());
					B->AxisExecute();
					break;
				}
			}

			break;
		}
		case AGE::GamePad::Axes::GamePadAxisRightTrigger:
		{
			for (auto& B : m_AxisBindings)
			{
				if (std::abs(E.GetPosition()) < .002f)
				{
					break;
				}

				if (B->GetName() == FindCorrespondingAxisName(ProjectAxisBindings, AGE::GamePad::Axes::GamePadAxisRightTrigger) && !bBlockInput)
				{
					B->SetAxisValue(E.GetPosition());
					B->AxisExecute();
					break;
				}
			}
			break;
		}
		default:
		{
			break;
		}
		}

		return true;
#endif
	}

	bool InputComponent::OnButtonPressed(AGE::GamepadButtonPressedEvent& E)
	{
		//What will have to happen with this and the button calls

		auto& ProjectActionBindings = AGE::Project::GetActive()->GetInfo().ActionBindings;

		std::ranges::for_each(ProjectActionBindings,[&](const auto& Binding) // Not entirely sure _why we're doing this....
		{
			if (Binding->m_State == AGE::KeyState::Pressed)
			{
				Binding->m_State = AGE::KeyState::Pressed;
			}
		});

		if (auto it = std::ranges::find(ProjectActionBindings,E.GetName(), &AGE::InputBinding::m_BindingName); it !=ProjectActionBindings.end() && !bBlockInput)
		{
			it->get()->m_State = AGE::KeyState::Pressed;
			it->get()->ActionExecute();
		}
		return true;
#if 0
		switch (E.GetButton())
		{
		case AGE::GamePad::GamePadButtonA:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->m_State == AGE::KeyState::Pressed)
				{
					B->m_State = AGE::KeyState::Pressed;
					break;
				}

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonA) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Pressed;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonB:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->m_State == AGE::KeyState::Pressed)
				{
					B->m_State = AGE::KeyState::Pressed;
					break;
				}

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonB) && !bBlockInput) // This should check if whatever name is linked to the LeftY Axis as a button is the axis name here and it should be like this for everything else
				{
					B->m_State = AGE::KeyState::Pressed;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonX:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->m_State == AGE::KeyState::Pressed)
				{
					B->m_State = AGE::KeyState::Pressed;
					break;
				}

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonX) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Pressed;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonY:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->m_State == AGE::KeyState::Pressed)
				{
					B->m_State = AGE::KeyState::Pressed;
					break;
				}

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonY) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Pressed;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonLB:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->m_State == AGE::KeyState::Pressed)
				{
					B->m_State = AGE::KeyState::Pressed;
					break;
				}

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonLB) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Pressed;
					B->ActionExecute();
					break;
				}
			}

			break;
		}
		case AGE::GamePad::GamePadButtonRB:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->m_State == AGE::KeyState::Pressed)
				{
					B->m_State = AGE::KeyState::Pressed;
					break;
				}

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonRB) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Pressed;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonBack:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->m_State == AGE::KeyState::Pressed)
				{
					B->m_State = AGE::KeyState::Pressed;
					break;
				}

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonBack) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Pressed;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonStart:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->m_State == AGE::KeyState::Pressed)
				{
					B->m_State = AGE::KeyState::Pressed;
					break;
				}

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonStart) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Pressed;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonGUIDE:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->m_State == AGE::KeyState::Pressed)
				{
					B->m_State = AGE::KeyState::Pressed;
					break;
				}

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonGUIDE) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Pressed;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonLeftThumb:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->m_State == AGE::KeyState::Pressed)
				{
					B->m_State = AGE::KeyState::Pressed;
					break;
				}

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonLeftThumb) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Pressed;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonRightThumb:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->m_State == AGE::KeyState::Pressed)
				{
					B->m_State = AGE::KeyState::Pressed;
					break;
				}

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonRightThumb) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Pressed;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		default:
		{
			break;
		}
		}

		return true;
#endif
	}

	bool InputComponent::OnButtonReleased(AGE::GamepadButtonReleasedEvent& E)
	{
		//What will have to happen with this and the button calls

		auto& ProjectActionBindings = AGE::Project::GetActive()->GetInfo().ActionBindings;

		if (auto it = std::ranges::find(ProjectActionBindings,E.GetName(), &AGE::InputBinding::m_BindingName); it !=ProjectActionBindings.end() && !bBlockInput)
		{
			it->get()->m_State = AGE::KeyState::Released;
			it->get()->ActionExecute();
		}
		return true;
	}
#if 0
		switch (E.GetButton())
		{
		case AGE::GamePad::GamePadButtonA:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonA) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Released;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonB:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonB) && !bBlockInput) // This should check if whatever name is linked to the LeftY Axis as a button is the axis name here and it should be like this for everything else
				{
					B->m_State = AGE::KeyState::Released;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonX:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonX) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Released;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonY:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonY) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Released;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonLB:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonLB) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Released;
					B->ActionExecute();
					break;
				}
			}

			break;
		}
		case AGE::GamePad::GamePadButtonRB:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonRB) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Released;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonBack:
		{
			for (auto& B : m_ActionBindings)
			{


				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonBack) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Released;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonStart:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonStart) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Released;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonGUIDE:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonGUIDE) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Released;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonLeftThumb:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonLeftThumb) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Released;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonRightThumb:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->GetName() == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonRightThumb) && !bBlockInput)
				{
					B->m_State = AGE::KeyState::Released;
					B->ActionExecute();
					break;
				}
			}
			break;
		}
		default:
		{
			break;
		}
		}

		return true;
	}

	std::string InputComponent::FindCorrespondingAxisName(std::vector<std::pair<std::string, std::vector<uint8_t>>>& AxisBindings, uint8_t Key)
	{
		for (auto& B : AxisBindings)
		{
			auto it = std::find(B.second.begin(), B.second.end(), Key);

			if (it != B.second.end())
			{
				return B.first;
			}
		}

		return std::string("NOT FOUND");
	}

	std::string InputComponent::FindCorrespondingActionName(std::vector<std::pair<std::string, std::vector<uint8_t>>>& ActionBindings, uint8_t Key)
	{
		for (auto& B : ActionBindings)
		{
			auto it = std::find(B.second.begin(), B.second.end(), Key);

			if (it != B.second.end())
			{
				return B.first;
			}
		}
		return std::string("NOT FOUND");
	}
#endif
}
