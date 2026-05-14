//
// Created by gdmgp on 12/3/2025.
//

//#include "AGEpch.hpp"
#include "../Public/WidgetStack.h"


namespace AGE
{
	/**
 * @brief Pushes a ScriptableWidget to the front of the stack.
 * 
 * This function takes a reference to a ScriptableWidget and pushes it onto the front of the m_Widgets list. The widget is added at the beginning of the list, so it will be the next one to be popped off the stack.
 * @param Widget A reference to the ScriptableWidget that should be pushed onto the stack.
 */
/** 
 * @brief Pushes a ScriptableWidget to the front of the stack.
 * 
 * This function takes in a reference to a ScriptableWidget and pushes it to the front of the m_Widgets list. The widget is added at the beginning of the list, so it will be the next one to be popped off the stack if PopNextWidgetFromStack() is called.
 * 
 * @param Widget A reference to a ScriptableWidget that you want to push onto the stack.
 * @return void No return value.
 */
void WidgetStack::PushWidgetToStack(Ref<ScriptableWidget> Widget)
	{
		m_Widgets.emplace_front(Widget);
	}

	/**
 * @brief Removes the first widget from the stack.
 * 
 * This function removes the front element of the m_Widgets list, effectively popping the topmost widget off the stack.
 * If there are no widgets in the stack, this function does nothing and has no effect.
 */
/** 
 * @brief Removes the first widget from the stack.
 *
 * This function removes the frontmost element of the m_Widgets list, effectively "popping" the top-most widget off the stack.
 * If the stack is empty, this operation has no effect.
 */
void WidgetStack::PopWidgetFromStack()
	{
		m_Widgets.pop_front();
	}

	/**
 * @brief This function updates the topmost widget in the stack based on a given time step.
 * 
 * @param DeltaTime The amount of time that has passed since the last update.
 * 
 * @return void
 */
/**
 * @brief This function updates the top widget in the stack based on a given time step.
 * 
 * The function checks if there are any widgets in the stack (i.e., m_Widgets size is greater than 0). If so, it calls the OnUpdate() method for the frontmost widget with the provided DeltaTime. This allows the top widget to be updated based on time elapsed since the last frame.
 * 
 * @param DeltaTime The time step representing the amount of time that has passed since the last update.
 * 
 * @return void
 */
void WidgetStack::OnTopUpdate(TimeStep DeltaTime)
	{
		if (m_Widgets.size() > 0)
		{
			m_Widgets.front()->OnUpdate(DeltaTime);
		}
	}

	/**
 * @brief Activates the widget at the front of the stack by setting its visibility to true.
 * 
 * This function uses a member variable `m_Widgets`, which is assumed to be a container storing pointers to Widget objects. The front element of this container (i.e., the first added widget) is activated by calling the SetVisibility method on it with an argument of true. 
 *
 * @return void
 */
/**
 * @brief Activates the widget at the front of the stack by setting its visibility to true.
 * 
 * This function uses a member variable `m_Widgets`, which is assumed to be a container storing pointers to Widget objects. The front element of this container (i.e., the first added widget) will have its visibility set to true using the `SetVisibility(true)` method.
 * 
 * @return void
 */
void WidgetStack::ActivateWidget() {
		m_Widgets.front()->SetVisibility(true);
	}

	/**
 * @brief Deactivates the widget at the front of the stack by setting its visibility to false.
 *
 * This function removes the first element from the m_Widgets vector and sets its visibility to false, effectively deactivating it. 
 * If the stack is empty, this function does nothing.
 */
/**
 * @brief Deactivates the widget at the front of the stack by setting its visibility to false.
 *
 * This function removes the first widget from the stack and sets its visibility to false, effectively deactivating it. 
 * If there are no widgets in the stack, this function does nothing.
 */
void WidgetStack::DeactivateWidget() {
		m_Widgets.front()->SetVisibility(false);
	}
} // AGE