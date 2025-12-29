//
// Created by gdmgp on 12/5/2025.
//

#ifndef AGE2D_TEXTBOXCOMPONENT_H
#define AGE2D_TEXTBOXCOMPONENT_H
#pragma once
#include "Core/Public/Core.h"
#include "Render/Public/Font.h"
#include "UI/Public/UiComponent.h"
#include "Serializers/Public/DataWriter.h"
#include "Serializers/Public/DataReader.h"

namespace AGE
{
	class TextBoxComponent : public UIComponent
	{
	public:
		TextBoxComponent(const std::string& Name);
		StringProperties m_StringProperties;
		BoxProperties m_BoxProperties;
		void OnUpdate(TimeStep DeltaTime) override;

		void DrawFontSelectionComboBox() override;
		void DrawContent() override;

		RTTR_ENABLE(UIComponent)
		RTTR_REGISTRATION_FRIEND
	};
} // AGE

#endif //AGE2D_TEXTBOXCOMPONENT_H