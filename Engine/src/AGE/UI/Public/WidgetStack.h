//
// Created by gdmgp on 12/3/2025.
//

#pragma once
#ifndef AGE2D_WIDGETSTACK_H
#define AGE2D_WIDGETSTACK_H
#include "UI/Public/ScriptableWidget.h"
#include "Core/Public/Core.h"
#include "Core/Public/DeltaTime.h"

namespace AGE
{
	class WidgetStack
	{
	public:
		/**
 * @brief Default constructor for the WidgetStack class.
 * This function initializes an instance of the WidgetStack class with its members set to their default values.
 *
 * @return An instance of the WidgetStack class with all member variables initialized to their default values.
 */
/**
 * @brief Default constructor for the WidgetStack class.
 * This function initializes a new instance of the WidgetStack class with an empty stack.
 *
 * @return A new instance of the WidgetStack class.
 */
WidgetStack() = default;
		/**
 * @brief Destructor for the WidgetStack class.
 *
 * This destructor is used to clean up any resources that were allocated during the lifetime of an object of this class.
 * It does not perform any specific actions related to the WidgetStack class, but serves as a standard way to define and document such a destructor in Doxygen.
 * 
 * @return Nothing is returned as it's a destructor.
 */
/**
 * @brief Destructor for the WidgetStack class.
 *
 * This destructor is used to clean up any resources that were allocated during the lifetime of an object of this class.
 * It does not perform any specific operations related to the WidgetStack class itself, but serves as a standard way to define and document such a destructor in Doxygen.
 *
 * @return void
 */
~WidgetStack() = default;

		void PushWidgetToStack(Ref<ScriptableWidget> Widget);
		void PopWidgetFromStack();

		/**
 * @brief This function returns the active widget from the list of widgets.
 * @return A reference to the first element in the m_Widgets vector, which is the active widget. If the vector is empty, it will return a default-constructed Ref<ScriptableWidget> object.
 */
/**
 * @brief Retrieves the active widget from the list of widgets.
 * @return A reference to the frontmost widget in the list. If there are no widgets, a default-constructed Ref<ScriptableWidget> is returned.
 */
Ref<ScriptableWidget> GetActiveWidget() {return m_Widgets.front();}

		void OnTopUpdate(TimeStep DeltaTime);

		void ActivateWidget();
		void DeactivateWidget();

		/**
 * @brief Returns an iterator pointing to the beginning of the deque container storing ScriptableWidget objects.
 * @return An iterator that points to the start of the deque.
 */
/**
 * @brief Returns an iterator pointing to the beginning of the deque container storing ScriptableWidget objects.
 * @return An iterator pointing to the first element in the deque. If the deque is empty, the returned iterator will be equal to end().
 */
std::deque<Ref<ScriptableWidget>>::iterator begin() {return m_Widgets.begin();}
		/**
 * @brief Returns an iterator pointing to the past-the-end element in the deque container.
 * @return An iterator pointing to the past-the-end element of the sequence controlled by the deque object. 
 */
/**
 * @brief Returns an iterator pointing to the past-the-end element in the deque container.
 * @return An iterator to the past-the-end of the sequence controlled by the deque object.
 */
std::deque<Ref<ScriptableWidget>>::iterator end() {return m_Widgets.end();}
		/**
 * @brief Returns a constant iterator pointing to the beginning of the deque of ScriptableWidget objects.
 * @return A constant iterator pointing to the first element in the deque, or end() if the deque is empty.
 */
/**
 * @brief Returns a constant iterator pointing to the beginning of the deque.
 * @details This function returns a constant iterator that points to the first element in the deque 'm_Widgets'. 
 * The returned iterator can be used to access and traverse all elements from the start of the deque.
 * @return A constant iterator pointing to the beginning of the deque.
 */
std::deque<Ref<ScriptableWidget>>::const_iterator begin() const {return m_Widgets.cbegin();}
		/**
 * @brief Returns a constant iterator pointing to the past-the-end element of the deque container.
 * @return A constant iterator pointing to the past-the-end element in the container.
 */
/**
 * @brief Returns a constant iterator pointing to the past-the-end element of the deque container.
 * @return A constant iterator pointing to the past-the-end element in the container.
 */
std::deque<Ref<ScriptableWidget>>::const_iterator end() const {return m_Widgets.cend();}


	private:
		std::deque<Ref<ScriptableWidget>> m_Widgets;
		Entity m_Entity;
	};
} // AGE

#endif //AGE2D_WIDGETSTACK_H