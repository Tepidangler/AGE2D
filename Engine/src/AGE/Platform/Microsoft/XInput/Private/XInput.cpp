#include "AGEpch.hpp"
#include "Platform/Microsoft/XInput/Public/XInput.h"
#include "Core/Public/GamepadCodes.h"
#include "Events/Public/GameEvent.h"
#include "Core/Public/JoyStickCodes.h"

namespace AGE
{
	XInput::XInput()
	{
		CoreLogger::Info("Registering Controllers...");
		RegisterControllers();

	}

	void XInput::RegisterControllers()
	{
		ulong_t Result;

		for (ulong_t i = 0; i < XUSER_MAX_COUNT; i++)
		{
			XINPUT_STATE State;
			XInputControllerInfo ControllerInfo;

				memset(&State, 0, sizeof(XINPUT_STATE));

			Result = XInputGetState(i, &State);

			if (Result == ERROR_SUCCESS)
			{

				ControllerInfo.PacketNumber = State.dwPacketNumber;
				ControllerInfo.UserIndex = i;
				ControllerInfo.bConnected = true;
				ControllerInfo.ButtonState = State.Gamepad.wButtons;

				XINPUT_BATTERY_INFORMATION BattInfo;
				memset(&BattInfo, 0, sizeof(XINPUT_BATTERY_INFORMATION));
				Result = XInputGetBatteryInformation(i, BATTERY_DEVTYPE_GAMEPAD, &BattInfo);
				if (Result == ERROR_SUCCESS)
				{
					ControllerInfo.BatteryType = BattInfo.BatteryType;
					ControllerInfo.BatteryLevel = BattInfo.BatteryLevel;
				}

				m_Controllers[i].first = State.Gamepad;
				m_Controllers[i].second = ControllerInfo;

				CoreLogger::Info("\t Controller in slot {} Sucessfully Registered!", i);
			}
		}
	}
	void XInput::ClampLeftThumbstickDeadZone(XINPUT_GAMEPAD& Gamepad, const XInputControllerInfo& Info)
	{
		float LX = Gamepad.sThumbLX;
		float LY = Gamepad.sThumbLY;

		float Magnitude = std::sqrtf(LX * LX + LY * LY);

		float NormalizedLX = LX / Magnitude;

		float NormalizedLY = LY / Magnitude;

		float NormalizedMagnitude = 0.f;

		if (Magnitude > Info.Settings.LeftThumbstickDeadzone)
		{
			if (Magnitude > 32767.f)
			{
				Magnitude = 32767.f;
			}

			Magnitude -= Info.Settings.LeftThumbstickDeadzone;

			NormalizedMagnitude = Magnitude / (32767.f - Info.Settings.LeftThumbstickDeadzone);
		}
		else
		{
			Magnitude = 0.f;
			NormalizedMagnitude = 0.f;
			return;
		}

		if (NormalizedLX != 0.f)
		{
			AxisEvent Event(JoyStick::GamePadAxisLeftX, NormalizedLX);
			Info.CallbackFn(Event);
		}

		if (NormalizedLY != 0.f)
		{
			AxisEvent Event(JoyStick::GamePadAxisLeftY, NormalizedLY);
			Info.CallbackFn(Event);
			
		}
	}

	void XInput::ClampRightThumbstickDeadZone(XINPUT_GAMEPAD& Gamepad, const XInputControllerInfo& Info)
	{
		float RX = Gamepad.sThumbRX;
		float RY = Gamepad.sThumbRY;

		float Magnitude = std::sqrtf(RX * RX + RY * RY);

		float NormalizedRX = RX / Magnitude;

		float NormalizedRY = RY / Magnitude;

		float NormalizedMagnitude = 0.f;

		if (Magnitude > Info.Settings.RightThumbstickDeadzone)
		{
			if (Magnitude > 32767.f)
			{
				Magnitude = 32767.f;
			}

			Magnitude -= Info.Settings.RightThumbstickDeadzone;

			NormalizedMagnitude = Magnitude / (32767.f - Info.Settings.RightThumbstickDeadzone);
		}
		else
		{
			Magnitude = 0.f;
			NormalizedMagnitude = 0.f;
			return;
		}

		if (NormalizedRX != 0.f)
		{
			AxisEvent Event(JoyStick::GamePadAxisRightX, NormalizedRX);
			Info.CallbackFn(Event);
		}

		if (NormalizedRY != 0.f)
		{
			AxisEvent Event(JoyStick::GamePadAxisRightY, NormalizedRX);
			Info.CallbackFn(Event);
		}
	}
	void XInput::ClampLeftTriggerDeadZone(XINPUT_GAMEPAD& Gamepad, const XInputControllerInfo& Info)
	{
		float LT = Gamepad.bLeftTrigger;
		float NormalizedLT = 0.f;
		if (LT > Info.Settings.LeftTriggerDeadzone)
		{
			if (LT > 255.f)
			{
				LT = 255.f;
			}

			LT -= Info.Settings.LeftTriggerDeadzone;

			NormalizedLT = LT / (255.f - Info.Settings.RightThumbstickDeadzone);
		}
		else
		{
			LT = 0.f;
			NormalizedLT = 0.f;
			return;
		}

		if (NormalizedLT != 0.f)
		{
			AxisEvent Event(JoyStick::GamePadAxisLeftTrigger, NormalizedLT);
			Info.CallbackFn(Event);
		}
	}
	void XInput::ClampRightTriggerDeadZone(XINPUT_GAMEPAD& Gamepad, const XInputControllerInfo& Info)
	{
		float RT = Gamepad.bRightTrigger;

		float NormalizedRT = 0.f;
		if (RT > Info.Settings.LeftTriggerDeadzone)
		{
			if (RT > 255.f)
			{
				RT = 255.f;
			}

			RT -= Info.Settings.RightTriggerDeadzone;

			NormalizedRT = RT / (255.f - Info.Settings.RightThumbstickDeadzone);
		}
		else
		{
			RT = 0.f;
			NormalizedRT = 0.f;
			return;
		}

		if (NormalizedRT != 0.f)
		{
			AxisEvent Event(JoyStick::GamePadAxisRightTrigger, NormalizedRT);
			Info.CallbackFn(Event);
		}
	}
	void XInput::CheckButtonInput(XINPUT_GAMEPAD& Gamepad, const XInputControllerInfo& Info)
	{
		bool IsSet = IsBitSet(Gamepad.wButtons, GamePad::XInputDpadUp);
		bool WasSet = IsBitSet(m_Controllers[Info.UserIndex].second.ButtonState, GamePad::XInputDpadUp);
		XINPUT_KEYSTROKE Keystroke;
		memset(&Keystroke, 0, sizeof(XINPUT_KEYSTROKE));
		XInputGetKeystroke(Info.UserIndex, 0, &Keystroke);

		
		switch (Keystroke.VirtualKey)
		{
		case VK_PAD_A:
		{
			if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
			{
				GamepadButtonPressedEvent Event(GamePad::GamePadButtonA);

				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(GamePad::GamePadButtonA);
				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_REPEAT)
			{

			}
			break;
		}
		case VK_PAD_B:
		{
			if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
			{
				GamepadButtonPressedEvent Event(GamePad::GamePadButtonB);

				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(GamePad::GamePadButtonB);
				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_REPEAT)
			{

			}
			break;
		}
		case VK_PAD_X:
		{
			if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
			{
				GamepadButtonPressedEvent Event(GamePad::GamePadButtonX);

				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(GamePad::GamePadButtonX);
				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_REPEAT)
			{

			}
			break;
		}
		case VK_PAD_Y:
		{
			if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
			{
				GamepadButtonPressedEvent Event(GamePad::GamePadButtonY);

				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(GamePad::GamePadButtonY);
				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_REPEAT)
			{

			}
			break;
		}
		case VK_PAD_RSHOULDER:
		{
			if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
			{
				GamepadButtonPressedEvent Event(GamePad::GamePadButtonRB);

				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(GamePad::GamePadButtonRB);
				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_REPEAT)
			{

			}
			break;
		}
		case VK_PAD_LSHOULDER:
		{
			if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
			{
				GamepadButtonPressedEvent Event(GamePad::GamePadButtonLB);

				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(GamePad::GamePadButtonLB);
				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_REPEAT)
			{

			}
			break;
		}
		case VK_PAD_LTRIGGER:
		{
			if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
			{
				GamepadButtonPressedEvent Event(JoyStick::GamePadAxisLeftTrigger);

				Info.CallbackFn(Event);
				
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(JoyStick::GamePadAxisLeftTrigger);
				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_REPEAT)
			{

			}
			break;
		}
		case VK_PAD_RTRIGGER:
		{
			if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
			{
				GamepadButtonPressedEvent Event(JoyStick::GamePadAxisRightTrigger);

				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(JoyStick::GamePadAxisRightTrigger);
				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_REPEAT)
			{

			}
			break;
		}
		case VK_PAD_DPAD_UP:
		{
			if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
			{
				GamepadButtonPressedEvent Event(GamePad::GamePadButtonDpadUp);

				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(GamePad::GamePadButtonDpadUp);
				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_REPEAT)
			{

			}
			break;
		}
		case VK_PAD_DPAD_DOWN:
		{
			if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
			{
				GamepadButtonPressedEvent Event(GamePad::GamePadButtonDpadDown);

				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(GamePad::GamePadButtonDpadDown);
				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_REPEAT)
			{

			}
			break;
		}
		case VK_PAD_DPAD_LEFT:
		{
			if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
			{
				GamepadButtonPressedEvent Event(GamePad::GamePadButtonDpadLeft);

				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(GamePad::GamePadButtonDpadLeft);
				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_REPEAT)
			{

			}
			break;
		}
		case VK_PAD_DPAD_RIGHT:
		{
			if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
			{
				GamepadButtonPressedEvent Event(GamePad::GamePadButtonDpadRight);

				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(GamePad::GamePadButtonDpadRight);
				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_REPEAT)
			{

			}
			break;
		}
		case VK_PAD_START:
		{
			if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
			{
				GamepadButtonPressedEvent Event(GamePad::GamePadButtonGUIDE);

				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(GamePad::GamePadButtonGUIDE);
				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_REPEAT)
			{

			}
			break;
		}
		case VK_PAD_BACK:
		{
			if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
			{
				GamepadButtonPressedEvent Event(GamePad::GamePadButtonBack);

				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(GamePad::GamePadButtonBack);
				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_REPEAT)
			{

			}
			break;
		}
		case VK_PAD_LTHUMB_PRESS:
		{
			if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
			{
				GamepadButtonPressedEvent Event(GamePad::GamePadButtonLeftThumb);

				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(GamePad::GamePadButtonLeftThumb);
				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_REPEAT)
			{

			}
			break;
		}
		case VK_PAD_RTHUMB_PRESS:
		{
			if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYDOWN)
			{
				GamepadButtonPressedEvent Event(GamePad::GamePadButtonRightThumb);

				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(GamePad::GamePadButtonRightThumb);
				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_REPEAT)
			{

			}
			break;
		}
		case VK_PAD_LTHUMB_UP:
		case VK_PAD_LTHUMB_DOWN:
		case VK_PAD_LTHUMB_RIGHT:
		case VK_PAD_LTHUMB_LEFT:
		case VK_PAD_LTHUMB_UPLEFT:
		case VK_PAD_LTHUMB_UPRIGHT:
		case VK_PAD_LTHUMB_DOWNLEFT:
		case VK_PAD_LTHUMB_DOWNRIGHT:
		{
			ClampLeftThumbstickDeadZone(Gamepad, Info);
			break;
		}
		case VK_PAD_RTHUMB_UP:
		case VK_PAD_RTHUMB_DOWN:
		case VK_PAD_RTHUMB_RIGHT:
		case VK_PAD_RTHUMB_LEFT:
		case VK_PAD_RTHUMB_UPLEFT:
		case VK_PAD_RTHUMB_UPRIGHT:
		case VK_PAD_RTHUMB_DOWNRIGHT:
		case VK_PAD_RTHUMB_DOWNLEFT:
		{
			ClampRightThumbstickDeadZone(Gamepad, Info);
			break;
		}
		default:
			break;
		}

	}
	bool XInput::IsBitSet(uint16_t Number, uint16_t Mask)
	{
		return (Number & Mask) != 0;
	}
	void XInput::RegisterSingleController(ulong_t Slot)
	{
		ulong_t Result;
		XINPUT_STATE State;
		XInputControllerInfo ControllerInfo;

		memset(&State, 0, sizeof(XINPUT_STATE));

		Result = XInputGetState(Slot, &State);

		if (Result == ERROR_SUCCESS)
		{
			ControllerInfo.PacketNumber = State.dwPacketNumber;
			ControllerInfo.UserIndex = Slot;
			ControllerInfo.bConnected = true;
			ControllerInfo.ButtonState = State.Gamepad.wButtons;
			m_Controllers[Slot].first = State.Gamepad;
			m_Controllers[Slot].second = ControllerInfo;

			XINPUT_BATTERY_INFORMATION BattInfo;
			memset(&BattInfo, 0, sizeof(XINPUT_BATTERY_INFORMATION));
			Result = XInputGetBatteryInformation(Slot, BATTERY_DEVTYPE_GAMEPAD, &BattInfo);
			if (Result == ERROR_SUCCESS)
			{
				ControllerInfo.BatteryType = BattInfo.BatteryType;
				ControllerInfo.BatteryLevel = BattInfo.BatteryLevel;
			}

			CoreLogger::Info("\t Controller in slot {} Sucessfully Registered!", Slot);
		}
	}
	std::pair<uint16_t, uint16_t> XInput::GetLRDeadzones(ulong_t Slot)
	{
		return std::pair<uint16_t, uint16_t>(m_Controllers[Slot].second.Settings.LeftThumbstickDeadzone, m_Controllers[Slot].second.Settings.RightThumbstickDeadzone);
	}
	uint16_t XInput::GetLeftThumbstickDeadzone(ulong_t Slot)
	{
		return GetLRDeadzones(Slot).first;
	}
	void XInput::SetLeftThumbstickDeadzone(ulong_t Slot, uint16_t Value)
	{
		m_Controllers[Slot].second.Settings.LeftThumbstickDeadzone = Value;

	}
	uint16_t XInput::GetRightThumbstickDeadzone(ulong_t Slot)
	{
		return GetLRDeadzones(Slot).second;
	}
	void XInput::SetRightThumbstickDeadzone(ulong_t Slot, uint16_t Value)
	{
		m_Controllers[Slot].second.Settings.RightThumbstickDeadzone = Value;
	}
	std::pair<uint16_t, uint16_t> XInput::GetTriggerThresholds(ulong_t Slot)
	{
		return std::pair<uint16_t, uint16_t>(m_Controllers[Slot].second.Settings.LeftTriggerDeadzone, m_Controllers[Slot].second.Settings.RightTriggerDeadzone);
	}
	uint16_t XInput::GetLeftTriggerThreshold(ulong_t Slot)
	{
		return GetTriggerThresholds(Slot).first;
	}
	void XInput::SetLeftTriggerThreshold(ulong_t Slot, uint16_t Value)
	{
		m_Controllers[Slot].second.Settings.LeftTriggerDeadzone = Value;
	}
	uint16_t XInput::GetRightTriggerThreshold(ulong_t Slot)
	{
		return GetTriggerThresholds(Slot).second;
	}
	void XInput::SetRightTriggerThreshold(ulong_t Slot, uint16_t Value)
	{
		m_Controllers[Slot].second.Settings.RightTriggerDeadzone = Value;
	}
	void XInput::SetLowFrequencyMotorSpeed(uint16_t Speed, ulong_t ControllerSlot)
	{
		m_Controllers[ControllerSlot].second.Settings.LowFreqMotorSpeed = Speed;
		ulong_t Result;
		XINPUT_VIBRATION Vibration;

		memset(&Vibration, 0, sizeof(XINPUT_VIBRATION));

		Vibration.wLeftMotorSpeed = Speed;
		Result = XInputSetState(ControllerSlot, &Vibration);

	}
	void XInput::SetHighFrequencyMotorSpeed(uint16_t Speed, ulong_t ControllerSlot)
	{
		m_Controllers[ControllerSlot].second.Settings.HighFreqMotorSpeed = Speed;
		ulong_t Result;
		XINPUT_VIBRATION Vibration;

		memset(&Vibration, 0, sizeof(XINPUT_VIBRATION));

		Vibration.wRightMotorSpeed = Speed;
		Result = XInputSetState(ControllerSlot, &Vibration);
	}

	void XInput::PollControllers()
	{
		for (ulong_t i = 0; i < m_Controllers.size(); i++)
		{
			if (!m_Controllers[i].second)
			{
				continue;
			}
			XINPUT_STATE State;

			memset(&State, 0, sizeof(XINPUT_STATE));

			XInputGetState(i, &State);

			if (State.dwPacketNumber != m_Controllers[i].second.PacketNumber)
			{
				m_Controllers[i].first = State.Gamepad;
				m_Controllers[i].second.PacketNumber = State.dwPacketNumber;

				ulong_t Result;
				XINPUT_BATTERY_INFORMATION BattInfo;
				memset(&BattInfo, 0, sizeof(XINPUT_BATTERY_INFORMATION));
				Result = XInputGetBatteryInformation(i, BATTERY_DEVTYPE_GAMEPAD, &BattInfo);
				if (Result == ERROR_SUCCESS)
				{
					m_Controllers[i].second.BatteryType = BattInfo.BatteryType;
					m_Controllers[i].second.BatteryLevel = BattInfo.BatteryLevel;
					m_Controllers[i].second.bConnected = false;
				}

				//TODO: Do more stuff here and check for changes, we'll lively use the event system for this, 
				//		however we need to make a true controller to do this properly

				CheckButtonInput(m_Controllers[i].first, m_Controllers[i].second);
				m_Controllers[i].second.ButtonState = State.Gamepad.wButtons;
			}
		}
	}
}

