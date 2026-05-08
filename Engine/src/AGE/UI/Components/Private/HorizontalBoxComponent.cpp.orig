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
    HorizontalBoxComponent::HorizontalBoxComponent(const std::string &Name)
    {
        m_Name = Name;
        m_Type = UIComponentType::HorizontalBoxComponent;
    }

    void HorizontalBoxComponent::OnUpdate(TimeStep DeltaTime)
    {
        UIComponent::OnUpdate(DeltaTime);
    }

    void HorizontalBoxComponent::OnEvent(Event &Event) {
    }

    void HorizontalBoxComponent::DrawContent() {
    }
} // AGE