#pragma once
#include "Core/Public/Core.h"
#include "Event.h"

namespace AGE 
{
	/**
 * @brief Represents a window resize event.
 * 
 * This class is used to represent a window resize event, which includes the width and height of the resized window.
 */
class AGE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int Width, unsigned int Height)
			: m_Width(Width), m_Height(Height) {}


		/**
 * @brief Returns the width of the object.
 *
 * This function returns the current value of the private member variable 'm_Width'. It provides a way to access and retrieve the width of an object.
 *
 * @return unsigned int The current width of the object. If no width is set, it will return 0.
 */
inline unsigned int GetWidth() const { return m_Width; }
		/**
 * @brief Returns the height of an object.
 *
 * This function is used to get the current height value of an object. It returns an unsigned integer representing the height.
 *
 * @return The current height of the object as an unsigned int. If no height has been set, it will return 0.
 */
inline unsigned int GetHeight() const { return m_Height; }

		/**
 * @brief This function returns a string representation of the WindowResizeEvent object.
 * The returned string includes the width and height of the window that was resized.
 * 
 * @return A string containing the details about the event, such as the new width and height of the window.
 */
std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};

	/**
 * @brief Represents a framebuffer resize event.
 * 
 * This class is used to represent a framebuffer resize event, which occurs when the size of the framebuffer changes. It contains two parameters - width and height that specify the new dimensions of the framebuffer.
 */
class AGE_API FramebufferResizeEvent : public Event
	{
	public:
		FramebufferResizeEvent(unsigned int Width, unsigned int Height)
			: m_Width(Width), m_Height(Height) {}


		/**
 * @brief Returns the width of the object.
 * @return The width as an unsigned integer.
 */
inline unsigned int GetWidth() const { return m_Width; }
		/**
 * @brief Returns the height of an object.
 *
 * This function is used to get the current height value of an object. It returns an unsigned integer representing the height.
 *
 * @return The current height of the object as an unsigned int.
 */
inline unsigned int GetHeight() const { return m_Height; }

		/**
 * @brief Converts the FramebufferResizeEvent into a string format.
 *
 * This function converts the FramebufferResizeEvent object into a string representation, 
 * which includes the width and height of the framebuffer that was resized.
 *
 * @return A string containing the details about the event.
 */
std::string ToString() const override
		{
			std::stringstream ss;
			ss << "FramebufferResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(FramebufferResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};

	class AGE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AGE_API WindowFocusEvent : public Event
	{
	public:

		WindowFocusEvent() {}

		EVENT_CLASS_TYPE(WindowFocus)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AGE_API WindowLostFocusEvent : public Event
	{
	public:

		WindowLostFocusEvent() {}

		EVENT_CLASS_TYPE(WindowLostFocus)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AGE_API WindowMovedEvent : public Event
	{
	public:

		WindowMovedEvent() {}

		EVENT_CLASS_TYPE(WindowMoved)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};


	class AGE_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

	class AGE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AGE_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/**
 * @brief Represents a string copy event. This event is triggered when a string is copied to the clipboard.
 * 
 * @param String The string that was copied.
 */
class AGE_API StringCopyEvent : public Event
	{
	public:
		StringCopyEvent(const char* String)
			: m_String(String) {}


		/**
 * @brief This function returns a pointer to the string stored in the object.
 * @return A constant character pointer to the internal string of this object.
 */
inline const char* GetString() { return m_String; }

		/**
 * @brief This function returns a string representation of the event.
 * The returned string includes details about what string was copied to the clipboard, and is formatted as such.
 * 
 * @return A string containing information about the copy event.
 */
std::string ToString() const override
		{
			std::stringstream ss;
			ss << "String Copy Event: " << m_String << " was copied to clipboard";
			return ss.str();
		}

		EVENT_CLASS_TYPE(StringCopy)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		const char* m_String;

	};

	/**
 * @brief Represents a string paste event. This event is triggered when a string is pasted from the clipboard.
 * 
 * @param String The string that was pasted.
 */
class AGE_API StringPasteEvent : public Event
	{
	public:
		StringPasteEvent(const char* String)
			: m_String(String) {}


		/**
 * @brief This function returns a pointer to the string stored in the object.
 * @return A constant character pointer pointing to the internal string of the object. If no string is set, it will return nullptr.
 */
inline const char* GetString() { return m_String; }

		/**
 * @brief This function returns a string representation of the event.
 * The returned string includes details about what string was pasted and from where (clipboard).
 * 
 * @return std::string A string containing information about the paste event.
 */
std::string ToString() const override
		{
			std::stringstream ss;
			ss << "String Paste Event: " << m_String << " was pasted from clipboard";
			return ss.str();
		}

		EVENT_CLASS_TYPE(StringPaste)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		const char* m_String;
	};

	class ProjectCreatedEvent : public Event
	{
	public:
		/**
 * @brief Default constructor for ProjectCreatedEvent class.
 */
ProjectCreatedEvent(){}

		EVENT_CLASS_TYPE(ProjectCreated)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	class ProjectLoadedEvent : public Event
	{
	public:
		/**
 * @brief Default constructor for ProjectLoadedEvent class.
 */
ProjectLoadedEvent(){}

		EVENT_CLASS_TYPE(ProjectLoaded)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}