#pragma once

#include "Core.h"
#include "Events/Public/Event.h"
#include "Core/Public/DeltaTime.h"



namespace AGE
{
	

class AGE_API Layer
	{
	public:

		Layer(const std::string& name = "Layer");

		virtual ~Layer();

		virtual void Init() {};

		/**
 * @brief This function is called when the object is attached to a scene or game world.
 * 
 * @return void
 */
/**
 * @brief This function is called when the component is attached to a scene.
 * 
 * @return void
 */
virtual void OnAttach() {}
		
		/**
 * @brief Detaches the component from its parent.
 *
 * This function is called when a component is detached from its parent. It provides an opportunity for any necessary cleanup or notification to be done before the component is completely removed from use.
 * 
 * @return void
 */
/**
 * @brief Detaches the component from its parent.
 *
 * This function is called when a component is detached from its parent. It provides an opportunity for any necessary cleanup or notification to be done.
 *
 * @return void
 */
virtual void OnDetach() {}
		
		/**
 * @brief This function is called every frame to update the game state.
 *
 * @param DeltaTime The time elapsed since the last frame, used for smooth movement and animation.
 * @return void No return value expected as this function does not have a return statement.
 */
/**
 * @brief This function is called every frame to update the game state based on the elapsed time since the last call.
 * 
 * @param DeltaTime The time step between the current and previous frames, used to calculate how much of an effect should be applied.
 */
virtual void OnUpdate(TimeStep DeltaTime) {} 

		/**
 * @brief This function is called every frame to render the ImGUI interface.
 * 
 * @param[in] DeltaTime The time step for the current frame, indicating how much time has passed since the last frame.
 * @return void No return value expected as this function does not return any result.
 */
/**
 * @brief This function is called every frame to render the ImGui interface.
 * 
 * @param[in] DeltaTime The time step for the current frame, indicating how much time has passed since the last frame.
 */
virtual void OnImGuiRender(TimeStep DeltaTime) {}
		
		/**
 * @brief This function is called when an event occurs.
 *
 * The function takes a reference to an Event object as its parameter, which contains information about the event that occurred.
 * It does not return anything (void).
 *
 * @param[in] Event - A reference to an Event object containing details about the event.
 */
/**
 * @brief This function is called when an event occurs.
 *
 * @param Event The event that has occurred.
 */
virtual void OnEvent(Event& Event) {}

		float GetTime();

		/**
 * @brief Returns the name of this object.
 *
 * This function returns a reference to a string that represents the name of this object. The returned value is constant and does not allow modification.
 *
 * @return A const reference to the debug name of this object.
 */
/**
 * @brief Returns the name of this object.
 * @return A constant reference to a string containing the debug name.
 */
inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}