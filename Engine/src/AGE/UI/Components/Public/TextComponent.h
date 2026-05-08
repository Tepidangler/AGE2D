//
// Created by gdmgp on 12/5/2025.
//

#ifndef AGE2D_TEXTCOMPONENT_H
#define AGE2D_TEXTCOMPONENT_H
#pragma once
#include "Core/Public/Core.h"
#include "Render/Public/Font.h"
#include "Serializers/Public/DataWriter.h"
#include "Serializers/Public/DataReader.h"
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnontrivial-memcall"
#include <imgui.h>
#pragma clang diagnostic pop
#endif

#include "UI/Public/UiComponent.h"


namespace AGE
{
	class TextComponent : public UIComponent
	{
	public:
		TextComponent(const std::string& Name);
		StringProperties m_StringProperties;
		void OnUpdate(TimeStep DeltaTime) override;
		void OnEvent(Event& Event) override;
		/**
 * @brief This function serializes the TextComponent object using a DataWriter.
 * 
 * The function writes the current instance of the TextComponent to the provided DataWriter, which can be used for further processing or storage.
 * 
 * @param Serializer A pointer to an instance of DataWriter that will handle the writing operation.
 * 
 * @return void No return value is expected as this function directly writes data using the provided DataWriter.
 */
void CallSerialize(DataWriter* Serializer) override
		{
			Serializer->WriteObject<TextComponent>(*this);
		}
		/**
 * @brief Deserializes the TextComponent from a DataReader.
 * 
 * This function reads an instance of TextComponent from the provided DataReader and assigns it to this object.
 * The exact format in which the data is read depends on how the DataReader's ReadObject method is implemented.
 *
 * @param Serializer A pointer to a DataReader that provides the serialized data.
 */
void CallDeserialize(DataReader* Serializer) override
		{
			Serializer->ReadObject<TextComponent>(*this);
		}
		void DrawFontSelectionComboBox() override;
		void DrawContent() override;

		/**
 * @brief This function serializes a TextComponent instance into the provided DataWriter.
 * 
 * The function writes several properties of the TextComponent to the DataWriter, including its name, type, string properties (text, font name), color, font size, and position/rotation.
 * 
 * @param Serializer A pointer to a DataWriter instance that will be used for serialization.
 * @param Instance The TextComponent instance to be serialized.
 */
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