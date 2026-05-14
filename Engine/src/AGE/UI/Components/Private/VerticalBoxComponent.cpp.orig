//
// Created by gdmgp on 2/1/2026.
//

#include "../Public/VerticalBoxComponent.h"

RTTR_REGISTRATION{
    rttr::registration::class_<AGE::VerticalBoxComponent>("VerticalBoxComponent")
    .constructor<const std::string&>()
    .method("OnUpdate", &AGE::VerticalBoxComponent::OnUpdate);
    //.property("Children", &AGE::VerticalBoxComponent::m_Components)(rttr::metadata("Description", "Child components attached to this box"));
}

namespace AGE
{
    /**
 * @brief Constructs a VerticalBoxComponent with the given name.
 * 
 * This function initializes a new instance of VerticalBoxComponent with the provided name and sets its type to VerticalBoxComponentType.
 * 
 * @param Name The name for this component.
 */
VerticalBoxComponent::VerticalBoxComponent(const std::string &Name) {
        m_Name = Name;
        m_Type = UIComponentType::VerticalBoxComponent;
    }

    /**
 * @brief This function updates the component based on a time step.
 * 
 * The function first calls the base class's OnUpdate() method with the provided delta time, which allows for any necessary cleanup or other tasks to be performed before the update process begins. It then continues with its own specific update logic.
 * 
 * @param DeltaTime - A TimeStep object representing the amount of time that has passed since the last frame.
 */
void VerticalBoxComponent::OnUpdate(TimeStep DeltaTime)
    {
        UIComponent::OnUpdate(DeltaTime);
    }

    /**
 * @brief Handles an event of type Event by updating the component's state accordingly.
 *
 * This function takes in a reference to an Event object and processes it based on its type. The exact behavior depends on the specific implementation of this class, which is not specified here.
 *
 * @param Event A reference to the Event object that needs to be processed.
 */
void VerticalBoxComponent::OnEvent(Event &Event) {
    }

    /**
 * @brief Draw the content of this component in a vertical layout.
 *
 * This function is responsible for drawing the content of the component in a vertical layout, which means that it will draw all its child components one after another vertically. 
 * It does not handle any specific styling or positioning of these child components. These are handled by their respective Draw methods.
 *
 * @return void
 */
void VerticalBoxComponent::DrawContent() {
    }
} // AGE