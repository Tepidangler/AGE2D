//
// Created by gdmgp on 3/7/2026.
//
#ifdef AG_PLATFORM_LINUX
#include "AGEpch.hpp"
#include "Core/Public/Input.h"
#include "App.h"
#include <GLFW/glfw3.h>

namespace AGE
{

	/**
 * @brief Checks if a key is pressed or repeated.
 *
 * This function checks the current state of a given key in the application's window. It returns true if the key is currently being pressed or has been held down for more than one frame, false otherwise.
 * 
 * @param Keycode The GLFW key code to check.
 * @return True if the key is currently being pressed or repeated, false otherwise.
 */
bool Input::IsKeyPressed(int Keycode)
	{

		auto Window = static_cast<GLFWwindow*>(App::Get().GetDeviceManager().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(Window, Keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	/**
 * @brief Checks if a mouse button is pressed.
 *
 * This function checks the current state of a given mouse button in the application's window. It uses the GLFW library to get the current state of the specified button.
 * 
 * @param Button The ID of the button to check, as defined by GLFW constants (e.g., GLFW_MOUSE_BUTTON_LEFT).
 * @return True if the button is pressed, false otherwise.
 */
bool Input::IsMouseButtonPressed(int Button)
	{
		auto Window = static_cast<GLFWwindow*>(App::Get().GetDeviceManager().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(Window, Button);

		return state == GLFW_PRESS;
	}

	/**
 * @brief Checks if a gamepad button is pressed.
 * 
 * This function checks the state of a specific button on a connected gamepad. It takes two parameters, an unsigned 16-bit integer for the gamepad ID and another unsigned 8-bit integer for the button code. If the gamepad is present and the specified button is pressed, it logs this information and returns true. Otherwise, it returns false.
 * 
 * @param ID The unique identifier of the gamepad to be checked.
 * @param Button The specific button on the gamepad to be checked.
 * @return True if the button is pressed, False otherwise.
 */
bool Input::IsGamepadButtonPressed(uint16_t ID, uint8_t Button)
	{
		GLFWgamepadstate State;
		if (IsJoyStickPresent(ID))
		{
			if (glfwGetGamepadState(ID, &State)) // Consider changing to glfwGetJoysticButtons() because of the redundancy of checking if the joystick is present twice
			{
				if (State.buttons[Button] == GLFW_PRESS)
				{
					CoreLogger::Info("Gamepad Button {0} on Gamepad {1} Pressed!", Button, ID);
					return true;
				}
				return false;
			}
			return false;

		}
		CoreLogger::Error("Joystick {0} Not Connected!", ID);
		return false;
	}

	/**
 * @brief Get the current mouse position in screen coordinates.
 *
 * This function retrieves the current cursor position on the window in screen coordinates. The values are returned as a pair of floats where the first value is the x-coordinate and the second value is the y-coordinate.
 * 
 * @return A pair of float values representing the mouse's current x and y positions respectively.
 */
std::pair<float, float> Input::GetMouseXY()
	{
		auto Window = static_cast<GLFWwindow*>(App::Get().GetDeviceManager().GetWindow().GetNativeWindow());

		double x, y;

		glfwGetCursorPos(Window, &x, &y);

		return { (float)x, (float)y };
	}

	/** 
 * @brief Checks if a joystick is connected.
 * 
 * This function checks whether the specified joystick is currently connected to the system.
 * It uses the `IsJoyStickPresent` method for this purpose, which should be implemented elsewhere in the codebase.
 * 
 * @param ID The unique identifier of the joystick to check.
 * @return True if the joystick is present and connected, false otherwise.
 */
bool Input::IsJoyStickConnected(uint16_t ID)
	{
		return IsJoyStickPresent(ID);
	}

	/**
 * @brief This function returns the X-coordinate of the left joystick.
 *
 * The function takes an unsigned 16 bit integer as input, which is presumably a unique identifier for the joystick. It then calls another function to get both the X and Y coordinates of the left joystick, unpacks them into two variables using structured binding (auto [x, y] = GetJoyStickLeftXY(ID)), and finally returns only the X coordinate.
 * 
 * @param ID The unique identifier for the joystick.
 * @return float Returns the X-coordinate of the left joystick.
 */
float Input::GetJoyStickLeftX(uint16_t ID)
	{
		auto [x, y] = GetJoyStickLeftXY(ID);
		return x;
	}

	/**
 * @brief This function returns the Y-axis value of a joystick with a given ID.
 *
 * @param[in] ID The unique identifier for the joystick.
 * 
 * @return Returns the Y-axis value of the joystick as a float. If no joystick is found, it returns Unknown.
 */
float Input::GetJoyStickLeftY(uint16_t ID)
	{
		auto [x, y] = GetJoyStickLeftXY(ID);
		return y;
	}

	/**
 * @brief Get the XY coordinates of the left joystick.
 *
 * This function retrieves the X and Y coordinates of the left joystick for a given joystick ID. 
 * The coordinates are returned as a pair of floats in the range -1 to 1. If the joystick is not connected, it returns (-2,-2).
 *
 * @param ID The unique identifier for the joystick.
 * @return A pair of float values representing the X and Y coordinates of the left joystick.
 */
std::pair<float, float> Input::GetJoyStickLeftXY(uint16_t ID)
	{
		int count;
		const float* Axes;

		if (IsJoyStickPresent(ID))
		{
			Axes = glfwGetJoystickAxes(ID, &count);
			return { Axes[0], Axes[1] };
		}
		CoreLogger::Error("Joystick {0} Not Connected!", ID);
		return {-2.f,-2.f};
	}

	/**
 * @brief This function returns the X-coordinate of a joystick with a given ID.
 *
 * The function takes an unsigned 16-bit integer as input, which is presumably the ID of the joystick. It then calls another function to get both the X and Y coordinates of the joystick. These are unpacked into two variables using structured binding (auto [x, y] = GetJoyStickRightXY(ID)). The function finally returns the value of x, which is presumably the X-coordinate of the joystick.
 *
 * @param ID An unsigned 16-bit integer representing the ID of the joystick to get the X coordinate from.
 * @return A float representing the X-coordinate of the joystick with the given ID.
 */
float Input::GetJoyStickRightX(uint16_t ID)
	{
		auto [x, y] = GetJoyStickRightXY(ID);
		return x;
	}

	/**
 * @brief Retrieves the Y-axis value of a joystick with a given ID.
 *
 * This function retrieves the Y-axis value from the right joystick associated with the provided ID. 
 * The returned value is in the range [-1, 1]. If the joystick does not exist or if it has not been initialized, this function will return 0.
 *
 * @param ID The unique identifier for the joystick.
 * @return The Y-axis value of the right joystick with the given ID.
 */
float Input::GetJoyStickRightY(uint16_t ID)
	{
		auto [x, y] = GetJoyStickRightXY(ID);
		return y;
	}

	/**
 * @brief Get the XY coordinates of the right joystick.
 *
 * This function retrieves the current state of the specified joystick and returns its X and Y axes as a pair of floats. If the joystick is not connected, it logs an error message and returns (-2.f, -2.f).
 *
 * @param ID The unique identifier for the joystick.
 * @return A pair of float values representing the X and Y coordinates of the right joystick.
 */
std::pair<float, float> Input::GetJoyStickRightXY(uint16_t ID)
	{
		int count;
		const float* Axes;

		if (IsJoyStickPresent(ID))
		{
			Axes = glfwGetJoystickAxes(ID, &count);
			return { Axes[2], Axes[3] };
		}
		CoreLogger::Error("Joystick {0} Not Connected!", ID);
		return { -2.f, -2.f };
	}

	/**
 * @brief Get the left trigger value from a joystick.
 *
 * This function retrieves the left trigger value from a connected joystick. The trigger is typically located on the back of some game controllers, and it returns a float between 0.0 (fully depressed) to 1.0 (fully pressed). If the joystick is not present or if there are issues with retrieving the data, -2.f is returned as an error code.
 *
 * @param ID The unique identifier for the joystick.
 * @return The left trigger value on a scale of 0.0 to 1.0, or -2.f in case of errors.
 */
float Input::GetJoyStickLeftTrigger(uint16_t ID)
	{
		int count;
		const float* Axes;

		if (IsJoyStickPresent(ID))
		{
			Axes = glfwGetJoystickAxes(ID, &count);
			return Axes[4];
		}
		CoreLogger::Error("Joystick {0} Not Connected!", ID);
		return -2.f;
	}

	/**
 * @brief Get the value of the right trigger on a joystick.
 *
 * This function retrieves the value of the right trigger from a connected joystick. The joystick ID is required to identify the correct device. 
 * If the joystick is not present, an error message will be logged and -2.0 will be returned.
 *
 * @param ID The unique identifier for the joystick.
 * @return The value of the right trigger as a float between 0.0 (not pressed) and 1.0 (fully pressed). If the joystick is not connected, -2.0 is returned.
 */
float Input::GetJoyStickRightTrigger(uint16_t ID)
	{
		int count;
		const float* Axes;

		if (IsJoyStickPresent(ID))
		{
			Axes = glfwGetJoystickAxes(ID, &count);
			return Axes[5];
		}
		CoreLogger::Error("Joystick {0} Not Connected!", ID);
		return -2.f;
	}

	/**
 * @brief Checks if a joystick is present.
 *
 * This function checks whether the specified joystick ID is currently connected to the system.
 *
 * @param ID The identifier of the joystick to check for.
 * @return True if the joystick is present, false otherwise.
 */
bool Input::IsJoyStickPresent(uint16_t ID)
	{
		return glfwJoystickPresent(ID) == 1 ? true : false;
	}

	/**
 * @brief This function returns the X coordinate of the mouse cursor.
 *
 * @param None
 * @return float Returns a floating-point number representing the X coordinate of the mouse cursor.
 */
float Input::GetMouseX()
	{
		auto [x, y] = GetMouseXY();
		return x;
	}
	/**
 * @brief This function returns the Y coordinate of the mouse cursor.
 *
 * The function uses the `GetMouseXY()` method to get both X and Y coordinates of the mouse cursor, 
 * then it only returns the Y coordinate.
 *
 * @return A float representing the Y coordinate of the mouse cursor.
 */
float Input::GetMouseY()
	{
		auto [x, y] = GetMouseXY();

		return y;
	}

}
#endif