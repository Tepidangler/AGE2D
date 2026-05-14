#pragma once
#ifdef AG_PLATFORM_WINDOWS
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

		/**
 * @brief Default destructor for the XInput class.
 *
 * This function is used to clean up any resources that the XInput object may be using, such as memory or file handles. It's important to ensure that all resources are properly released when they are no longer needed to prevent potential memory leaks or other issues. 
 *
 * @return void
 */
/**
 * @brief Default destructor for the XInput class.
 *
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime, such as memory or file handles. It does not perform any operations on the state of the object itself.
 *
 * @return void
 */
~XInput() = default;

		/**
 * @brief Constructor for the XInput class. This constructor is deleted to prevent copying of objects.
 * 
 * @param other The object to be copied.
 */
/**
 * @brief Constructs a new instance of the XInput class using copy semantics.
 *
 * This constructor is deleted to prevent copying of existing instances, ensuring that each instance has its own resources and state.
 *
 * @param other The instance to be copied.
 */
XInput(const XInput&) = delete;
		/**
 * @brief This is a move constructor for the XInput class that has been explicitly deleted to prevent copying of objects.
 * 
 * @param other The object to be moved from.
 */
/**
 * @brief This is a move constructor for the XInput class that has been explicitly deleted to prevent copying of objects.
 * @param other The object to be moved from.
 */
XInput(XInput&&) = delete;

		/**
 * @brief Retrieves the gamepad and controller information for all connected controllers.
 * @return A reference to an array of pairs where each pair contains a XINPUT_GAMEPAD structure representing the current state of a controller, 
 *         and a XInputControllerInfo struct containing additional information about that controller. The size of this array is determined by XUSER_MAX_COUNT (16).
 */
/**
 * @brief Retrieves the gamepad and controller information for all connected controllers.
 * @return A reference to an array of pairs where each pair contains a XINPUT_GAMEPAD structure and corresponding XInputControllerInfo.
 */
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

		/**
 * @brief This function sets the event callback for all controllers in the system.
 *
 * The function takes an EventCallbackFn object as input, which is a callable type that represents the event callback function. 
 * It iterates over each controller (C) in the m_Controllers map and assigns the provided Callback to its corresponding CallbackFn member.
 * This means that whenever any event occurs within a controller, it will trigger the specified callback function.
 *
 * @param Callback The EventCallbackFn object representing the new event callback function.
 */
/**
 * @brief This function sets the event callback for all controllers in the system.
 *
 * The function takes an EventCallbackFn object as input, which is a callable type that represents the event callback function. 
 * It iterates over each controller (C) in the m_Controllers map and assigns the provided Callback to its corresponding CallbackFn member.
 * This means that whenever any event occurs within a controller, it will trigger the specified callback function.
 *
 * @param Callback The new event callback function to be set for all controllers.
 */
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
#endif
