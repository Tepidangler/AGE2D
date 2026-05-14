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

		/**
 * @brief Virtual destructor for the InputBinding class.
 *
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime, such as memory or file handles. It does not return anything and has no parameters. 
 */
virtual ~InputBinding() = default;

		static Ref<InputBinding> CreateGamepadBinding(const std::string_view& Name, GamePad::Buttons button = GamePad::Buttons::INVALID, Binding::Type bindingtype = Binding::Type::INVALID);
		static Ref<InputBinding> CreateGamepadBinding(const std::string_view& Name, GamePad::Axes axes = GamePad::Axes::INVALIDAXES, Binding::Type bindingtype = Binding::Type::Axis);
		static Ref<InputBinding> CreateKBMBinding(const std::string_view& Name, Key::Keys keycode = Key::INVALID, Binding::Type bindingtype = Binding::INVALID);
		static Ref<InputBinding> CreateInvalid();
		/**
 * @brief This function binds an axis callback function to the game controller.
 *
 * @param Func The function that will be called when a specific event on an axis occurs.
 */
void BindAxisFunction(AxisCallbackFn Func)
		{
			BindedAxisFunction = Func;
		}
		/**
 * @brief This function binds an action callback function to the class instance.
 * 
 * @param Func The ActionCallbackFn type function that will be bound as the new action callback function.
 * @return None
 */
void BindActionFunction(ActionCallbackFn Func)
		{
			BindedActionFunction = Func;
		}

		/**
 * @brief Executes the binded action function.
 * 
 * This function calls the BindedActionFunction, which is presumably a method that performs some action when called.
 * The exact behavior of this function depends on its implementation and cannot be accurately described here.
 *
 * @return void
 */
void ActionExecute()
		{
			BindedActionFunction();
		}
		/**
 * @brief Executes the axis function with the stored m_AxisValue.
 * 
 * This function calls the BindedAxisFunction member function of the class, passing in the value of m_AxisValue as an argument. It is assumed that this member function handles the actual execution of the axis function.
 * 
 * @return void
 */
void AxisExecute()
		{
			BindedAxisFunction(m_AxisValue);
		}
		virtual uint16_t GetKey() const = 0;
		/**
 * @brief Returns the name of the binding.
 * @return A string containing the name of the binding. If no name is set, returns an empty string.
 */
std::string GetName() const { return m_BindingName; }
		/**
 * @brief This function returns the type of input used in the system.
 * @return A string representing the type of input, which can be "Unknown" if it is not known or has not been set yet.
 */
std::string GetInputType() const {return m_InputType;}
		/**
 * @brief Sets the input type for a specific component.
 * @param[in] type A string view representing the new input type.
 * @return void
 */
void SetInputType(const std::string_view& type) {m_InputType = type;}
		/**
 * @brief Checks whether the object is paired.
 *
 * This function returns a boolean value indicating whether the object is currently paired or not.
 *
 * @return True if the object is paired, false otherwise.
 */
bool IsPaired() const { return bPaired; }
		/**
 * @brief Sets the paired status of an object.
 *
 * This function sets the 'bPaired' member variable to a specified boolean value, indicating whether or not the object is in a pairing state.
 *
 * @param value A boolean value representing the new paired status of the object.
 */
void SetPaired(bool value) { bPaired = value; }
		/**
 * @brief This function returns the handle value of an object.
 * @return The integer representation of the handle.
 */
int32_t GetHandle() const { return m_Handle; }
		/**
 * @brief This function returns the current value of the axis.
 * @return A float representing the current value of the axis.
 */
float GetAxisValue() const { return m_AxisValue; }
		/**
 * @brief This function sets the axis value to a given float value.
 * @param value The new value for the axis.
 * @return void
 */
void SetAxisValue(float value) { m_AxisValue = value; }

		/**
 * @brief This function generates a new handle for an object. The generated handle is unique and sequential, starting from 1.
 * @return void
 */
void GenerateNewHandle()
		{
			static int32_t sHandle = 1;
			m_Handle = sHandle++;
		}

		/**
 * @brief Checks whether the object handle is valid.
 *
 * This function checks if the object's handle is not equal to -1, indicating that it is a valid handle.
 *
 * @return True if the handle is valid (not equal to -1), false otherwise.
 */
bool IsValid() { return m_Handle != -1; }

		/**
 * @brief Compares two InputBinding objects for equality based on their validity and handle values.
 * @param rhs The right-hand side of the comparison.
 * @return True if both objects are valid and have the same handle value, false otherwise.
 */
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
		/**
 * @brief Default constructor for InvalidInputBinding_t class.
 * Initializes the binding name to "INVALID".
 */
InvalidInputBinding_t()
		{
			m_BindingName = "INVALID";
		}
		/**
 * @brief Default destructor for the InvalidInputBinding_t class.
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime, such as memory or file handles. It does not return a value and has no parameters.
 */
~InvalidInputBinding_t() = default;
		/**
 * @brief This function returns a constant 16-bit unsigned integer with the maximum value.
 * @return A constant 16-bit unsigned integer with the maximum value (UINT16_MAX).
 */
uint16_t GetKey() const override
		{
			return UINT16_MAX;
		}
	};

	struct GamepadInputBinding : public InputBinding
	{
		/**
 * @brief Constructor for GamepadInputBinding class.
 *
 * This constructor initializes a new instance of the GamepadInputBinding class with the given name and type. It sets default values for some member variables such as bPaired, bConsumeInput, bExecuteWhenPaused, m_Handle, and m_State.
 * 
 * @param Name The name of the binding.
 * @param type The type of the binding (Keyboard, Mouse etc.).
 */
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
		/**
 * @brief GamepadInputBinding is a constructor for the class that initializes an instance of GamepadInputBinding.
 * @param Name The name of the binding, which will be used to identify it in the gamepad input system.
 * @param button The specific button on the gamepad that this binding corresponds to.
 * @param type The type of the binding (e.<｜begin▁of▁sentence｜>croll down for more details).
 * 
 * @return None
 */
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
		/**
 * @brief GamepadInputBinding is a constructor for the class that initializes an instance of GamepadInputBinding.
 * @param Name The name of the input binding, represented as a string_view reference.
 * @param axes Axes represents the axes of the gamepad input.
 * @param type Type represents the type of the binding (e.g., KeyBoard, Mouse).
 */
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
		/**
 * @brief Destructor for the GamepadInputBinding class.
 *
 * This function is responsible for freeing any resources that were allocated during the lifetime of an instance of this class.
 */
~GamepadInputBinding() override = default;

		/**
 * @brief GetKey returns the key value based on the binding type.
 * 
 * This function checks the m_BindingType and returns different values depending on its state. If it's an Axis, it returns the m_Axes value. If it's an Action, it returns the m_Button value. For all other cases, it returns UINT16_MAX to indicate an error or invalid state.
 * 
 * @return uint16_t The key value based on the binding type.
 */
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
		/**
 * @brief Default constructor for the GamepadInputBinding class.
 *
 * This function initializes a new instance of the GamepadInputBinding class with default values. It does not take any parameters and returns nothing.
 */
GamepadInputBinding() = default;
	};

	struct KBMInputBinding : public InputBinding
	{
		/**
 * @brief Constructs a new instance of KBMInputBinding.
 * 
 * This constructor initializes the binding with the given name and type, setting default values for other members.
 * 
 * @param Name The name of the input binding.
 * @param type The type of the input binding (Keyboard, Mouse etc.).
 */
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
		/**
 * @brief Constructs a new KBMInputBinding object.
 * 
 * This constructor initializes the binding with a given name, keycode, and type. It also sets some default values for other members of the class.
 * 
 * @param Name The name of the binding.
 * @param keycode The key code associated with this binding.
 * @param type The type of the binding (e.g., KeyPress, KeyRelease).
 */
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

		/**
 * @brief Destructor for the KBMInputBinding class.
 *
 * This function is responsible for releasing any resources that were acquired during the lifetime of this object, such as memory or file handles. It also ensures that all subclasses have a well-defined destructor to follow the Rule of 5 (copy constructor, copy assignment operator, move constructor, move assignment operator and destructor).
 *
 * @return void
 */
~KBMInputBinding() override = default;

		/**
 * @brief This function returns a key code based on the binding type.
 * 
 * The function checks the value of m_BindingType and returns different values depending on its state. If it's an Axis, it returns UINT16_MAX as placeholder for future implementation. If it's an Action, it returns the value stored in m_Key. For all other cases, it again returns UINT16<｜begin▁of▁sentence｜>MAX.
 * 
 * @return uint16_t The key code to be returned based on the binding type.
 */
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
		/**
 * @brief Default constructor for KBMInputBinding class.
 */
KBMInputBinding() = default;
	};
} // AGE

#endif //AGE_INPUTBINDING_H