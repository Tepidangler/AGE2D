#ifdef AG_PLATFORM_WINDOWS
#include "AGEpch.hpp"
#include "Core/Public/Input.h"
#include "App.h"
#include <GLFW/glfw3.h>

namespace AGE
{

	/**
 * @brief Checks if a key is currently pressed or repeated.
 *
 * This function checks the current state of a given key in the application's window. It uses the GLFW library to get the key state, which can be either GLFW_PRESS (the key was just pressed) or GLFW_REPEAT (the key is being held down). The function returns true if the key is currently pressed or repeated, and false otherwise.
 *
 * @param Keycode The integer code of the key to check. This should correspond to a value from the GLFW key enumeration.
 * 
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
 * This function checks the state of a given mouse button in the current window. It uses the GLFW library to get the state of the specified button.
 * 
 * @param Button The ID of the button to check, as defined by GLFW constants (e.g., `GLFW_MOUSE_BUTTON_LEFT`).
 * @return True if the mouse button is pressed, false otherwise.
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
 * This function checks whether the specified gamepad button is currently being pressed. It takes two parameters, an unsigned 16-bit integer for the gamepad ID and another unsigned 8-bit integer for the button ID. The function returns a boolean value indicating whether or not the button was pressed.
 * 
 * @param ID An unsigned 16-bit integer representing the gamepad ID to check.
 * @param Button An unsigned 8-bit integer representing the button ID to check.
 * @return A boolean value indicating if the specified gamepad button is currently being pressed (true) or not (false).
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
 * This function retrieves the current cursor position within the GLFW window. The position is returned as a pair of floats, where the first float represents the x-coordinate and the second float represents the y-coordinate.
 * 
 * @return A pair of floats representing the current mouse position in screen coordinates.
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
 * It uses the `IsJoyStickPresent` function for this purpose, which should be implemented elsewhere in the codebase.
 * 
 * @param ID The unique identifier of the joystick to check.
 * @return True if the joystick is present and connected, false otherwise.
 */
bool Input::IsJoyStickConnected(uint16_t ID)
	{
		return IsJoyStickPresent(ID);
	}

	/**
 * @brief This function returns the X-coordinate of the left joystick for a given device ID.
 * 
 * @param ID The unique identifier of the device whose joystick's X coordinate is to be returned.
 * 
 * @return Returns the X-coordinate value as a float.
 * 
 * @note This function assumes that the GetJoyStickLeftXY() function returns both X and Y coordinates in a std::pair object, where X represents the X-coordinate and Y represents the Y-coordinate of the left joystick.
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
 * @return Returns the Y-axis value as a float. If no such joystick exists, it will return Unknown.
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
 * The function uses the `GetJoyStickRightXY` method to get both the X and Y coordinates of the joystick, then it simply returns the X coordinate.
 * 
 * @param ID The unique identifier for the joystick.
 * @return float Returns the X-coordinate of the joystick with the given ID.
 */
float Input::GetJoyStickRightX(uint16_t ID)
	{
		auto [x, y] = GetJoyStickRightXY(ID);
		return x;
	}

	/**
 * @brief This function returns the Y-axis value of a joystick with a given ID.
 *
 * The function takes an unsigned 16 bit integer as input, which is used to identify the joystick. It then retrieves the X and Y values from the GetJoyStickRightXY() function using structured binding (auto [x, y] = GetJoyStickRightXY(ID);). The function returns only the Y value.
 *
 * @param ID An unsigned 16 bit integer used to identify a joystick.
 * @return A float representing the Y-axis value of the identified joystick.
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
 * This function retrieves the left trigger value of a joystick with a given ID. The trigger is typically located on the back of some game controllers, and it returns a float between 0.0 (fully depressed) to 1.0 (fully pressed). If the joystick is not connected, an error message will be logged and -2.f will be returned.
 *
 * @param ID The unique identifier for the joystick.
 * @return The left trigger value as a float between 0.0 and 1.0 if the joystick is present; otherwise -2.f.
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
 * This function retrieves the value of the right trigger from a connected joystick. The ID of the joystick is passed as an argument. 
 * If the joystick is present and has axes, it returns the value of the sixth axis (indexed at 5). Otherwise, it logs an error message and returns -2.0.
 *
 * @param ID The unique identifier for the joystick.
 * @return The value of the right trigger on the joystick or -2.0 if the joystick is not connected.
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
 * It uses the glfwJoystickPresent() function from GLFW library, which returns 1 if the joystick is present and 0 otherwise.
 *
 * @param ID The identifier of the joystick to check for.
 * @return true If the specified joystick is currently connected.
 * @return false Otherwise.
 */
bool Input::IsJoyStickPresent(uint16_t ID)
	{
		return glfwJoystickPresent(ID) == 1 ? true : false;
	}

	/**
 * @brief This function returns the X coordinate of the mouse cursor.
 *
 * The function uses the `GetMouseXY()` method to get both the X and Y coordinates of the mouse cursor, 
 * then it only returns the X coordinate.
 *
 * @return A float representing the X coordinate of the mouse cursor.
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
 * then it only returns the Y value.
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