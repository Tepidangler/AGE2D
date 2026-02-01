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

	class RenderUIEvent : public Event
	{
	public:
		RenderUIEvent(TimeStep DeltaTime)
			:m_DeltaTime(DeltaTime){}

		inline TimeStep GetDeltaTime() const { return m_DeltaTime; }
		TimeStep m_DeltaTime;
		EVENT_CLASS_TYPE(RenderUI)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}