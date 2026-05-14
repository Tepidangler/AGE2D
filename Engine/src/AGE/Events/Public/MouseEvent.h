#pragma once
#include "Core/Public/Core.h"
#include "Event.h"


namespace AGE
{
	
/**
 * @brief Represents a mouse event. 
 * 
 * This class is used to represent different types of mouse events, such as button presses or scrolls. It provides methods for getting the type and position of the mouse event.
 */
class AGE_API MouseEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }
		
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseEvent(int Button)
			: m_Button(Button) {}

		/**
 * @brief Constructs a MouseEvent object with the given coordinates.
 * @param x The x-coordinate of the mouse event.
 * @param y The y-coordinate of the mouse event.
 */
/**
 * @brief Constructs a MouseEvent object with the given coordinates.
 * 
 * @param x The x-coordinate of the mouse event.
 * @param y The y-coordinate of the mouse event.
 */
MouseEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		/**
 * @brief Constructs a MouseEvent object with given offsets.
 * 
 * This function is used to create a new MouseEvent instance with the specified x and y offsets. The boolean Scrolled parameter is not actually utilized in this function, so it can be safely ignored for now.
 * 
 * @param xOffset The horizontal scroll offset.
 * @param yOffset The vertical scroll offset.
 * @param Scrolled A boolean indicating whether the mouse scrolled or not (not used).
 */
/**
 * @brief Constructs a MouseEvent object with given x and y offset values.
 * 
 * This constructor is used to create a new MouseEvent instance with the specified x and y offset values, which are then stored in member variables m_XOffset and m_YOffset respectively. The boolean Scrolled parameter is not utilized as it's not clear what its purpose would be without additional context or information about how this class is intended to be used.
 * 
 * @param xOffset The horizontal offset value for the mouse event.
 * @param yOffset The vertical offset value for the mouse event.
 * @param Scrolled A boolean indicating whether the scroll wheel was moved (not currently utilized).
 */
MouseEvent(float xOffset, float yOffset, bool Scrolled) // I can probably figure out a better way to do this, but it'll work for now since I won't ever actually be using the boolean
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

	protected:

		int m_Button;

		float m_MouseX;
		float m_MouseY;

		float m_XOffset;
		float m_YOffset;
	};

	class AGE_API MouseMovedEvent : public MouseEvent
	{
	public:
		
		MouseMovedEvent(float x, float y)
			: MouseEvent(x,y) {}

		/**
 * @brief Returns the current x-coordinate of the mouse cursor.
 * @return A floating point number representing the current x-coordinate of the mouse cursor.
 */
/**
 * @brief Returns the current x-coordinate of the mouse cursor.
 * @return The x-coordinate value as a floating point number. If there is an error in retrieving the data, it returns -1.0.
 */
inline float GetX() const { return m_MouseX; }
		/**
 * @brief This function returns the current value of member variable 'm_MouseY'.
 * @return A floating-point number representing the y-coordinate.
 */
/**
 * @brief This function returns the value of member variable 'm_MouseY'.
 * @return A floating-point number representing the current y-coordinate.
 */
inline float GetY() const { return m_MouseY; }

		/**
 * @brief Converts the event data into a string format.
 *
 * This function converts the mouse movement event data into a human-readable string format. 
 * The string includes the x and y coordinates of the mouse cursor at the time of the event.
 *
 * @return A string containing the details of the mouse movement event.
 */
/**
 * @brief This function returns a string representation of the MouseMovedEvent object.
 * The returned string includes the x and y coordinates of the mouse cursor at the time of the event.
 * 
 * @return A string in the format "MouseMovedEvent: <m_MouseX>, <m_MouseY>".
 */
std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
	};

	class AGE_API MouseScrolledEvent : public MouseEvent
	{
	public:
		
		MouseScrolledEvent(float xOffset, float yOffset)
			: MouseEvent(xOffset, yOffset, true) {}

		/**
 * @brief Returns the X offset value.
 *
 * This function returns the current X offset value stored in the object. The X offset is used to adjust the position of objects on the x-axis.
 *
 * @return A float representing the current X offset value.
 */
/**
 * @brief This function returns the X offset value.
 * @return A floating-point number representing the X offset.
 */
inline float GetXOffset() const { return m_XOffset; }
		/**
 * @brief This function returns the Y offset value.
 * @return A floating-point number representing the Y offset.
 */
/**
 * @brief This function returns the Y offset value.
 * @return A constant float representing the current Y offset value.
 */
inline float GetYOffset() const { return m_YOffset; }

		/**
 * @brief This function returns a string representation of the MouseScrolledEvent object.
 * The returned string includes the x and y offsets that represent the scroll event.
 * 
 * @return A string containing the details about the mouse scrolling event.
 */
/**
 * @brief Converts the MouseScrolledEvent into a string format.
 * 
 * The function constructs and returns a string representation of the MouseScrolledEvent object, which includes the x-offset and y-offset values.
 * 
 * @return A string containing the details about the MouseScrolledEvent.
 */
std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
	};

	class AGE_API MouseButtonPressedEvent : public MouseEvent
	{
	public:

		MouseButtonPressedEvent(int Button)
			: MouseEvent(Button) {}

		/**
 * @brief Converts the event to a string representation.
 *
 * This function converts the event into a human-readable format by appending the button value of the event to a base string. 
 * The resulting string is returned as output.
 *
 * @return A string representing the event in the format "MouseButtonPressedEvent: <button>".
 */
/**
 * @brief Converts the event to a string representation.
 *
 * This function converts the MouseButtonPressedEvent into a human-readable string format. 
 * It includes information about the button that was pressed in the event.
 *
 * @return A string containing the details of the event, such as "MouseButtonPressedEvent: ButtonName".
 */
std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	/**
 * @brief Represents a mouse button released event.
 *
 * This class inherits from the MouseEvent base class and is used to represent a specific type of event, which is a mouse button being released. 
 * The constructor takes an integer parameter representing the button that was released.
 * The ToString() method overrides the base class's pure virtual method and returns a string representation of this event.
 */
/**
 * @brief Represents a mouse button release event.
 *
 * This class represents a specific type of mouse event where a button is released. It includes details about the button that was released.
 */
class AGE_API MouseButtonReleasedEvent : public MouseEvent
	{
	public:

		MouseButtonReleasedEvent(int Button)
			: MouseEvent(Button) {}

		/**
 * @brief Converts the event to a string representation.
 *
 * This function converts the MouseButtonReleasedEvent into a human-readable string format. 
 * It includes details about the button that was released.
 *
 * @return A string containing the event type and the button that was released.
 */
/**
 * @brief Converts the event to a string representation.
 *
 * This function converts the MouseButtonReleasedEvent into a human-readable format by appending the button that was released. 
 * The resulting string is returned as output of this method.
 *
 * @return A string containing the details about the mouse button release event.
 */
std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}