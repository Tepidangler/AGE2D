#pragma once
#include "Core/Public/Core.h"
#include "Structs/Public/DataStructures.h"
#include <Xinput.h>
#include <array>


namespace AGE
{
	class XInput final
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		XInput();

		~XInput() = default;

		XInput(const XInput&) = delete;
		XInput(XInput&&) = delete;

		std::array<std::pair<XINPUT_GAMEPAD, XInputControllerInfo>, XUSER_MAX_COUNT>& GetControllers() { return m_Controllers; }

		void RegisterControllers();

		void RegisterSingleController(ulong_t Slot);

		std::pair<uint16_t,uint16_t> GetLRDeadzones(ulong_t Slot);
		uint16_t GetLeftThumbstickDeadzone(ulong_t Slot);
		void SetLeftThumbstickDeadzone(ulong_t Slot, uint16_t Value);
		uint16_t GetRightThumbstickDeadzone(ulong_t Slot);
		void SetRightThumbstickDeadzone(ulong_t Slot, uint16_t Value);

		std::pair<uint16_t, uint16_t> GetTriggerThresholds(ulong_t Slot);
		uint16_t GetLeftTriggerThreshold(ulong_t Slot);
		void SetLeftTriggerThreshold(ulong_t Slot, uint16_t Value);
		uint16_t GetRightTriggerThreshold(ulong_t Slot);
		void SetRightTriggerThreshold(ulong_t Slot, uint16_t Value);



		void SetLowFrequencyMotorSpeed(uint16_t Speed, ulong_t ControllerSlot);
		void SetHighFrequencyMotorSpeed(uint16_t Speed, ulong_t ControllerSlot);

		void PollControllers();

		inline void SetEventCallback(const EventCallbackFn& Callback)
		{
			for (auto& C : m_Controllers)
			{
				C.second.CallbackFn = Callback;
			}
		}
	private:

		void CheckButtonInput(XINPUT_GAMEPAD& Gamepad, const XInputControllerInfo& Info);
		void ClampLeftThumbstickDeadZone(XINPUT_GAMEPAD& Gamepad, const XInputControllerInfo& Info);
		void ClampRightThumbstickDeadZone(XINPUT_GAMEPAD& Gamepad, const XInputControllerInfo& Info);
		void ClampLeftTriggerDeadZone(XINPUT_GAMEPAD& Gamepad, const XInputControllerInfo& Info);
		void ClampRightTriggerDeadZone(XINPUT_GAMEPAD& Gamepad, const XInputControllerInfo& Info);
		bool IsBitSet(uint16_t Number, uint16_t Mask);
	private:

		std::array<std::pair<XINPUT_GAMEPAD, XInputControllerInfo>, XUSER_MAX_COUNT> m_Controllers;


	};
}
