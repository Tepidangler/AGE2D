#include "AGEpch.hpp"
#include "Core/Public/Input.h"
#include "App.h"
#include <GLFW/glfw3.h>

namespace AGE
{

	bool Input::IsKeyPressed(int Keycode)
	{

		auto Window = static_cast<GLFWwindow*>(App::Get().GetDeviceManager().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(Window, Keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int Button)
	{
		auto Window = static_cast<GLFWwindow*>(App::Get().GetDeviceManager().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(Window, Button);

		return state == GLFW_PRESS;
	}

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

	std::pair<float, float> Input::GetMouseXY()
	{
		auto Window = static_cast<GLFWwindow*>(App::Get().GetDeviceManager().GetWindow().GetNativeWindow());

		double x, y;

		glfwGetCursorPos(Window, &x, &y);

		return { (float)x, (float)y };
	}

	bool Input::IsJoyStickConnected(uint16_t ID)
	{
		return IsJoyStickPresent(ID);
	}

	float Input::GetJoyStickLeftX(uint16_t ID)
	{
		auto [x, y] = GetJoyStickLeftXY(ID);
		return x;
	}

	float Input::GetJoyStickLeftY(uint16_t ID)
	{
		auto [x, y] = GetJoyStickLeftXY(ID);
		return y;
	}

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

	float Input::GetJoyStickRightX(uint16_t ID)
	{
		auto [x, y] = GetJoyStickRightXY(ID);
		return x;
	}

	float Input::GetJoyStickRightY(uint16_t ID)
	{
		auto [x, y] = GetJoyStickRightXY(ID);
		return y;
	}

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

	bool Input::IsJoyStickPresent(uint16_t ID)
	{
		return glfwJoystickPresent(ID) == 1 ? true : false;
	}

	float Input::GetMouseX()
	{
		auto [x, y] = GetMouseXY();
		return x;
	}
	float Input::GetMouseY()
	{
		auto [x, y] = GetMouseXY();

		return y;
	}

}