#pragma once
#include "Core/Public/Core.h"
#include "Event.h"

#include "Scene/Public/Scene.h"

namespace AGE
{

	class InputEvent : public Event
	{
		/**
 * @brief Retrieves the gamepad button state.
 *
 * This function is used to get the current state of a gamepad button. It returns an integer representing the state of the button, which could be either pressed or not pressed. 
 *
 * @return An integer value indicating the state of the gamepad button. If the button is pressed, it will return 1; if not, it will return 0.
 */
inline int GetGamepadButton() { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryGame)

	protected:
		InputEvent();
		/**
 * @brief Constructs an InputEvent object with the specified axis and position.
 * @param Axis The input event's axis.
 * @param Position The input event's position on the axis.
 */
InputEvent(int Axis, float Position)
			:m_Axis(Axis), m_Position(Position) {}
		/**
 * @brief Constructor for the InputEvent class.
 *
 * This constructor initializes an instance of the InputEvent class with a specific button value.
 *
 * @param Button The integer representation of the input event's button.
 */
InputEvent(int Button)
			: m_Button(Button) {}

	protected:
		int m_Axis;
		float m_Position;
		int m_Button;
	};

	class AxisEvent : public InputEvent
	{
	public:
		/**
 * @brief Constructs an instance of the AxisEvent class with specified axis and position.
 * 
 * This constructor creates a new instance of the AxisEvent class by initializing its base class (InputEvent) with the provided axis and position values.
 * 
 * @param Axis The identifier for the input event's associated physical axis.
 * @param Position The current position of the physical axis in relation to its origin point.
 */
AxisEvent(int Axis, float Position)
			: InputEvent(Axis, Position) {}

		/**
 * @brief This function returns the value of the member variable 'm_Axis'.
 * @return The integer value stored in 'm_Axis'
 */
inline int GetAxis() { return m_Axis; }
		/**
 * @brief This function returns the current position value.
 *
 * @return A floating-point number representing the current position.
 */
inline float GetPosition() { return m_Position; }
		EVENT_CLASS_TYPE(AxisMoved)
	};

	class GamepadButtonPressedEvent : public InputEvent
	{
	public:
		/**
 * @brief Constructor for the GamepadButtonPressedEvent class.
 *
 * This constructor creates a new instance of the GamepadButtonPressedEvent class with the specified button number. It inherits from the InputEvent base class.
 * 
 * @param Button The button number that was pressed on the gamepad.
 */
GamepadButtonPressedEvent(int Button)
			:InputEvent(Button) {}

		/**
 * @brief Returns the value of member variable 'm_Button'.
 * @return The current state of button represented by integer.
 */
inline int GetButton() { return m_Button; }
		EVENT_CLASS_TYPE(GamepadButtonPressed)
	};

	class GamepadButtonReleasedEvent : public InputEvent
	{
	public:
		/**
 * @brief Constructor for the GamepadButtonReleasedEvent class.
 *
 * This constructor is used to create a new instance of the GamepadButtonReleasedEvent class, which represents an event signifying that a gamepad button has been released. 
 * The specific button associated with this event is passed as an argument during instantiation.
 *
 * @param Button An integer representing the ID of the gamepad button that was released.
 */
GamepadButtonReleasedEvent(int Button)
			:InputEvent(Button) {}

		/**
 * @brief Returns the current state of the button.
 *
 * This function returns the current state of the button which can be either pressed or not pressed.
 * The returned value is an integer where 0 represents the button being not pressed and any other number represents it being pressed.
 *
 * @return int - Current state of the button (0 for not pressed, non-zero for pressed).
 */
inline int GetButton() { return m_Button; }
		EVENT_CLASS_TYPE(GamepadButtonReleased)
	};

	class SceneEvent : public Event
	{
		EVENT_CLASS_CATEGORY(EventCategoryGame)
		protected:
		/**
 * @brief Constructs a new instance of the SceneEvent class with the given scene.
 * @param Scene The scene to be associated with this event.
 */
SceneEvent(Ref<Scene> Scene)
			:m_Scene(Scene) {}

	protected:
		Ref<Scene> m_Scene;
	};

	class SceneChangedEvent : public SceneEvent
	{
		public:
		/**
 * @brief Constructs a new instance of the SceneChangedEvent class with the given scene reference.
 * 
 * @param Scene The scene that has changed.
 */
SceneChangedEvent(Ref<Scene> Scene)
			:SceneEvent(Scene){}

		/**
 * @brief Returns the current scene object.
 *
 * This function returns a reference to the currently active scene in the application. The returned Scene object can be used for various operations such as rendering, updating, and managing game objects within the scene.
 *
 * @return A reference to the current scene.
 */
inline Ref<Scene> GetScene() {return m_Scene;}
		EVENT_CLASS_TYPE(SceneChanged)
	};
}
