//
// Created by gdmgp on 3/13/2026.
//
#include "AGEpch.hpp"
#include "Core/Public/InputBinding.h"

namespace AGE
{
	Ref<InputBinding> InputBinding::CreateGamepadBinding(const std::string_view& Name, GamePad::Buttons button, Binding::Type bindingtype)
	{
		if (button != GamePad::Buttons::INVALID)
		{
			return CreateRef<GamepadInputBinding>(Name,button, bindingtype);
		}
			return CreateRef<GamepadInputBinding>(Name, bindingtype);
	}

	Ref<InputBinding> InputBinding::CreateGamepadBinding(const std::string_view &Name, GamePad::Axes axes,
		Binding::Type bindingtype)
	{
		if (axes != GamePad::Axes::INVALIDAXES)
		{
			return CreateRef<GamepadInputBinding>(Name,axes, bindingtype);
		}
		return CreateRef<GamepadInputBinding>(Name, bindingtype);
	}

	Ref<InputBinding> InputBinding::CreateKBMBinding(const std::string_view& Name, Key::Keys keycode, Binding::Type bindingtype)
	{
		if (keycode != Key::INVALID)
		{
			return CreateRef<KBMInputBinding>(Name, keycode, bindingtype);
		}
			return CreateRef<KBMInputBinding>(Name, bindingtype);
	}

	Ref<InputBinding> InputBinding::CreateInvalid()
	{
		return CreateRef<InvalidInputBinding_t>();
	}
} // AGE