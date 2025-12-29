#pragma once
#include "Core/Public/Core.h"
#include "Event.h"

namespace AGE 
{
	class AGE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int Width, unsigned int Height)
			: m_Width(Width), m_Height(Height) {}


		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

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

	class AGE_API FramebufferResizeEvent : public Event
	{
	public:
		FramebufferResizeEvent(unsigned int Width, unsigned int Height)
			: m_Width(Width), m_Height(Height) {}


		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

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

	class AGE_API StringCopyEvent : public Event
	{
	public:
		StringCopyEvent(const char* String)
			: m_String(String) {}


		inline const char* GetString() { return m_String; }

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

	class AGE_API StringPasteEvent : public Event
	{
	public:
		StringPasteEvent(const char* String)
			: m_String(String) {}


		inline const char* GetString() { return m_String; }

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
		ProjectCreatedEvent(){}

		EVENT_CLASS_TYPE(ProjectCreated)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	class ProjectLoadedEvent : public Event
	{
	public:
		ProjectLoadedEvent(){}

		EVENT_CLASS_TYPE(ProjectLoaded)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}