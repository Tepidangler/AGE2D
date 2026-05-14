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
		void OnUpdate(TimeStep DeltaTime) override;
		void OnEvent(Event& Event) override;

		/**
 * @brief This function serializes the VerticalBoxComponent object.
 * 
 * The function writes the state of this object to a DataWriter, which can be used for saving or transmitting data.
 * It uses the WriteObject method from the provided Serializer to write the object's data.
 * 
 * @param[in] Serializer A pointer to an instance of DataWriter that is responsible for writing the serialized data.
 */
/**
 * @brief This function serializes the VerticalBoxComponent object.
 * 
 * The function writes the current state of the VerticalBoxComponent object to a DataWriter instance, which can be used for further processing or storage.
 * 
 * @param Serializer A pointer to an instance of DataWriter that will handle the serialization process.
 */
void CallSerialize(DataWriter* Serializer) override
		{
			//Serializer->WriteObject<VerticalBoxComponent>(*this);
		}
		/**
 * @brief This function is used to deserialize data from a DataReader object. 
 * It reads an object of type VerticalBoxComponent using the provided Serializer.
 * 
 * @param[in] Serializer A pointer to the DataReader object that will be used for deserialization.
 */
/**
 * @brief Deserializes the VerticalBoxComponent from a DataReader.
 * 
 * This function reads an object of type VerticalBoxComponent from the provided DataReader. The exact behavior depends on how the DataReader is implemented and what it can handle.
 * 
 * @param Serializer A pointer to the DataReader that provides the serialized data.
 * @return void No return value expected.
 */
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