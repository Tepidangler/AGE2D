//
// Created by gdmgp on 12/5/2025.
//

#ifndef AGE2D_TEXTBOXCOMPONENT_H
#define AGE2D_TEXTBOXCOMPONENT_H
#pragma once
#include "Core/Public/Core.h"
#include "Render/Public/Font.h"
#include "Serializers/Public/DataWriter.h"
#include "Serializers/Public/DataReader.h"

#include "UI/Public/UiComponent.h"

namespace AGE
{
	class TextBoxComponent : public UIComponent
	{
		RTTR_ENABLE(UIComponent)
		RTTR_REGISTRATION_FRIEND
	public:
		TextBoxComponent(const std::string& Name);
		StringProperties m_StringProperties;
		BoxProperties m_BoxProperties;
		void OnUpdate(TimeStep DeltaTime) override;
		void OnEvent(Event& Event) override;

		void DrawFontSelectionComboBox() override;
		void DrawContent() override;
		/**
 * @brief This function serializes the TextBoxComponent object using a DataWriter.
 * 
 * @param[in] Serializer A pointer to an instance of DataWriter that is used for writing data.
 */
/**
 * @brief This function serializes the TextBoxComponent object into a DataWriter.
 * 
 * @param[in] Serializer A pointer to the DataWriter instance where the object will be written.
 */
void CallSerialize(DataWriter* Serializer) override
		{
			Serializer->WriteObject<TextBoxComponent>(*this);
		}
		/**
 * @brief Deserializes the TextBoxComponent from a DataReader.
 * 
 * This function reads an instance of TextBoxComponent from the provided DataReader and assigns it to this object.
 * The exact format in which the data is read depends on how the DataReader's ReadObject method is implemented.
 *
 * @param Serializer A pointer to a DataReader that provides the serialized data.
 */
/** 
 * @brief This function is used to deserialize a TextBoxComponent from the provided DataReader.
 * 
 * @param Serializer A pointer to an instance of DataReader, which provides the serialized data.
 * @return void No return value as it directly modifies the state of the current object (TextBoxComponent).
 */
void CallDeserialize(DataReader* Serializer) override
		{
			Serializer->ReadObject<TextBoxComponent>(*this);
		}

		/**
 * @brief Serializes the TextBoxComponent instance into a DataWriter object.
 * 
 * This function writes various properties of the TextBoxComponent to the provided DataWriter, including its name, type, string properties (text, font name, color and size), and position and rotation data.
 * 
 * @param Serializer Pointer to the DataWriter instance where serialization will be performed.
 * @param Instance The TextBoxComponent instance that needs to be serialized.
 * 
 * @return void
 */
/**
 * @brief This function serializes the TextBoxComponent instance into a DataWriter object.
 * 
 * The function writes various properties of the TextBoxComponent, such as its name, type, string properties (text, font name, color and size), and position and rotation data.
 * 
 * @param Serializer Pointer to the DataWriter object where serialized data will be written into.
 * @param Instance The TextBoxComponent instance that needs to be serialized.
 * 
 * @return void
 */
static void Serialize(DataWriter* Serializer, const TextBoxComponent& Instance)
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

		/**
 * @brief Deserializes the TextBoxComponent instance from a DataReader object.
 * 
 * This function reads various properties of the TextBoxComponent instance, including its name, type, string properties (text, font name, color and size), and position and rotation data. It uses the provided Serializer to read these values.
 * 
 * @param[in] Serializer A pointer to a DataReader object that provides the serialized data.
 * @param[out] Instance The TextBoxComponent instance to be deserialized.
 */

static void Deserialize(DataReader* Serializer, TextBoxComponent& Instance)
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

	};
} // AGE

#endif //AGE2D_TEXTBOXCOMPONENT_H