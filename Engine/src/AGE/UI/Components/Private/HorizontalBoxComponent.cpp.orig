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
void HorizontalBoxComponent::DrawContent() {
    }
} // AGE