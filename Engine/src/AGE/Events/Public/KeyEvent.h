#pragma once
#include "Core/Public/Core.h"
#include "Event.h"


namespace AGE
{
	/**
 * @brief Represents a keyboard event.
 *
 * This class is used to represent a keyboard event, which includes the key code associated with the event.
 */
class AGE_API KeyEvent : public Event
	{
	public:
		
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		
	protected:
		
		KeyEvent(int KeyCode)
			: m_KeyCode(KeyCode) {}

		int m_KeyCode;
	};

	
class AGE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int KeyCode, int RepeatCount)
			: KeyEvent(KeyCode), m_RepeatCount(RepeatCount) {}

		/**
 * @brief Returns the repeat count of a certain process or operation.
 * @return The number of times the process or operation is repeated, as an integer value. If the function fails to retrieve the data, it returns -1.
 */
inline int GetRepeatCount() const { return m_RepeatCount; }

		/**
 * @brief Converts the event into a string representation.
 * 
 * This function converts the KeyPressedEvent object into a string format that includes the key code and repeat count of the event.
 * The resulting string is returned by this method.
 * 
 * @return A string in the format "KeyPressedEvent: [keycode] ([repeatcount] repeats)".
 */
std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
			
	private:
		int m_RepeatCount;
	};

	class AGE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int KeyCode)
			: KeyEvent(KeyCode) {}

		/**
 * @brief Converts the event to a string representation.
 *
 * This function converts the KeyReleasedEvent into a string format that includes information about the key code of the released key. 
 * The resulting string is returned by this method.
 *
 * @return A string representing the KeyReleasedEvent in the format "KeyReleasedEvent: <key_code>".
 */
std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

			EVENT_CLASS_TYPE(KeyReleased)
	};

	/**
 * @brief Represents a Key Typed Event in the system.
 * 
 * This class extends the base KeyEvent class and represents an event where a key has been typed into the system. It provides a method to convert this event into a string representation.
 */
class AGE_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int KeyCode)
			: KeyEvent(KeyCode) {}

		/**
 * @brief Converts the event into a string format.
 *
 * This function converts the KeyTypedEvent object into a string format that includes the key code of the event. 
 * The resulting string is returned by this method.
 *
 * @return A string representation of the KeyTypedEvent object, including the key code.
 */
std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}