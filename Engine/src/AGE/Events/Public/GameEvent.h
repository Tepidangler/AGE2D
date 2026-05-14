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
/**
 * @brief Retrieves the gamepad button state.
 *
 * This function returns the current state of the gamepad button. The returned value is an integer representing the state of the button, which could be a combination of various flags indicating different states such as pressed or released. 
 *
 * @return An integer representing the current state of the gamepad button.
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
/**
 * @brief Constructs an instance of the AxisEvent class with specified axis and position.
 * 
 * This constructor creates a new instance of the AxisEvent class by initializing its base class (InputEvent) with the provided axis and position values.
 * 
 * @param Axis The identifier for the input event's associated physical axis, such as an x-axis or y-axis.
 * @param Position The current position on the specified axis. This could be a value between -1.0 and 1.0, representing full left to right movement.
 * 
 * @return An instance of AxisEvent with the provided axis and position values.
 */
AxisEvent(int Axis, float Position)
			: InputEvent(Axis, Position) {}

		/**
 * @brief This function returns the value of the member variable 'm_Axis'.
 * @return The integer value stored in 'm_Axis'
 */
/**
 * @brief This function returns the current axis value.
 *
 * @return The integer value of the current axis.
 */
inline int GetAxis() { return m_Axis; }
		/**
 * @brief This function returns the current position value.
 *
 * @return A floating-point number representing the current position.
 */
/**
 * @brief Returns the current position value.
 * 
 * This function retrieves and returns the current position value stored in the member variable 'm_Position'.
 * The returned value represents a float representing the position of an object or entity.
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
/**
 * @brief Constructs a GamepadButtonPressedEvent object with the specified button number.
 * 
 * This constructor creates an instance of GamepadButtonPressedEvent that represents a button press event on a gamepad device. The button parameter specifies which button was pressed.
 * 
 * @param Button An integer representing the button number that was pressed.
 */
GamepadButtonPressedEvent(int Button)
			:InputEvent(Button) {}

		/**
 * @brief Returns the value of member variable 'm_Button'.
 * @return The current state of button represented by integer.
 */
/**
 * @brief Returns the current state of the button.
 * @return The current state of the button as an integer.
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
/**
 * @brief Constructs a GamepadButtonReleasedEvent object with the specified button number.
 * 
 * This constructor creates an instance of GamepadButtonReleasedEvent that represents a gamepad button release event. The button number is passed as an argument to this function, which will be used by the InputEvent base class for processing the event.
 * 
 * @param Button An integer representing the button number that was released.
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
/**
 * @brief Returns the current state of the button.
 * @return The current state of the button as an integer. If the button is pressed, it returns 1; if not, it returns 0.
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
/**
 * @brief Constructs a new instance of the SceneEvent class with the given scene.
 * @param Scene The reference to the scene that this event is associated with.
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
/**
 * @brief Constructs a new instance of the SceneChangedEvent class with the given scene.
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
/**
 * @brief Returns the current scene object.
 *
 * This function retrieves and returns the currently active Scene object, which is stored in the member variable 'm_Scene'. The returned reference can be used to manipulate or access the properties of this Scene object.
 *
 * @return A reference to the current Scene object.
 */
inline Ref<Scene> GetScene() {return m_Scene;}
		EVENT_CLASS_TYPE(SceneChanged)
	};
}
