#pragma once
#include "Core/Public/Core.h"
#include "Event.h"
#include "Platform/Windows/Public/WindowsWindow.h"
#include "Render/Public/RenderAPI.h"

namespace AGE
{
	class RendererChangeEvent : public Event
	{
	public:
		RendererChangeEvent(WindowsWindow* Window)
			: m_Window(Window) {}


		inline WindowsWindow* GetWindow() const { return m_Window; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Renderer Changed: " << AGE::Utils::ConvertAPIToString();
			return ss.str();
		}

		EVENT_CLASS_TYPE(RendererChanged)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		WindowsWindow* m_Window;
	};
}