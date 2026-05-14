//
// Created by gdmgp on 12/3/2025.
//

#ifndef AGE2D_WIDGET_H
#define AGE2D_WIDGET_H
#include "Core/Public/Core.h"
#include "Serializers/Public/DataReader.h"
#include "Serializers/Public/DataWriter.h"
namespace AGE
{
	class ScriptableWidget;

	struct Widget
	{
		/**
 * @brief This function serializes a widget object into a data writer.
 * 
 * @param[in] Serializer Pointer to the data writer where the widget will be written.
 * @param[in] Data The widget that needs to be serialized.
 */
/**
 * @brief This function serializes a widget object into a data writer.
 * 
 * The function takes in two parameters - a pointer to a DataWriter and a constant reference to a Widget. It does not return anything, hence the void return type.
 * 
 * @param Serializer A pointer to an instance of DataWriter that will be used for serialization.
 * @param Data A constant reference to the Widget object that needs to be serialized.
 */
static void Serialize(DataWriter* Serializer, const Widget& Data)
		{

		}

		/**
 * @brief This function deserializes data from a serialized format into an instance of the Widget class.
 * 
 * The function takes in a pointer to a DataReader object and a reference to a Widget object. It does not return anything, but it modifies the Widget object by filling its fields with data read from the DataReader.
 * 
 * @param Serializer A pointer to an instance of the DataReader class that provides the serialized data.
 * @param Data A reference to an instance of the Widget class where the deserialized data will be stored.
 */
/**
 * @brief This function deserializes data from a serialized format into an object of type Widget.
 * 
 * The function takes in a pointer to a DataReader and a reference to a Widget object. It does not return anything, but it modifies the Widget object by filling its fields with data read from the DataReader.
 * 
 * @param Serializer A pointer to an instance of DataReader that provides the serialized data.
 * @param Data The Widget object to be filled with deserialized data.
 */
static void Deserialize(DataReader* Serializer, Widget& Data)
		{

		}

		ScriptableWidget* Instance = nullptr;
		ScriptableWidget* (*InstantiateScript)();
		void (*DestroyScript)(Widget*);

		template<typename T>
		/**
 * @brief Binds a lambda function to instantiate an instance of class T.
 *        Also binds another lambda function for destroying the instance of Widget.
 * 
 * The first lambda function creates a new instance of class T and casts it to ScriptableWidget*.
 * The second lambda function deletes the instance of Widget, then sets its Instance pointer to nullptr.
 */
/**
 * @brief Binds a lambda function to create an instance of type T and another lambda function to destroy it.
 * 
 * This function sets the InstantiateScript lambda to a new function that creates a new instance of type T using static_cast. It also sets DestroyScript lambda to delete the Widget's instance and set it to nullptr.
 * 
 * @return void
 */
void Bind()
		{
			InstantiateScript = []() {return static_cast<ScriptableWidget*>(new T()); };
			DestroyScript = [](Widget* WC) {delete WC->Instance; WC->Instance = nullptr; };
		}

	};
} // AGE

#endif //AGE2D_WIDGET_H