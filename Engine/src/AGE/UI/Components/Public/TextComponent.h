//
// Created by gdmgp on 12/5/2025.
//

#ifndef AGE2D_TEXTCOMPONENT_H
#define AGE2D_TEXTCOMPONENT_H
#pragma once
#include "Core/Public/Core.h"
#include "Render/Public/Font.h"
#include "UI/Public/UiComponent.h"
#include "Serializers/Public/DataWriter.h"
#include "Serializers/Public/DataReader.h"
#include <imgui.h>


namespace AGE
{
	class TextComponent : public UIComponent
	{
	public:
		TextComponent(const std::string& Name);
		StringProperties m_StringProperties;
		void OnUpdate(TimeStep DeltaTime) override;

		void DrawFontSelectionComboBox() override;
		void DrawContent() override;

		static void Serialize(DataWriter* Serializer, const TextComponent& Instance)
		{
			Serializer->WriteString(Instance.m_Name);
			Serializer->WriteRaw<uint16_t>(Instance.m_Type);
			Serializer->WriteString(Instance.m_StringProperties.Text);
			Serializer->WriteString(Instance.m_StringProperties.FontName);
			Serializer->WriteRaw<float>(Instance.m_StringProperties.Color.x);
			Serializer->WriteRaw<float>(Instance.m_StringProperties.Color.y);
			Serializer->WriteRaw<float>(Instance.m_StringProperties.Color.z);
			Serializer->WriteRaw<float>(Instance.m_StringProperties.Color.w);
			Serializer->WriteRaw<double>(Instance.m_StringProperties.FontSize);
			Serializer->WriteRaw<float>(Instance.m_StringProperties.Position.x);
			Serializer->WriteRaw<float>(Instance.m_StringProperties.Position.y);
			Serializer->WriteRaw<float>(Instance.m_StringProperties.Position.z);
			Serializer->WriteRaw<float>(Instance.m_StringProperties.Rotation.x);
			Serializer->WriteRaw<float>(Instance.m_StringProperties.Rotation.y);
			Serializer->WriteRaw<float>(Instance.m_StringProperties.Rotation.z);
		}

		static void Deserialize(DataReader* Serializer, TextComponent& Instance)
		{
			Serializer->ReadString(Instance.m_Name);
			uint16_t Type;
			Serializer->ReadRaw<uint16_t>(Type);
			Instance.m_Type = (UIComponentType::Value)Type;
			Serializer->ReadString(Instance.m_StringProperties.Text);
			Serializer->ReadString(Instance.m_StringProperties.FontName);
			Serializer->ReadRaw<float>(Instance.m_StringProperties.Color.x);
			Serializer->ReadRaw<float>(Instance.m_StringProperties.Color.y);
			Serializer->ReadRaw<float>(Instance.m_StringProperties.Color.z);
			Serializer->ReadRaw<float>(Instance.m_StringProperties.Color.w);
			Serializer->ReadRaw<double>(Instance.m_StringProperties.FontSize);
			Serializer->ReadRaw<float>(Instance.m_StringProperties.Position.x);
			Serializer->ReadRaw<float>(Instance.m_StringProperties.Position.y);
			Serializer->ReadRaw<float>(Instance.m_StringProperties.Position.z);
			Serializer->ReadRaw<float>(Instance.m_StringProperties.Rotation.x);
			Serializer->ReadRaw<float>(Instance.m_StringProperties.Rotation.y);
			Serializer->ReadRaw<float>(Instance.m_StringProperties.Rotation.z);
		}

		RTTR_ENABLE(UIComponent)
		RTTR_REGISTRATION_FRIEND
	};
} // AGE

#endif //AGE2D_TEXTCOMPONENT_H