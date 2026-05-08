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
		/**
 * @brief Constructor for RendererChangeEvent class.
 *
 * This constructor initializes the member variable `m_Window` with a given WindowsWindow object.
 *
 * @param Window Pointer to a WindowsWindow object.
 */
RendererChangeEvent(WindowsWindow* Window)
			: m_Window(Window) {}


		/**
 * @brief Returns the reference to the window object.
 *
 * This function returns a pointer to the window object that is currently being used by this class instance. The returned value can be null if no valid window has been set yet.
 * 
 * @return Pointer to the current WindowsWindow object, or nullptr if none exists.
 */
inline WindowsWindow* GetWindow() const { return m_Window; }

		/**
 * @brief This function returns a string representation of the current object's state.
 * The returned string includes information about the renderer change, using the Utils::ConvertAPIToString() function to convert an API enum value into its corresponding string representation.
 * 
 * @return std::string A string containing the details about the renderer change.
 */
std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Renderer Changed: " << Utils::ConvertAPIToString();
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
		/**
 * @brief RenderUIEvent is a function that takes in a TimeStep as an argument and assigns it to the member variable m_DeltaTime.
 * 
 * @param DeltaTime The time step for rendering UI events.
 */
RenderUIEvent(TimeStep DeltaTime)
			:m_DeltaTime(DeltaTime){}

		COMMENT:
/**
 * @brief This function returns the time difference between two frames in the game world.
 * @return The time difference as a TimeStep object. If no previous frame exists, it will return an Unknown TimeStep.
 */
CONFIDENCE: 1.0;

inline TimeStep GetDeltaTime() const { return m_DeltaTime; }
		TimeStep m_DeltaTime;
		EVENT_CLASS_TYPE(RenderUI)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}