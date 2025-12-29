#include "AGEpch.hpp"
#include "Scene/Public/ScriptableEntity.h"
#include "Core/Public/App.h"
#include <rttr/registration>




namespace AGE
{
	void ScriptableEntity::PushComp()
	{
		App::Get().PushScriptableComp(this);
	}
	namespace Utils
	{
		static std::string ConvertToString(AGEPinType Type, bool Value) { std::string RetVal = ""; RetVal = Value ? "True" : "False"; return RetVal;}
		static std::string ConvertToString(AGEPinType Type, int Value) { std::string RetVal = ""; RetVal = std::to_string(Value); return RetVal;}
		static std::string ConvertToString(AGEPinType Type, int16_t Value) { std::string RetVal = ""; RetVal = std::to_string(Value); return RetVal;}
		static std::string ConvertToString(AGEPinType Type, int64_t Value) { std::string RetVal = ""; RetVal = std::to_string(Value); return RetVal;}
		static std::string ConvertToString(AGEPinType Type, uint16_t Value) { std::string RetVal = ""; RetVal = std::to_string(Value); return RetVal;}
		static std::string ConvertToString(AGEPinType Type, uint32_t Value) { std::string RetVal = ""; RetVal = std::to_string(Value); return RetVal;}
		static std::string ConvertToString(AGEPinType Type, uint64_t Value) { std::string RetVal = ""; RetVal = std::to_string(Value); return RetVal;}
		static std::string ConvertToString(AGEPinType Type, Vector2 Value) { std::string RetVal = ""; RetVal = (std::string)Value; return RetVal;}
		static std::string ConvertToString(AGEPinType Type, Vector3 Value) { std::string RetVal = ""; RetVal = (std::string)Value; return RetVal;}
		static std::string ConvertToString(AGEPinType Type, Vector4 Value) { std::string RetVal = ""; RetVal = (std::string)Value; return RetVal;}
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