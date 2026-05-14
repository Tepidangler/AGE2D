//
// Created by gdmgp on 3/13/2026.
//
#include "AGEpch.hpp"
#include "Core/Public/InputBinding.h"

namespace AGE
{
	/**
 * @brief Creates a gamepad input binding.
 * 
 * This function creates an instance of GamepadInputBinding based on the provided parameters. If the button parameter is not INVALID, it returns a reference to a new GamepadInputBinding object with the specified Name, button and binding type. Otherwise, it returns a reference to a new GamepadInputBinding object with only the Name and binding type.
 * 
 * @param Name The name of the input binding.
 * @param button The gamepad button that triggers this binding. If INVALID, no specific button is associated with this binding.
 * @param bindingtype The type of the input binding (e.<｜begin▁of▁sentence｜>g., keyboard, mouse).
 * 
 * @return A reference to a new GamepadInputBinding object.
 */
Ref<InputBinding> InputBinding::CreateGamepadBinding(const std::string_view& Name, GamePad::Buttons button, Binding::Type bindingtype)
	{
		if (button != GamePad::Buttons::INVALID)
		{
			return CreateRef<GamepadInputBinding>(Name,button, bindingtype);
		}
			return CreateRef<GamepadInputBinding>(Name, bindingtype);
	}

	/**
 * @brief Creates a gamepad input binding.
 * 
 * This function creates an instance of GamepadInputBinding based on the provided parameters. If axes are specified, it will create a GamepadInputBinding with both name and axes. Otherwise, it will only use the name. The type of binding is also passed in as a parameter.
 * 
 * @param Name The name of the gamepad input.
 * @param axes The axes to be used for the gamepad input (optional).
 * @param bindingtype The type of the binding, such as keyboard or mouse.
 * 
 * @return A reference to a GamepadInputBinding object.
 */
Ref<InputBinding> InputBinding::CreateGamepadBinding(const std::string_view &Name, GamePad::Axes axes,
		Binding::Type bindingtype)
	{
		if (axes != GamePad::Axes::INVALIDAXES)
		{
			return CreateRef<GamepadInputBinding>(Name,axes, bindingtype);
		}
		return CreateRef<GamepadInputBinding>(Name, bindingtype);
	}

	/**
 * @brief Creates an input binding object. The function checks if the provided key code is valid and creates a corresponding KBMInputBinding object accordingly. If the keycode is invalid, it still creates a KBMInputBinding object with only the name and type parameters.
 * 
 * @param Name The name of the input binding.
 * @param keycode The key code associated with the input binding.
 * @param bindingtype The type of the input binding (e.g., keyboard, mouse).
 * 
 * @return A reference to an InputBinding object. If the provided key code is valid, this will be a KBMInputBinding object; otherwise, it will still be a KBMInputBinding object with only the name and type parameters.
 */
Ref<InputBinding> InputBinding::CreateKBMBinding(const std::string_view& Name, Key::Keys keycode, Binding::Type bindingtype)
	{
		if (keycode != Key::INVALID)
		{
			return CreateRef<KBMInputBinding>(Name, keycode, bindingtype);
		}
			return CreateRef<KBMInputBinding>(Name, bindingtype);
	}

	/**
 * @brief Creates an invalid input binding instance.
 * 
 * This function creates and returns a reference to an InvalidInputBinding object, which is a subclass of InputBinding. It represents an invalid or undefined input binding.
 * 
 * @return A Ref<InvalidInputBinding_t> representing the created invalid input binding.
 */
Ref<InputBinding> InputBinding::CreateInvalid()
	{
		return CreateRef<InvalidInputBinding_t>();
	}
} // AGE