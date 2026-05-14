//
// Created by gdmgp on 2/1/2026.
//

#include "../Public/HorizontalBoxComponent.h"
RTTR_REGISTRATION{
    rttr::registration::class_<AGE::HorizontalBoxComponent>("HorizontalBoxComponent")
    .constructor<const std::string&>()
    .method("OnUpdate", &AGE::HorizontalBoxComponent::OnUpdate);
    //.property("Children", &AGE::HorizontalBoxComponent::m_Components)(rttr::metadata("Description", "Child components attached to this box"));
}
namespace AGE
{
    /**
 * @brief Constructs a HorizontalBoxComponent with the given name.
 * 
 * This constructor initializes a new instance of HorizontalBoxComponent with the provided name and sets its type to UIComponentType::HorizontalBoxComponent.
 * 
 * @param Name The name for this component.
 */
/**
 * @brief Constructs a HorizontalBoxComponent with the given name.
 * 
 * This function initializes a new instance of HorizontalBoxComponent with the provided name and sets its type to UIComponentType::HorizontalBoxComponent.
 * 
 * @param Name The name for this component.
 */
HorizontalBoxComponent::HorizontalBoxComponent(const std::string &Name)
    {
        m_Name = Name;
        m_Type = UIComponentType::HorizontalBoxComponent;
    }

    /**
 * @brief This function updates the component based on a given time step. 
 * It calls the base class's OnUpdate method to handle any common updates, and then performs its own specific update logic.
 * 
 * @param DeltaTime The amount of time that has passed since the last frame.
 */
/** 
 * @brief This function updates the component based on a given time step.
 * 
 * The function first calls the OnUpdate method of its base class, UIComponent, to handle any general updates that might be necessary. Then it performs any specific updates related to this HorizontalBoxComponent itself.
 * 
 * @param DeltaTime The time step for the update. This is used to calculate how much to move or change the component based on the elapsed time since the last frame.
 */
void HorizontalBoxComponent::OnUpdate(TimeStep DeltaTime)
    {
        UIComponent::OnUpdate(DeltaTime);
    }

    /**
 * @brief Handles an event of type Event.
 *
 * This function is responsible for processing the incoming event and updating the state of the component accordingly.
 *
 * @param[in] Event The event to be processed.
 */
/**
 * @brief Handles an event of type Event.
 *
 * This function is responsible for handling the incoming events and updating the state of the component accordingly.
 *
 * @param[in] Event The event to be handled.
 */
void HorizontalBoxComponent::OnEvent(Event &Event) {
    }

    /**
 * @brief Draw the content of this component in a horizontal layout.
 *
 * This function draws the content of this component in a horizontal layout, which means that all child components are arranged horizontally from left to right. 
 * The exact arrangement and size of each child component depends on their respective sizes and positions specified by their layout parameters.
 *
 * @return void
 */
/**
 * @brief Draw the content of this component in a horizontal layout.
 *
 * This function draws the content of this component in a horizontal layout, which means that all child components are laid out horizontally from left to right. 
 * The exact visual representation may depend on various factors such as the size and position of the parent container and the individual properties of each child component.
 *
 * @return void
 */
void HorizontalBoxComponent::DrawContent() {
    }
} // AGE