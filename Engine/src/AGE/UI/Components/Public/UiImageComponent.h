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

		/**
 * @brief Virtual destructor for the UIImageComponent class.
 *
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime. It does not take any parameters and returns no value.
 */
virtual ~UIImageComponent() = default;

		/**
 * @brief This function is used to serialize data using a DataWriter object.
 * 
 * The function takes in a pointer to a DataWriter object as its parameter. It does not return anything, so the return type should be void.
 * 
 * @param Serializer A pointer to a DataWriter object that will handle the serialization process.
 */
void CallSerialize(DataWriter* Serializer) override
		{
		}
		/**
 * @brief This function is used to call the deserialization process on a DataReader object.
 * 
 * The function takes in a pointer to a DataReader object as its parameter. It does not return anything, so it's void type.
 * 
 * @param Serializer A pointer to a DataReader object that will be used for the deserialization process.
 */
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