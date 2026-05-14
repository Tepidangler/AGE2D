//
// Created by gdmgp on 2/1/2026.
//

#ifndef AGE2D_BUTTONCOMPONENT_H
#define AGE2D_BUTTONCOMPONENT_H
#pragma once
#include "Events/Public/KeyEvent.h"

#include "UI/Public/UiComponent.h"

namespace AGE
{
	class ButtonComponent : public UIComponent
	{
	public:
		ButtonComponent(const std::string& Name);

		void DrawContent() override;
		void OnUpdate(TimeStep DeltaTime) override;
		void OnEvent(Event& Event) override;
		/**
 * @brief This function is used to serialize the VerticalBoxComponent object.
 * 
 * @param[in] Serializer A pointer to a DataWriter object, which provides methods for writing data.
 * @return void No return value expected.
 */
/**
 * @brief This function serializes the VerticalBoxComponent object.
 * 
 * The function writes the data of this object into a DataWriter, which can be used for further processing or storage.
 * It uses the WriteObject method to write the specific type (VerticalBoxComponent) and the instance of this class (*this).
 *
 * @param Serializer A pointer to an instance of DataWriter that will handle the serialization process.
 */
void CallSerialize(DataWriter* Serializer) override
		{
			//Serializer->WriteObject<VerticalBoxComponent>(*this);
		}
		/**
 * @brief This function is used to deserialize data from a DataReader object. 
 * It reads an object of type VerticalBoxComponent using the provided serializer.
 *
 * @param Serializer A pointer to the DataReader object that will be used for deserialization.
 */
/** 
 * @brief This function is used to deserialize data from a DataReader object. It reads an object of type VerticalBoxComponent into the current instance of this class.
 * @param Serializer A pointer to the DataReader object that contains the serialized data.
 * @return None
 */
void CallDeserialize(DataReader* Serializer) override
		{
			//Serializer->ReadObject<VerticalBoxComponent>(*this);
		}
		/**
 * @brief Sets the on-click function for this object.
 *
 * This function sets a new function to be called when the object is clicked. The provided function should take no arguments and return void.
 *
 * @param func A std::function that will be set as the new click handler. It should have no parameters and return nothing.
 * 
 * @return None
 */
/**
 * @brief Sets the on-click function for this object.
 *
 * This function sets a new function to be called when the object is clicked. The provided function should take no arguments and return void.
 *
 * @param func A std::function that will be set as the new click handler. It should have no parameters and return nothing.
 */
void SetOnClickFunc(const std::function<void()>& func) { m_OnClick = func; }

		RTTR_ENABLE(UIComponent)
		RTTR_REGISTRATION_FRIEND

	protected:
		bool IsButtonHovered();

	private:
		bool OnKeyPressed(KeyPressedEvent& E);
		bool OnClicked(MouseButtonPressedEvent& E);

		bool bIsPressed = false;
		bool bIsHovered = false;

		BoxProperties m_BoxProperties;
		Vector2 m_Bounds[2]; // [lx,ly] [rx,ry]

		std::function<void()> m_OnClick;

	};
} // AGE

#endif //AGE2D_BUTTONCOMPONENT_H