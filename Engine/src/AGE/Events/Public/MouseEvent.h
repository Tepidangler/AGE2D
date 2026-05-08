#pragma once
#include "Core/Public/Core.h"
#include "Event.h"


namespace AGE
{
	
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
inline float GetX() const { return m_MouseX; }
		/**
 * @brief This function returns the current value of member variable 'm_MouseY'.
 * @return A floating-point number representing the y-coordinate.
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
inline float GetXOffset() const { return m_XOffset; }
		/**
 * @brief This function returns the Y offset value.
 * @return A floating-point number representing the Y offset.
 */
inline float GetYOffset() const { return m_YOffset; }

		/**
 * @brief This function returns a string representation of the MouseScrolledEvent object.
 * The returned string includes the x and y offsets that represent the scroll event.
 * 
 * @return A string containing the details about the mouse scrolling event.
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
std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}