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
		for (auto& B : m_AxisBindings)
		{
			if (std::abs(B->AxisValue) == 1.f)
			{
				if (!bBlockInput)
				{
					B->Execute();
				}
			}
		}
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

		switch(E.GetAxis())
		{
		case AGE::JoyStick::GamePadAxisLeftX:
		{
			for (auto& B : m_AxisBindings)
			{
				if (std::abs(E.GetPosition()) < .002f)
				{
					break;
				}

				if (B->AxisName == FindCorrespondingAxisName(ProjectAxisBindings, AGE::JoyStick::GamePadAxisLeftX) && !bBlockInput)
				{
					B->AxisValue = E.GetPosition();
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::JoyStick::GamePadAxisLeftY:
		{
			for (auto& B : m_AxisBindings)
			{
				if (std::abs(E.GetPosition()) < .002f)
				{
					break;
				}

				if (B->AxisName == FindCorrespondingAxisName(ProjectAxisBindings, AGE::JoyStick::GamePadAxisLeftY) && !bBlockInput) // This should check if whatever name is linked to the LeftY Axis as a button is the axis name here and it should be like this for everything else
				{
					B->AxisValue = E.GetPosition();
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::JoyStick::GamePadAxisRightX:
		{
			for (auto& B : m_AxisBindings)
			{
				if (std::abs(E.GetPosition()) < .002f)
				{
					break;
				}

				if (B->AxisName == FindCorrespondingAxisName(ProjectAxisBindings, AGE::JoyStick::GamePadAxisRightX) && !bBlockInput)
				{
					B->AxisValue = E.GetPosition();
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::JoyStick::GamePadAxisRightY:
		{
			for (auto& B : m_AxisBindings)
			{
				if (std::abs(E.GetPosition()) < .002f)
				{
					break;
				}

				if (B->AxisName == FindCorrespondingAxisName(ProjectAxisBindings, AGE::JoyStick::GamePadAxisRightY) && !bBlockInput)
				{
					B->AxisValue = E.GetPosition();
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::JoyStick::GamePadAxisLeftTrigger:
		{
			for (auto& B : m_AxisBindings)
			{
				if (std::abs(E.GetPosition()) < .002f)
				{
					break;
				}

				if (B->AxisName == FindCorrespondingAxisName(ProjectAxisBindings, AGE::JoyStick::GamePadAxisLeftTrigger) && !bBlockInput)
				{
					B->AxisValue = E.GetPosition();
					B->Execute();
					break;
				}
			}

			break;
		}
		case AGE::JoyStick::GamePadAxisRightTrigger:
		{
			for (auto& B : m_AxisBindings)
			{
				if (std::abs(E.GetPosition()) < .002f)
				{
					break;
				}

				if (B->AxisName == FindCorrespondingAxisName(ProjectAxisBindings, AGE::JoyStick::GamePadAxisRightTrigger) && !bBlockInput)
				{
					B->AxisValue = E.GetPosition();
					B->Execute();
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

	bool InputComponent::OnButtonPressed(AGE::GamepadButtonPressedEvent& E)
	{
		//What will have to happen with this and the button calls

		auto& ProjectActionBindings = AGE::Project::GetActive()->GetInfo().ActionBindings;

		switch (E.GetButton())
		{
		case AGE::GamePad::GamePadButtonA:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->Status == KeyStatus::Pressed)
				{
					B->Status = KeyStatus::Pressed;
					break;
				}

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonA) && !bBlockInput)
				{
					B->Status = KeyStatus::Pressed;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonB:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->Status == KeyStatus::Pressed)
				{
					B->Status = KeyStatus::Pressed;
					break;
				}

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonB) && !bBlockInput) // This should check if whatever name is linked to the LeftY Axis as a button is the axis name here and it should be like this for everything else
				{
					B->Status = KeyStatus::Pressed;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonX:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->Status == KeyStatus::Pressed)
				{
					B->Status = KeyStatus::Pressed;
					break;
				}

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonX) && !bBlockInput)
				{
					B->Status = KeyStatus::Pressed;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonY:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->Status == KeyStatus::Pressed)
				{
					B->Status = KeyStatus::Pressed;
					break;
				}

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonY) && !bBlockInput)
				{
					B->Status = KeyStatus::Pressed;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonLB:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->Status == KeyStatus::Pressed)
				{
					B->Status = KeyStatus::Pressed;
					break;
				}

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonLB) && !bBlockInput)
				{
					B->Status = KeyStatus::Pressed;
					B->Execute();
					break;
				}
			}

			break;
		}
		case AGE::GamePad::GamePadButtonRB:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->Status == KeyStatus::Pressed)
				{
					B->Status = KeyStatus::Pressed;
					break;
				}

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonRB) && !bBlockInput)
				{
					B->Status = KeyStatus::Pressed;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonBack:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->Status == KeyStatus::Pressed)
				{
					B->Status = KeyStatus::Pressed;
					break;
				}

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonBack) && !bBlockInput)
				{
					B->Status = KeyStatus::Pressed;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonStart:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->Status == KeyStatus::Pressed)
				{
					B->Status = KeyStatus::Pressed;
					break;
				}

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonStart) && !bBlockInput)
				{
					B->Status = KeyStatus::Pressed;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonGUIDE:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->Status == KeyStatus::Pressed)
				{
					B->Status = KeyStatus::Pressed;
					break;
				}

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonGUIDE) && !bBlockInput)
				{
					B->Status = KeyStatus::Pressed;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonLeftThumb:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->Status == KeyStatus::Pressed)
				{
					B->Status = KeyStatus::Pressed;
					break;
				}

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonLeftThumb) && !bBlockInput)
				{
					B->Status = KeyStatus::Pressed;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonRightThumb:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->Status == KeyStatus::Pressed)
				{
					B->Status = KeyStatus::Pressed;
					break;
				}

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonRightThumb) && !bBlockInput)
				{
					B->Status = KeyStatus::Pressed;
					B->Execute();
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

	bool InputComponent::OnButtonReleased(AGE::GamepadButtonReleasedEvent& E)
	{
		//What will have to happen with this and the button calls

		auto& ProjectActionBindings = AGE::Project::GetActive()->GetInfo().ActionBindings;

		switch (E.GetButton())
		{
		case AGE::GamePad::GamePadButtonA:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonA) && !bBlockInput)
				{
					B->Status = KeyStatus::Released;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonB:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonB) && !bBlockInput) // This should check if whatever name is linked to the LeftY Axis as a button is the axis name here and it should be like this for everything else
				{
					B->Status = KeyStatus::Released;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonX:
		{
			for (auto& B : m_ActionBindings)
			{
				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonX) && !bBlockInput)
				{
					B->Status = KeyStatus::Released;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonY:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonY) && !bBlockInput)
				{
					B->Status = KeyStatus::Released;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonLB:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonLB) && !bBlockInput)
				{
					B->Status = KeyStatus::Released;
					B->Execute();
					break;
				}
			}

			break;
		}
		case AGE::GamePad::GamePadButtonRB:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonRB) && !bBlockInput)
				{
					B->Status = KeyStatus::Released;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonBack:
		{
			for (auto& B : m_ActionBindings)
			{


				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonBack) && !bBlockInput)
				{
					B->Status = KeyStatus::Released;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonStart:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonStart) && !bBlockInput)
				{
					B->Status = KeyStatus::Released;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonGUIDE:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonGUIDE) && !bBlockInput)
				{
					B->Status = KeyStatus::Released;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonLeftThumb:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonLeftThumb) && !bBlockInput)
				{
					B->Status = KeyStatus::Released;
					B->Execute();
					break;
				}
			}
			break;
		}
		case AGE::GamePad::GamePadButtonRightThumb:
		{
			for (auto& B : m_ActionBindings)
			{

				if (B->Name == FindCorrespondingActionName(ProjectActionBindings, AGE::GamePad::GamePadButtonRightThumb) && !bBlockInput)
				{
					B->Status = KeyStatus::Released;
					B->Execute();
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

}