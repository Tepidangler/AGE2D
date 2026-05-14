#include "AGEpch.hpp"
#include "Scene/Public/ScriptableEntity.h"
#include "Core/Public/App.h"
#include <rttr/registration>

#include "VisualScripting/Public/VisualScriptingStructs.h"


namespace AGE
{
	/**
 * @brief Pushes this scriptable entity into the application's scriptable component stack.
 * 
 * This function pushes the current instance of ScriptableEntity (`this`) into the stack of scriptable components in the App class. It does not return anything, so its return type is void.
 */
/** 
 * @brief Pushes this scriptable entity into the application's scriptable component stack.
 * 
 * This function pushes a reference to this ScriptableEntity instance onto the stack of scriptable components in the App class. It is used when a new scriptable object needs to be added to the system.
 */
void ScriptableEntity::PushComp()
	{
		App::Get().PushScriptableComp(this);
	}
	namespace Utils
	{
		/**
 * @brief Converts a boolean value to its string representation.
 *
 * This function takes an AGEPinType and a boolean value as input, converts the boolean value into its string representation ("True" or "False"), 
 * and returns it along with the AGEPinType in a formatted string.
 *
 * @param Type The type of pin to be converted.
 * @param Value The boolean value to be converted.
 * @return The string representation of the input boolean value.
 */
/**
 * @brief Converts a boolean value to its string representation.
 *
 * This function takes an AGEPinType and a boolean value as input, converts the boolean value into its string representation ("True" or "False"), 
 * and returns it as a std::string.
 *
 * @param Type The type of pin that is being converted. This parameter does not contribute to the function's output but is included for context.
 * @param Value The boolean value to be converted into its string representation.
 * @return A std::string containing "True" if Value is true, and "False" otherwise.
 */
static std::string ConvertToString(AGEPinType Type, bool Value) { std::string RetVal = ""; RetVal = Value ? "True" : "False"; return RetVal;}
		/**
 * @brief Converts an integer value to a string.
 *
 * This function takes in two parameters, an AGEPinType and an int Value. It converts the int Value into a string using std::to_string() 
 * and returns it as a std::string. The purpose of this function is to provide a standardized way of converting integer values to strings for 
 * use in various parts of the AGE system.
 *
 * @param Type This parameter represents the type of pin that we are working with, but its actual meaning or functionality within the context 
 *              of the AGE system is not specified here as it's beyond the scope of this function's documentation.
 * @param Value The integer value to be converted into a string.
 *
 * @return Returns a std::string that represents the input integer Value in textual form. If the conversion fails, an empty string ("") is returned.
 */
/**
 * @brief Converts an integer value to a string.
 *
 * This function takes in two parameters, an enumeration of type AGEPinType and an integer Value. It converts the integer into a string representation using std::to_string() and returns it. 
 * The purpose of this conversion is typically for logging or debugging purposes where you might want to display the value as a string instead of its numeric representation.
 *
 * @param Type An enumeration representing different types of pins. This parameter does not contribute to the functionality of the function, but it provides context about what kind of pin the Value represents.
 * @param Value The integer value that will be converted into a string.
 * 
 * @return Returns a std::string representation of the input integer Value.
 */
static std::string ConvertToString(AGEPinType Type, int Value) { std::string RetVal = ""; RetVal = std::to_string(Value); return RetVal;}
		/**
 * @brief Converts a numeric value to string.
 *
 * This function takes an AGEPinType and an int16_t as input, converts the int16_t to a string using std::to_string(), 
 * and returns it. The purpose of this conversion is unknown at present.
 *
 * @param Type An enumeration value representing the type of pin being processed. This parameter's role in the function 
 *              is not clear from the context provided, so its documentation has been left as "Unknown".
 * @param Value A numeric value to be converted to a string.
 *
 * @return The input int16_t value as a string.
 */
/**
 * @brief Converts a numeric value to string.
 *
 * This function takes an AGEPinType and an int16_t as input, converts the int16_t to a string using std::to_string(), 
 * and returns this string. The purpose of this conversion is unknown at present.
 *
 * @param Type An enumeration value representing the type of pin being processed. This parameter's role in the function is not clear.
 * @param Value A numeric value to be converted to a string.
 * 
 * @return Returns a string representation of the input int16_t Value.
 */
static std::string ConvertToString(AGEPinType Type, int16_t Value) { std::string RetVal = ""; RetVal = std::to_string(Value); return RetVal;}
		/**
 * @brief Converts a numeric value to string.
 *
 * This function takes an AGEPinType and an int64_t as input, converts the int64_t to a string representation, 
 * and returns it. The purpose of this conversion is unknown at present.
 *
 * @param Type - The type of pin being converted. It's not clear what this parameter represents or its significance.
 * @param Value - The numeric value to be converted into a string.
 *
 * @return Returns the string representation of the input int64_t Value.
 */
/**
 * @brief Converts a value to string.
 *
 * This function takes an AGEPinType and an int64_t as input, converts the int64_t to a string representation, 
 * and returns it. The purpose of this conversion is unknown at present.
 *
 * @param Type - The type of pin being converted.
 * @param Value - The value to be converted to a string.
 * @return A string representation of the input value.
 */
static std::string ConvertToString(AGEPinType Type, int64_t Value) { std::string RetVal = ""; RetVal = std::to_string(Value); return RetVal;}
		/**
 * @brief Converts a numeric value to string.
 *
 * This function takes an AGEPinType and a uint16_t as input, converts the uint16_t to a string representation, 
 * and returns it. The purpose of this conversion is unknown at present.
 *
 * @param Type - The type of pin being converted. Not used in the conversion process.
 * @param Value - The numeric value to be converted to a string.
 *
 * @return A string representation of the input uint16_t value.
 */
/**
 * @brief Converts a numeric value to string.
 *
 * This function takes an AGEPinType and a uint16_t as input, converts the uint16_t to a string representation, 
 * and returns it. The purpose of this conversion is unknown at present.
 *
 * @param Type - The type of pin being converted. It's not clear what this parameter represents or its significance.
 * @param Value - The numeric value to be converted to a string.
 *
 * @return Returns the string representation of the input uint16_t value.
 */
static std::string ConvertToString(AGEPinType Type, uint16_t Value) { std::string RetVal = ""; RetVal = std::to_string(Value); return RetVal;}
		/**
 * @brief Converts a value of an AGE pin type to its string representation.
 *
 * This function takes in the type of the AGE pin and its corresponding value, converts the value into a string 
 * representation using std::to_string() and returns it.
 *
 * @param Type The type of the AGE pin (not used in this conversion but included for completeness).
 * @param Value The value to be converted to a string.
 * @return Returns the string representation of the input value.
 */
/**
 * @brief Converts a numeric value to string.
 *
 * This function takes an AGEPinType and a uint32_t as input, converts the latter to a string representation, 
 * and returns it. The conversion is done using std::to_string() function from C++ standard library.
 *
 * @param Type - The type of pin being converted. This parameter does not contribute to the functionality of this function.
 * @param Value - The numeric value to be converted to a string.
 * 
 * @return Returns a string representation of the input uint32_t value.
 */
static std::string ConvertToString(AGEPinType Type, uint32_t Value) { std::string RetVal = ""; RetVal = std::to_string(Value); return RetVal;}
		/**
 * @brief Converts a value of any type to string.
 *
 * This function takes an AGEPinType and a uint64_t as input, converts the uint64_t to a string representation, 
 * and returns it. The conversion is done based on the provided AGEPinType which can be used for further processing or presentation of the value.
 *
 * @param Type - The type of pin that needs to be converted. This parameter does not contribute to the actual conversion but provides context about what kind of representation is expected from the function.
 * @param Value - The uint64_t value which needs to be converted to string.
 * 
 * @return Returns a string representation of the input uint64_t value.
 */
/**
 * @brief Converts a value to string.
 *
 * This function takes an AGEPinType and a uint64_t as input, converts the uint64_t to a string representation, 
 * and returns it. The conversion is done based on the provided AGEPinType which can be used for further processing or display purposes.
 *
 * @param Type - The type of pin that we are converting from.
 * @param Value - The value of the pin that we want to convert into a string.
 * 
 * @return Returns a string representation of the input uint64_t value.
 */
static std::string ConvertToString(AGEPinType Type, uint64_t Value) { std::string RetVal = ""; RetVal = std::to_string(Value); return RetVal;}
		/**
 * @brief Converts an AGEPinType and a Vector2 to a string.
 *
 * This function takes in an AGEPinType and a Vector2 as parameters, converts the Vector2 to a string using static_cast, 
 * then returns this string. The purpose of this conversion is unknown at present.
 *
 * @param Type The type of pin being converted.
 * @param Value The value of the pin being converted.
 * @return A string representation of the input parameters.
 */
/**
 * @brief Converts a given AGEPinType and Vector2 value to string.
 *
 * This function takes an AGEPinType and a Vector2 as input, converts the Vector2 value to string format using static_cast, 
 * then returns this converted string. The returned string is empty if the conversion fails.
 *
 * @param Type The type of pin that needs to be converted.
 * @param Value The value of the pin that needs to be converted.
 * @return A string representation of the input Vector2 value, or an empty string if the conversion failed.
 */
static std::string ConvertToString(AGEPinType Type, Vector2 Value) { std::string RetVal = ""; RetVal = (std::string)Value; return RetVal;}
		/**
 * @brief Converts an AGEPinType and a Vector3 to a string.
 * 
 * This function takes in two parameters, an AGEPinType and a Vector3. It converts the Vector3 to a string using the `std::string` constructor and returns it.
 * The conversion is done by simply casting the Vector3 object to a std::string.
 * 
 * @param Type The type of pin that we are converting.
 * @param Value The value of the pin, represented as a Vector3.
 * 
 * @return A string representation of the input parameters.
 */
/**
 * @brief Converts a given AGEPinType and Vector3 value to string.
 *
 * This function takes an AGEPinType and a Vector3 as input, converts the Vector3 into a string representation, 
 * and returns it along with the AGEPinType in string format.
 *
 * @param Type The type of pin that needs to be converted to string.
 * @param Value The value of the pin that needs to be converted to string.
 * @return Returns the string representation of the input values.
 */
static std::string ConvertToString(AGEPinType Type, Vector3 Value) { std::string RetVal = ""; RetVal = (std::string)Value; return RetVal;}
		/**
 * @brief Converts a given AGEPinType and Vector4 to string.
 *
 * This function takes an AGEPinType and a Vector4 as input, converts the Vector4 to a string representation, 
 * and returns it along with the AGEPinType. The conversion is done by simply casting the Vector4 to a std::string.
 *
 * @param Type The type of pin that we are converting.
 * @param Value The value of the pin in Vector4 format.
 * @return Returns the string representation of the input Vector4 along with the AGEPinType.
 */
/**
 * @brief Converts a given AGEPinType and Vector4 to string.
 *
 * This function takes an AGEPinType and a Vector4 as input, converts the Vector4 to a string using static_cast, 
 * and returns this string. The purpose of this conversion is unknown at present.
 *
 * @param Type The type of pin that we are converting.
 * @param Value The value of the pin that we are converting.
 *
 * @return Returns the converted string representation of the Vector4 input.
 */
static std::string ConvertToString(AGEPinType Type, Vector4 Value) { std::string RetVal = ""; RetVal = (std::string)Value; return RetVal;}
		/**
 * @brief Converts a floating-point value to a string.
 *
 * This function takes an AGEPinType and a float as input, converts the float to a string using std::to_string(), 
 * and returns this string. The purpose of this conversion is unknown at present.
 *
 * @param Type An enumeration value representing the type of pin being processed. This parameter's role in the function is not clear from the context provided.
 * @param Value A floating-point number to be converted to a string.
 * 
 * @return The float value as a string. If an error occurs during conversion, it returns an empty string.
 */
/**
 * @brief Converts a floating-point value to a string.
 *
 * This function takes an AGEPinType and a float as input, converts the float to a string using std::to_string(), 
 * and returns this string. The purpose of this conversion is unknown at present.
 *
 * @param Type An enum representing different types of pins in the system. It's not clear what this parameter represents or its significance.
 * @param Value A floating-point value to be converted to a string.
 * 
 * @return The float value as a string.
 */
static std::string ConvertToString(AGEPinType Type, float Value) { std::string RetVal = ""; RetVal = std::to_string(Value); return RetVal;}
	}
}

RTTR_REGISTRATION
{
	rttr::registration::class_<AGE::ScriptableEntity>("ScriptableEntity");
	rttr::registration::method("Convert To String", rttr::select_overload<std::string(AGE::AGEPinType,bool)>(&AGE::Utils::ConvertToString));
	rttr::registration::method("Convert To String", rttr::select_overload<std::string(AGE::AGEPinType,int)>(&AGE::Utils::ConvertToString));
	rttr::registration::method("Convert To String", rttr::select_overload<std::string(AGE::AGEPinType,int16_t)>(&AGE::Utils::ConvertToString));
	rttr::registration::method("Convert To String", rttr::select_overload<std::string(AGE::AGEPinType,int64_t)>(&AGE::Utils::ConvertToString));
	rttr::registration::method("Convert To String", rttr::select_overload<std::string(AGE::AGEPinType,uint16_t)>(&AGE::Utils::ConvertToString));
	rttr::registration::method("Convert To String", rttr::select_overload<std::string(AGE::AGEPinType,uint32_t)>(&AGE::Utils::ConvertToString));
	rttr::registration::method("Convert To String", rttr::select_overload<std::string(AGE::AGEPinType,uint64_t)>(&AGE::Utils::ConvertToString));
	rttr::registration::method("Convert To String", rttr::select_overload<std::string(AGE::AGEPinType,AGE::Vector2)>(&AGE::Utils::ConvertToString));
	rttr::registration::method("Convert To String", rttr::select_overload<std::string(AGE::AGEPinType,AGE::Vector3)>(&AGE::Utils::ConvertToString));
	rttr::registration::method("Convert To String", rttr::select_overload<std::string(AGE::AGEPinType,AGE::Vector4)>(&AGE::Utils::ConvertToString));
	rttr::registration::method("Convert To String", rttr::select_overload<std::string(AGE::AGEPinType,float)>(&AGE::Utils::ConvertToString));

}