//
// Created by gdmgp on 2/1/2026.
//

#ifndef AGE2D_VERTICALBOXCOMPONENT_H
#define AGE2D_VERTICALBOXCOMPONENT_H
#include "UI/Public/UiComponent.h"

namespace AGE
{
	class VerticalBoxComponent : public UIComponent
	{
	public:
		VerticalBoxComponent(const std::string& Name);
		void OnUpdate(TimeStep DeltaTime) override;
		void OnEvent(Event& Event) override;

		/**
 * @brief This function serializes the VerticalBoxComponent object.
 * 
 * The function writes the current state of the VerticalBoxComponent object to a DataWriter instance, which can be used for further processing or storage.
 * 
 * @param Serializer A pointer to the DataWriter instance that will handle the serialization process.
 * 
 * @return void No return value is expected as this function only writes data and does not return any result.
 */
/** 
 * @brief This function is used to serialize the VerticalBoxComponent object.
 * 
 * @param Serializer A pointer to a DataWriter object, which provides methods for writing data.
 * 
 * @return None
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
 * @brief This function is used to deserialize data from a DataReader object. 
 * It reads an object of type VerticalBoxComponent into the current instance of the class.
 * 
 * @param Serializer A pointer to the DataReader object that contains the serialized data.
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

#endif //AGE2D_VERTICALBOXCOMPONENT_H