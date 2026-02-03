//
// Created by gdmgp on 2/1/2026.
//

#ifndef AGE2D_HORIZONTALBOXCOMPONENT_H
#define AGE2D_HORIZONTALBOXCOMPONENT_H
#include "UI/Public/UiComponent.h"

namespace AGE
{
	class HorizontalBoxComponent : public UIComponent
	{
	public:
		HorizontalBoxComponent(const std::string& Name);
		void OnEvent(Event& Event) override;

		void CallSerialize(DataWriter* Serializer) override
		{
			//Serializer->WriteObject<VerticalBoxComponent>(*this);
		}
		void CallDeserialize(DataReader* Serializer) override
		{
			//Serializer->ReadObject<VerticalBoxComponent>(*this);
		}
		void DrawContent() override;

		RTTR_ENABLE(UIComponent)
		RTTR_REGISTRATION_FRIEND

	private:

		std::vector<UIComponent> m_Components;
	};
} // AGE

#endif //AGE2D_HORIZONTALBOXCOMPONENT_H