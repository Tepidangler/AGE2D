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
    VerticalBoxComponent::VerticalBoxComponent(const std::string &Name) {
        m_Name = Name;
        m_Type = UIComponentType::VerticalBoxComponent;
    }

    void VerticalBoxComponent::OnUpdate(TimeStep DeltaTime)
    {
        UIComponent::OnUpdate(DeltaTime);
    }

    void VerticalBoxComponent::OnEvent(Event &Event) {
    }

    void VerticalBoxComponent::DrawContent() {
    }
} // AGE