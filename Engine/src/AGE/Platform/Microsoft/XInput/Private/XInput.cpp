#ifdef AG_PLATFORM_WINDOWS
#include "AGEpch.hpp"
#include "Platform/Microsoft/XInput/Public/XInput.h"
#include "Core/Public/GamepadCodes.h"
#include "Events/Public/GameEvent.h"
#include "Core/Public/Log.h"
namespace AGE
{
	/**
 * @brief Constructor for the XInput class. Initializes and registers controllers when an instance of this class is created.
 */
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
	/**
 * @brief Clamps the left thumbstick values to a specified deadzone.
 * 
 * This function takes in an XINPUT_GAMEPAD structure and its corresponding controller info, which includes settings for the deadzone. It then clamps the left thumbstick x and y axes based on the magnitude of the input. If the magnitude is greater than the deadzone, it normalizes the values to a range between 0 and 1.
 * 
 * @param Gamepad The XINPUT_GAMEPAD structure containing the raw left thumbstick values.
 * @param Info The controller info including settings for the deadzone.
 */
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
			AxisEvent Event(GamePad::Axes::GamePadAxisLeftX, NormalizedLX);
			Info.CallbackFn(Event);
		}

		if (NormalizedLY != 0.f)
		{
			AxisEvent Event(GamePad::Axes::GamePadAxisLeftY, NormalizedLY);
			Info.CallbackFn(Event);
			
		}
	}

	/**
 * @brief Clamps the right thumbstick values to a specified deadzone.
 * 
 * This function takes in a reference to an XINPUT_GAMEPAD structure and an XInputControllerInfo object, which contain information about the controller settings. It first calculates the magnitude of the right thumbstick's x and y axes by taking the square root of their squares. The normalized values for these axes are then calculated as the original value divided by its magnitude.
 * 
 * If the magnitude is greater than the deadzone, it checks if it exceeds a maximum value (32767). If so, it sets the magnitude to this maximum value. It also subtracts the deadzone from the magnitude. The normalized magnitude is then calculated as the adjusted magnitude divided by the difference between the maximum value and the deadzone.
 * 
 * If the magnitude is less than or equal to the deadzone, both the magnitude and the normalized magnitude are set to zero and the function returns immediately.
 * 
 * Finally, if either of the normalized x or y axes values are non-zero, an AxisEvent object is created with the appropriate axis type (JoyStick::GamePadAxisRightX for x and JoyStick::GamePadAxisRightY for y) and value, which is then passed to the callback function associated with the XInputControllerInfo object.
 * 
 * @param Gamepad Reference to an XINPUT_GAMEPAD structure containing the right thumbstick values.
 * @param Info Object containing information about the controller settings.
 */
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
			AxisEvent Event(GamePad::Axes::GamePadAxisRightX, NormalizedRX);
			Info.CallbackFn(Event);
		}

		if (NormalizedRY != 0.f)
		{
			AxisEvent Event(GamePad::Axes::GamePadAxisRightY, NormalizedRX);
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
			AxisEvent Event(GamePad::Axes::GamePadAxisLeftTrigger, NormalizedLT);
			Info.CallbackFn(Event);
		}
	}
	/**
 * @brief Clamps the value of the right trigger to a normalized range between 0 and 1, taking into account the deadzone settings.
 * 
 * @param Gamepad The gamepad whose right trigger value to clamp.
 * @param Info Contains settings for deadzones and a callback function.
 */
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
			AxisEvent Event(GamePad::Axes::GamePadAxisRightTrigger, NormalizedRT);
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
				GamepadButtonPressedEvent Event(GamePad::Axes::GamePadAxisLeftTrigger);

				Info.CallbackFn(Event);
				
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(GamePad::Axes::GamePadAxisLeftTrigger);
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
				GamepadButtonPressedEvent Event(GamePad::Axes::GamePadAxisRightTrigger);

				Info.CallbackFn(Event);
			}
			else if (Keystroke.Flags == XINPUT_KEYSTROKE_KEYUP)
			{
				GamepadButtonReleasedEvent Event(GamePad::Axes::GamePadAxisRightTrigger);
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
	/**
 * @brief This function checks if a specific bit is set in a given number.
 * @param Number The number to check for the bit.
 * @param Mask The mask representing the bit position to be checked.
 * @return Returns true if the specified bit is set, false otherwise.
 */
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
	/**
 * @brief GetLRDeadzones returns the left and right deadzones for a given controller slot.
 * 
 * @param Slot The index of the controller whose deadzones are to be retrieved.
 * @return A pair containing the left and right deadzone values.
 * 
 * @note This function assumes that the input is within the valid range (0 <= Slot < number of controllers).
 */
std::pair<uint16_t, uint16_t> XInput::GetLRDeadzones(ulong_t Slot)
	{
		return std::pair<uint16_t, uint16_t>(m_Controllers[Slot].second.Settings.LeftThumbstickDeadzone, m_Controllers[Slot].second.Settings.RightThumbstickDeadzone);
	}
	/**
 * @brief Gets the deadzone value for the left thumbstick.
 * 
 * This function retrieves the deadzone value for the left thumbstick from the specified slot. The returned value is in the range of 0 to 32767, representing a percentage of the total possible input range (16-bit unsigned integer).
 * 
 * @param Slot The slot number to retrieve the deadzone value from.
 * @return uint16_t The left thumbstick deadzone value in the specified slot.
 */
uint16_t XInput::GetLeftThumbstickDeadzone(ulong_t Slot)
	{
		return GetLRDeadzones(Slot).first;
	}
	/**
 * @brief Set the left thumbstick deadzone for a specific controller slot.
 *
 * This function sets the value of the left thumbstick deadzone for a given controller slot. The deadzone is a value between 0 and 100, where 0 represents no deadzone (all input values are sent to the device) and 100 represents full deadzone (no input values are sent to the device).
 *
 * @param Slot The slot of the controller whose left thumbstick deadzone is being set.
 * @param Value The new value for the left thumbstick deadzone, between 0 and 100.
 */
void XInput::SetLeftThumbstickDeadzone(ulong_t Slot, uint16_t Value)
	{
		m_Controllers[Slot].second.Settings.LeftThumbstickDeadzone = Value;

	}
	/**
 * @brief Gets the deadzone value for the right thumbstick.
 * 
 * This function retrieves the deadzone value for the right thumbstick from a specified slot. The returned value is in the range of 0 to 32767, representing the deadzone size.
 * 
 * @param Slot The slot number to retrieve the deadzone values from.
 * @return uint16_t The deadzone value for the right thumbstick.
 */
uint16_t XInput::GetRightThumbstickDeadzone(ulong_t Slot)
	{
		return GetLRDeadzones(Slot).second;
	}
	/**
 * @brief Set the right thumbstick deadzone for a specific controller slot.
 *
 * This function sets the value of the right thumbstick deadzone for a given controller slot. The deadzone is a value between 0 and 100, where 0 represents no deadzone (all input values are sent to the game) and 100 represents full deadzone (no input values are sent to the game).
 *
 * @param Slot The slot of the controller whose right thumbstick deadzone is being set.
 * @param Value The new value for the right thumbstick deadzone. Must be between 0 and 100, inclusive.
 */
void XInput::SetRightThumbstickDeadzone(ulong_t Slot, uint16_t Value)
	{
		m_Controllers[Slot].second.Settings.RightThumbstickDeadzone = Value;
	}
	/**
 * @brief Get the trigger thresholds for a specific controller slot.
 * 
 * This function retrieves the left and right trigger deadzones for a given controller slot. The deadzones are represented as uint16_t values, which represent the threshold levels at which triggers will be considered 'pressed'.
 *
 * @param Slot The index of the controller whose thresholds you want to retrieve. This is an unsigned long integer that represents the position of the controller in a controllers array.
 * 
 * @return A pair of uint16_t values representing the left and right trigger deadzones, respectively. If the provided slot number exceeds the total number of controllers, this function will return (0, 0).
 */
std::pair<uint16_t, uint16_t> XInput::GetTriggerThresholds(ulong_t Slot)
	{
		return std::pair<uint16_t, uint16_t>(m_Controllers[Slot].second.Settings.LeftTriggerDeadzone, m_Controllers[Slot].second.Settings.RightTriggerDeadzone);
	}
	/**
 * @brief Retrieves the left trigger threshold for a given slot.
 * 
 * This function retrieves the left trigger threshold value from the specified slot. The returned value is in the range of 0 to 65535, representing the analog input level that will cause the controller's triggers to be activated.
 * 
 * @param Slot The slot number for which to retrieve the trigger threshold. This should be a value between 1 and 4, inclusive.
 * @return uint16_t The left trigger threshold value in the range of 0 to 65535.
 */
uint16_t XInput::GetLeftTriggerThreshold(ulong_t Slot)
	{
		return GetTriggerThresholds(Slot).first;
	}
	/**
 * @brief Set the left trigger threshold for a specific controller slot.
 * 
 * This function sets the deadzone value for the left trigger of the specified controller slot. The deadzone is a value between 0 and 127 that determines how sensitive the input needs to be before it's registered as meaningful.
 * @param Slot The index of the controller slot, which must be less than XINPUT_MAX_CONTROLLERS (currently 4).
 * @param Value The new deadzone value, a uint16_t between 0 and 127 inclusive.
 * @return void
 */
void XInput::SetLeftTriggerThreshold(ulong_t Slot, uint16_t Value)
	{
		m_Controllers[Slot].second.Settings.LeftTriggerDeadzone = Value;
	}
	/**
 * @brief This function returns the right trigger threshold for a given slot.
 * 
 * The function uses the `GetTriggerThresholds` method to get the pair of thresholds (left, right) for a specific slot. It then returns the second value in this pair, which represents the right trigger threshold.
 * 
 * @param Slot The slot number for which we want to retrieve the right trigger threshold.
 * @return uint16_t The right trigger threshold for the given slot.
 */
uint16_t XInput::GetRightTriggerThreshold(ulong_t Slot)
	{
		return GetTriggerThresholds(Slot).second;
	}
	/**
 * @brief Set the right trigger threshold for a specific controller slot.
 * 
 * This function sets the right trigger threshold value for a given controller slot. The threshold is used to determine when the analog input should be interpreted as a button press or hold.
 * 
 * @param Slot The index of the controller slot whose right trigger threshold is being set.
 * @param Value The new right trigger threshold value, which must be between 0 and UINT16_MAX (inclusive).
 * 
 * @return void
 */
void XInput::SetRightTriggerThreshold(ulong_t Slot, uint16_t Value)
	{
		m_Controllers[Slot].second.Settings.RightTriggerDeadzone = Value;
	}
	/**
 * @brief Set the low frequency motor speed for a specific controller slot.
 *
 * This function sets the low frequency motor speed of a specified controller slot. The speed is represented as an unsigned 16-bit integer, with higher values representing faster motor movement.
 *
 * @param Speed The new low frequency motor speed to set. Must be between XINPUT_GAMEPAD_LEFT_TRIGGER_DEADZONE and XINPUT_GAMEPAD_RIGHT_TRIGGER_DEADZONE.
 * @param ControllerSlot The slot of the controller whose low frequency motor speed to set. Must be a valid controller slot number (0-3).
 */
void XInput::SetLowFrequencyMotorSpeed(uint16_t Speed, ulong_t ControllerSlot)
	{
		m_Controllers[ControllerSlot].second.Settings.LowFreqMotorSpeed = Speed;
		ulong_t Result;
		XINPUT_VIBRATION Vibration;

		memset(&Vibration, 0, sizeof(XINPUT_VIBRATION));

		Vibration.wLeftMotorSpeed = Speed;
		Result = XInputSetState(ControllerSlot, &Vibration);

	}
	/**
 * @brief Set the high frequency motor speed for a specific controller slot.
 *
 * This function sets the high frequency motor speed of a specified controller slot. The speed is set in the range of uint16_t, where 0 represents no vibration and 65535 represents maximum vibration.
 *
 * @param Speed The new high frequency motor speed to be set. Must be within the range of uint16_t (0-65535).
 * @param ControllerSlot The slot number of the controller whose motor speed is being set.
 */
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
#endif
