//
// Created by gdmgp on 12/29/2025.
//

#ifndef AGE2D_UISTRUCTS_H
#define AGE2D_UISTRUCTS_H

#include <string>
#include "Core/Public/Core.h"
#include "Math/Public/Vector3.h"
#include "Math/Public/Vector4.h"
#include "Texture/Public/Texture.h"

namespace AGE
{
	template<typename ... Callable>
	struct UIVisitor : Callable...
	{
		using Callable::operator()...;
	};

	struct UIComponentType
	{
		enum Value : uint16_t
		{
			TextComponent,TextBoxComponent,
			HorizontalBoxComponent,VerticalBoxComponent,
			ButtonComponent,
			ImageComponent
		};

		/**
 * @brief Default constructor for the UIComponentType class.
 */
UIComponentType() = default;
		 COMMENT:
/**
 * @brief Constructs a UIComponentType object with the given Value and sets its Name to the string representation of the Value.
 * @param Val The value to be used for initialization.
 */
CONFIDENCE: 1.0;

UIComponentType(Value Val)
			: value(Val)
		{
			Name = ToString(value);

		}

		/**
 * @brief Returns the current value of the object.
 *
 * This function returns the stored value in a constant expression. It is used to get the current value of the object without modifying it.
 *
 * @return The current value of the object as a Value type.
 */
constexpr operator Value() const {return value;}

		explicit operator bool() const = delete;

		/**
 * @brief Compares the current UIComponentType with another one for equality.
 *
 * This function compares the 'value' member of this instance with that of the provided UIComponentType object. It returns true if they are equal, and false otherwise.
 *
 * @param a The UIComponentType to compare against.
 * 
 * @return True if the current UIComponentType is equal to the input one, False otherwise.
 */
constexpr bool operator==(UIComponentType a) const
		{
			return value == a.value;
		}

		/**
 * @brief Compares the current UIComponentType instance with another one for inequality.
 *
 * This function compares the 'value' member of this instance with that of the provided UIComponentType instance. 
 * It returns true if they are not equal, and false otherwise.
 *
 * @param a The UIComponentType instance to compare with.
 * @return True if the values are not equal, false otherwise.
 */
constexpr bool operator!=(UIComponentType a) const
		{
			return value != a.value;
		}

		/**
 * @brief Converts the object to a string representation of its name.
 *
 * This function returns the `Name` member variable as a string. It is used for converting an object into a string format.
 * 
 * @return std::string The name of the object.
 */
operator std::string()  const
		{
			return Name;
		}
		/**
 * @brief Converts a Value to its string representation.
 *
 * This function takes in a Value and returns its string representation using the ToString() function.
 * 
 * @param Val The Value to be converted to a string.
 * @return A string representing the input Value.
 */
std::string operator()(Value Val)  const
		{
			return ToString(Val);
		}

		/**
 * @brief Returns the Value object stored in the function.
 * 
 * This function is used to return the 'value' variable of type Value that was previously set elsewhere in the code.
 * It does not take any parameters and returns a single Value object.
 * 
 * @return The Value object stored in the function.
 */
Value ToValue()
		{
			return value;
		}
		/**
 * @brief This function returns the Value object 'value'.
 * 
 * @return The Value object that is being returned by this function.
 */
Value ToValue() const
		{
			return value;
		}

		/**
 * @brief Returns a reference to the object's name string.
 * 
 * This function returns a reference to the internal `Name` member variable of the class instance. It is used for getting and setting the value of the name attribute.
 * 
 * @return A reference to the Name string.
 */
std::string& ToString()
		{
			return Name;
		}

		/**
 * @brief This function returns the name of an object as a string.
 * 
 * @return std::string The name of the object.
 */
std::string ToString() const
		{
			return Name;
		}

		/**
 * @brief Converts a Value enum to its corresponding string representation.
 * 
 * This function takes in a Value enum and returns the string equivalent of it. The possible values are "TextComponent", "TextBoxComponent", "HorizontalBoxComponent", "VerticalBoxComponent", "ButtonComponent" and "ImageComponent". If the input is not one of these, an empty string is returned.
 * 
 * @param Val Value enum to be converted.
 * @return String representation of the Value enum.
 */
std::string ToString(Value Val)
		{
			switch(Val)
			{
				case TextComponent:
				{
					return "TextComponent";
					break;
				}
				case TextBoxComponent:
				{
					return "TextBoxComponent";
					break;
				}
				case HorizontalBoxComponent: {
					return "HorizontalBoxComponent";
					break;
				}
				case VerticalBoxComponent: {
					return "VerticalBoxComponent";
					break;
				}
				case ButtonComponent: {
					return "ButtonComponent";
					break;
				}
				case ImageComponent: {
					return "ImageComponent";
					break;
				}
				default:
				{
					break;
				}
			}

			return std::string();
		}

		/**
 * @brief Converts an enumeration value to its corresponding string representation.
 * 
 * This function takes as input an enumerated type Value and returns a string that corresponds to the enum value. The possible values of the enum are TextComponent, TextBoxComponent, HorizontalBoxComponent, VerticalBoxComponent, ButtonComponent, and ImageComponent. If the input is not one of these values, the function will return an empty string.
 * 
 * @param Val An enumerated type Value to be converted into a string.
 * @return A string representation of the enum value. Returns an empty string if the input is not recognized.
 */
std::string ToString(Value Val) const
		{
			switch(Val)
			{
				case TextComponent:
				{
					return "TextComponent";
					break;
				}
				case TextBoxComponent:
				{
					return "TextBoxComponent";
					break;
				}
				case HorizontalBoxComponent: {
					return "HorizontalBoxComponent";
					break;
				}
				case VerticalBoxComponent: {
					return "VerticalBoxComponent";
					break;
				}
				case ButtonComponent: {
					return "ButtonComponent";
					break;
				}
				case ImageComponent: {
					return "ImageComponent";
					break;
				}
				default:
				{
					break;
				}
			}
			return std::string();

		}

		/**
 *  @brief This function serializes a UIComponentType instance into the provided DataWriter.
 *  
 *  The function writes the name of the component and its value to the writer, which can be used for further processing or storage.
 *  
 *  @param Serializer Pointer to an object that implements the DataWriter interface. This is where the serialized data will be written.
 *  @param Instance The UIComponentType instance to be serialized. Contains the name and value of the component.
 *  
 *  @return None
 */
static void Serialize(DataWriter* Serializer, const UIComponentType& Instance)
		{
			Serializer->WriteString(Instance.Name);
			Serializer->WriteRaw<uint16_t>(Instance.value);
		}

		/**
 * @brief Deserialize function for the UIComponentType class.
 * 
 * This function reads a string and a Value from the provided DataReader instance, which are expected to be populated with data in some way (like reading from a file or network). The read values are then used to set the Name and value properties of the passed-in UIComponentType instance.
 * 
 * @param Serializer A pointer to an initialized DataReader instance.
 * @param Instance An uninitialized UIComponentType instance that will be populated with data from the Serializer.
 * 
 * @return void
 */
static void Deserialize(DataReader* Serializer, UIComponentType& Instance)
		{
			Serializer->ReadString(Instance.Name);
			Serializer->ReadRaw<Value>(Instance.value);
		}


	private:
		Value value;
		std::string Name = "";
	};

	struct UIProperties
	{
		/**
 * @brief Default constructor for UIProperties class.
 */
UIProperties() = default;
		Vector3 Position = Vector3(0.f);
		Vector3 Rotation = Vector3(0.f);
		Vector3 Scale = Vector3(1.f);
		bool Visible = true;
		bool Focused = false;
	};

	struct BoxProperties
	{
		/**
 * @brief Default constructor for the BoxProperties class.
 */
BoxProperties() = default;
		Vector3 Position = Vector3(0.f);
		Vector3 Rotation = Vector3(0.f);
		Vector3 Scale = Vector3(1.f);
		Vector4 TintColor = {1.f};
		Ref<Texture> BoxTexture = nullptr;
	};
}
#endif //AGE2D_UISTRUCTS_H