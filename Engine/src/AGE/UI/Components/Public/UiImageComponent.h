//
// Created by gdmgp on 12/30/2025.
//

#ifndef AGE2D_UIIMAGECOMPONENT_H
#define AGE2D_UIIMAGECOMPONENT_H
#pragma once
#include "UI/Public/UiComponent.h"
#include "Texture/Public/Texture.h"

namespace AGE
{
	class UIImageComponent : public UIComponent
	{
	public:

		UIImageComponent(const std::string& Name);

		virtual ~UIImageComponent() = default;

		void CallSerialize(DataWriter* Serializer) override
		{
		}
		void CallDeserialize(DataReader* Serializer) override
		{
		}

		void OnUpdate(TimeStep DeltaTime) override;
		void OnEvent(Event& Event) override;
		void DrawContent() override;

		Ref<Texture2D> m_Image;
		std::string m_CurrentTexture;
		std::vector<std::string> m_TextureNames;
		QuadProperties m_Properties{};

		RTTR_ENABLE(UIComponent)
		RTTR_REGISTRATION_FRIEND
	};
} // AGE

#endif //AGE2D_UIIMAGECOMPONENT_H