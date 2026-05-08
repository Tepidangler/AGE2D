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
 * @brief Default constructor for UIComponentType class.
 */
UIComponentType() = default;
		 /**
 * @brief Constructs a UIComponentType object with the given Value and sets its Name to the string representation of the Value.
 * 
 * @param Val The value to be used for initialization.
 */
UIComponentType(Value Val)
			: value(Val)
		{
			Name = ToString(value);

		}

		/**
 * @brief Returns the current value of the object.
 *
 * This function returns the stored value in a constant time operation. It is used to get the current state of the object without altering it.
 *
 * @return The current value of the object.
 */
constexpr operator Value() const {return value;}

		explicit operator bool() const = delete;

		/**
 * @brief Compares the current UIComponentType with another one for equality.
 *
 * This function compares the 'value' member of this UIComponentType instance with that of another given UIComponentType instance. 
 * It returns true if both instances have the same value, and false otherwise.
 *
 * @param a The UIComponentType instance to compare against.
 * @return True if the current UIComponentType has the same 'value' as the input parameter, False otherwise.
 */
constexpr bool operator==(UIComponentType a) const
		{
			return value == a.value;
		}

		/**
 * @brief Compares the UIComponentType object with another one for inequality.
 *
 * This function compares the 'value' member of this UIComponentType object with that of another given UIComponentType object. 
 * It returns true if they are not equal, and false otherwise.
 *
 * @param a The UIComponentType object to compare with.
 * @return True if the objects are not equal, false otherwise.
 */
constexpr bool operator!=(UIComponentType a) const
		{
			return value != a.value;
		}

		/**
 * @brief Converts the object to a string representation.
 *
 * This function returns the name of the object as a string. The conversion is explicit, meaning it must be called with 
 * parentheses following the object (e.g., `objectName = (std::string)object;`).
 *
 * @return A std::string containing the name of the object.
 */
operator std::string()  const
		{
			return Name;
		}
		/**
 * @brief Converts a Value to its string representation.
 *
 * This function takes in a Value and converts it into its string representation using the ToString() function. 
 * The result is then returned as a std::string.
 *
 * @param Val The Value to be converted.
 * @return A std::string representing the input Value.
 */
std::string operator()(Value Val)  const
		{
			return ToString(Val);
		}

		/**
 * @brief This function returns the stored Value object.
 * 
 * @return The Value object that is currently being held by this instance of the class.
 */
Value ToValue()
		{
			return value;
		}
		/**
 * @brief This function returns the Value object 'value' of the class instance.
 * 
 * @return The Value object 'value'.
 */
Value ToValue() const
		{
			return value;
		}

		/**
 * @brief This function returns a reference to the 'Name' string object.
 * 
 * @return A reference to the 'Name' string object.
 */
std::string& ToString()
		{
			return Name;
		}

		/**
 * @brief Converts the object into a string representation.
 * 
 * This function returns a string that represents the current state of this object. The format and content of the returned string are implementation-dependent.
 * 
 * @return std::string A string representing the current state of this object.
 */
std::string ToString() const
		{
			return Name;
		}

		/**
 * @brief Converts a Value enum to its corresponding string representation.
 * 
 * This function takes in a Value enum and returns the string equivalent of it. The possible values are "TextComponent", "TextBoxComponent", "HorizontalBoxComponent", "VerticalBoxComponent", "ButtonComponent" and "ImageComponent". If the input does not match any of these, an empty string is returned.
 * 
 * @param Val Value enum to convert.
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
 * @brief Converts a Value enum to its corresponding string representation.
 * 
 * This function takes in a Value enum and returns the string equivalent of it. The possible values are "TextComponent", "TextBoxComponent", "HorizontalBoxComponent", "VerticalBoxComponent", "ButtonComponent" and "ImageComponent". If the input does not match any of these, an empty string is returned.
 * 
 * @param Val Value enum to be converted.
 * @return String representation of the Value enum.
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
 *  @return void No return value expected.
 */
static void Serialize(DataWriter* Serializer, const UIComponentType& Instance)
		{
			Serializer->WriteString(Instance.Name);
			Serializer->WriteRaw<uint16_t>(Instance.value);
		}

		/**
 * @brief Deserialize function for a UIComponentType instance.
 * 
 * This function reads the Name and value fields from the provided DataReader into an existing UIComponentType instance.
 * 
 * @param Serializer The DataReader to read data from.
 * @param Instance The UIComponentType instance to deserialize into.
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
		Vector3 Position = {0.f};
		Vector3 Rotation = {0.f};
		Vector3 Scale = {1.f};
		bool Visible = true;
		bool Focused = false;
	};

	struct BoxProperties
	{
		/**
 * @brief Default constructor for BoxProperties class.
 */
BoxProperties() = default;
		Vector3 Position = {0.f};
		Vector3 Rotation = {0.f};
		Vector3 Scale = {1.f};
		Vector4 TintColor = {1.f};
		Ref<Texture> BoxTexture = nullptr;
	};
}
#endif //AGE2D_UISTRUCTS_H