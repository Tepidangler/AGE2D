#pragma once
#include "Core/Public/Core.h"
#include "Event.h"
#include "Core/Public/Window.h"
#include "Render/Public/RenderAPI.h"

namespace AGE
{
	class RendererChangeEvent : public Event
	{
	public:
		/**
 * @brief Constructor for RendererChangeEvent class.
 *
 * This constructor initializes the RendererChangeEvent object with a reference to an AGEWindow instance.
 * It is used to handle changes in the renderer of the provided window.
 *
 * @param Window Pointer to an AGEWindow instance representing the window whose renderer will be changed.
 */
RendererChangeEvent(AGEWindow* Window)
			: m_Window(Window) {}


		/**
 * @brief Returns the window object associated with this class instance.
 * @return Pointer to an AGEWindow object representing the current window.
 */
inline AGEWindow* GetWindow() const { return m_Window; }

		/**
 * @brief Converts the Renderer object to a string representation.
 *
 * This function returns a string that represents the current state of the Renderer object, including its type and any relevant details. 
 * The returned string is formatted as "Renderer Changed: [Utils::ConvertAPIToString()]", where [Utils::ConvertAPIToString()] represents the result of Utils::ConvertAPIToString().
 *
 * @return A string representation of the Renderer object.
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
		AGEWindow* m_Window;
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

		/**
 * @brief This function returns the time difference between two frames in the game world.
 * @return The time difference as a TimeStep object.
 */
inline TimeStep GetDeltaTime() const { return m_DeltaTime; }
		TimeStep m_DeltaTime;
		EVENT_CLASS_TYPE(RenderUI)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}