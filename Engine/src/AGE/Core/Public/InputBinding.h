//
// Created by gdmgp on 3/13/2026.
//
#include "Core/Public/GamepadCodes.h"
#include "Core/Public/Keycodes.h"
#include "Core/Public/Pointers.h"

#ifndef AGE_INPUTBINDING_H
#define AGE_INPUTBINDING_H

namespace AGE
{
	namespace Binding
	{
		enum Type
		{
			Axis,
			Action,
			INVALID
		};
	}

	namespace KeyState
	{
		enum State
		{
			Pressed = 0,
			Released = 1
		};

	};



	struct InputBinding
	{
		using ActionCallbackFn = std::function<void()>;
		using AxisCallbackFn = std::function<void(float)>;

		virtual ~InputBinding() = default;

		static Ref<InputBinding> CreateGamepadBinding(const std::string_view& Name, GamePad::Buttons button = GamePad::Buttons::INVALID, Binding::Type bindingtype = Binding::Type::INVALID);
		static Ref<InputBinding> CreateGamepadBinding(const std::string_view& Name, GamePad::Axes axes = GamePad::Axes::INVALIDAXES, Binding::Type bindingtype = Binding::Type::Axis);
		static Ref<InputBinding> CreateKBMBinding(const std::string_view& Name, Key::Keys keycode = Key::INVALID, Binding::Type bindingtype = Binding::INVALID);
		static Ref<InputBinding> CreateInvalid();
		void BindAxisFunction(AxisCallbackFn Func)
		{
			BindedAxisFunction = Func;
		}
		void BindActionFunction(ActionCallbackFn Func)
		{
			BindedActionFunction = Func;
		}

		void ActionExecute()
		{
			BindedActionFunction();
		}
		void AxisExecute()
		{
			BindedAxisFunction(m_AxisValue);
		}
		virtual uint16_t GetKey() const = 0;
		std::string GetName() const { return m_BindingName; }
		std::string GetInputType() const {return m_InputType;}
		void SetInputType(const std::string_view& type) {m_InputType = type;}
		bool IsPaired() const { return bPaired; }
		void SetPaired(bool value) { bPaired = value; }
		int32_t GetHandle() const { return m_Handle; }
		float GetAxisValue() const { return m_AxisValue; }
		void SetAxisValue(float value) { m_AxisValue = value; }

		void GenerateNewHandle()
		{
			static int32_t sHandle = 1;
			m_Handle = sHandle++;
		}

		bool IsValid() { return m_Handle != -1; }

		bool operator==(const InputBinding& rhs)
		{
			return (IsValid() && GetHandle() == rhs.GetHandle());
		}
		KeyState::State m_State = KeyState::Pressed;
		std::string m_BindingName;

	protected:
		std::string m_InputType;
		uint8_t bPaired = 1;
		[[maybe_unused]] uint8_t bConsumeInput = 1;
		[[maybe_unused]] uint8_t bExecuteWhenPaused = 0;
		float m_AxisValue =0.f;
		int m_Handle;
		ActionCallbackFn BindedActionFunction;
		AxisCallbackFn BindedAxisFunction;
	};

	struct InvalidInputBinding_t : public InputBinding
	{
		InvalidInputBinding_t()
		{
			m_BindingName = "INVALID";
		}
		~InvalidInputBinding_t() = default;
		uint16_t GetKey() const override
		{
			return UINT16_MAX;
		}
	};

	struct GamepadInputBinding : public InputBinding
	{
		GamepadInputBinding(const std::string_view& Name,Binding::Type type)
			:m_BindingType(type)
		{
			m_BindingName = Name;
			bPaired = false;
			bConsumeInput = true;
			bExecuteWhenPaused = false;
			m_Handle = -1;
			m_State = KeyState::Released;
		}
		GamepadInputBinding(const std::string_view& Name,GamePad::Buttons button, Binding::Type type)
			:m_Button(button), m_BindingType(type)
		{
			m_BindingName = Name;
			bPaired = false;
			bConsumeInput = true;
			bExecuteWhenPaused = false;
			m_Handle = -1;
			m_State = KeyState::Released;
		}
		GamepadInputBinding(const std::string_view& Name,GamePad::Axes axes, Binding::Type type)
			:m_Axes(axes), m_BindingType(type)
		{
			m_BindingName = Name;
			bPaired = false;
			bConsumeInput = true;
			bExecuteWhenPaused = false;
			m_Handle = -1;
			m_State = KeyState::Released;
		}
		~GamepadInputBinding() override = default;

		uint16_t GetKey() const override
		{
			switch (m_BindingType)
			{
				case Binding::Axis:
				{
					return m_Axes;
				}
				case Binding::Action:
				{
					return m_Button;
				}
				default:
				{
					return UINT16_MAX;
				}
			}
		}

		GamePad::Buttons m_Button = GamePad::Buttons::INVALID;
		GamePad::Axes m_Axes = GamePad::Axes::INVALIDAXES;
		Binding::Type m_BindingType;

	private:
		GamepadInputBinding() = default;
	};

	struct KBMInputBinding : public InputBinding
	{
		KBMInputBinding(const std::string_view& Name, Binding::Type type)
			:m_BindingType(type)
		{
			m_BindingName = Name;
			bPaired = false;
			bConsumeInput = true;
			bExecuteWhenPaused = false;
			m_Handle = -1;
			m_State = KeyState::Released;
		}
		KBMInputBinding(const std::string_view& Name, Key::Keys keycode, Binding::Type type)
			:m_Key(keycode), m_BindingType(type)
		{
			m_BindingName = Name;
			bPaired = false;
			bConsumeInput = true;
			bExecuteWhenPaused = false;
			m_Handle = -1;
			m_State = KeyState::Released;
		}

		~KBMInputBinding() override = default;

		uint16_t GetKey() const override
		{
			switch (m_BindingType)
			{
				case Binding::Axis:
				{
					return UINT16_MAX; // TODO: Implement the mouse part of KBM
				}
				case Binding::Action:
				{
					return m_Key;
				}
				default:
				{
					return UINT16_MAX;
				}
			}
		}
		Key::Keys m_Key = Key::INVALID;
		Binding::Type m_BindingType;
	private:
		KBMInputBinding() = default;
	};
} // AGE

#endif //AGE_INPUTBINDING_H