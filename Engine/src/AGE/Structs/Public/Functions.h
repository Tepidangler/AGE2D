#pragma once
#include "Core/Public/Core.h"
#include "Serializers/Public/DataReader.h"
#include "Serializers/Public/DataWriter.h"
//#include "Render/Public/Renderer2D.h"
//#include "Scene/Public/Entity.h"
//#include <imgui.h>
//#include <misc/cpp/imgui_stdlib.h>
//#include <imgui_internal.h>
//#include <imgui_node_editor.h>
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wfloat-conversion"
#ifdef AG_PLATFORM_WINDOWS
#pragma clang diagnostic ignored "-Wmicrosoft-unqualified-friend"
#endif
#include <rttr/type>
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#ifdef AG_PLATFORM_WINDOWS
#pragma GCC diagnostic ignored "-Wmicrosoft-unqualified-friend"
#endif
#include <rttr/type>
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(push, 0)
#include <rttr/type>
#pragma warning(pop)
#else
#error "Compiler is not supported with AGE yet"
#endif

namespace AGE
{

	enum class FunctionToExecute
	{
		OnUpdate,
		LessThan,
		GreaterThan,
		EqualTo,
		GTET,
		LTET,
		PrintString,
		MakeLiteralString,
		AppendString,
		GetLocation2D,
		GetLocation3D,
		SetLocation2D,
		SetLocation3D,
		ToString,
		GetActor,
		Sum,
		Subtract,
		Multiply,
		Divide,
		Modulo,
		Pow,
		SquareRoot,
		CubeRoot,
		DotProduct,
		CrossProduct,
		Cosine,
		Sine,
	};

	template<typename R, typename E>
	struct AGEFunction final
	{
	public:
		/**
 * @brief Default constructor for the AGEFunction class.
 */
/**
 * @brief Default constructor for the AGE class.
 *
 * This function initializes an instance of the AGE class with its default values. It is used to create a new object without any specific initialization.
 *
 * @return void
 */
AGEFunction() = default;

		/**
 * @brief Constructs an instance of the class with given parameters.
 * @param Exec A string parameter that is used for some purpose, but not specified in this comment.
 * @param Arguments A vector of rttr::variant objects which are used to perform various operations.
 * @param Value Pointer to an E object, default value is nullptr.
 * @param Ptr Reference to a R object, default value is nullptr.
 */
/**
 * @brief Constructs an instance of the class with given parameters.
 * @param Exec The string to be stored in the object.
 * @param Arguments A vector of rttr::variant objects to be stored in the object.
 * @param Value Pointer to an E object, which is copied into the object if not null. Defaults to nullptr.
 * @param Ptr Reference to a R object, which can be used to access and modify the object. Defaults to nullptr.
 */
AGEFunction(const std::string& Exec,  std::vector<rttr::variant> Arguments, E* Value = nullptr, Ref<R>& Ptr = nullptr)
			: Entt(Value), Val(Exec), Reference(Ptr), Args(Arguments)
		{
		}

		COMMENT:
/**
 * @brief Default copy constructor for the class.
 *
 * This function is used to create a new instance of an object by copying another existing one. It uses the '= default' syntax, which tells the compiler to use the default implementation provided by the compiler.
 *
 * @param other The existing object to be copied.
 * 
 * @return A new instance of the class with the same state as the input parameter.
 */
CONFIDENCE: 1.0;

COMMENT:
/**
 * @brief Default copy constructor for the class.
 *
 * This function is used to create a new instance of the class by copying an existing one. It uses the '= default' syntax, which tells the compiler to generate a default implementation for this member function.
 *
 * @param other The instance to be copied.
 */
CONFIDENCE: 1.0;

AGEFunction(const AGEFunction&) = default;
		/**
 * @brief Virtual destructor for the AGEFunction class.
 *
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime. It does not take any parameters and returns void.
 */
/**
 * @brief Virtual destructor for the AGEFunction class.
 *
 * This function is responsible for freeing any resources that were allocated by the object during its lifetime. It does not take any parameters and returns void.
 */
virtual ~AGEFunction() = default;


		Ref<R> Reference;
		E* Entt;
		std::string Val;
		std::vector<rttr::variant> Args;
		uint64_t RefID;
		uint64_t EnttID;
		bool bIsUtilFunction = false;

		/**
 * @brief Executes the function stored in Reference with optional delta time as input.
 * 
 * The function will be executed based on whether a reference to an object is present and if DeltaTime > 0. If only Reference is provided, it assumes that no additional parameters are required for execution.
 * 
 * @param[in] DeltaTime Optional parameter representing time elapsed since the last frame. Defaults to 0.f.
 * @return The return value of the function stored in Reference.
 */
/**
 * @brief Executes the function stored in Reference with an optional delta time as parameter.
 * 
 * The function to be executed is determined by the state of Reference. If it's not null, then either Function(Reference) or Function(Reference, DeltaTime) will be called depending on whether DeltaTime > 0. If Reference is null and DeltaTime > 0, then Function(nullptr, DeltaTime) is called.
 * 
 * @param DeltaTime The time step to pass into the function (optional).
 * @return rttr::variant The return value of the executed function.
 */
rttr::variant Execute(TimeStep DeltaTime = 0.f)
		{
			if (Reference && DeltaTime > 0.f)
			{
				return Function(Reference, DeltaTime);
			}

			if (Reference)
			{
				return Function(Reference);

			}

			Reference = nullptr;
			if (DeltaTime > 0.f)
			{
				return Function(Reference, DeltaTime);
			}

			return Function(Reference);

		}

		/**
 * @brief This function serializes the AGEFunction data into a DataWriter object.
 * 
 * The function writes the RefID, bIsUtilFunction and Entt status of the AGEFunction to the DataWriter. If the Entt is present, it also writes the EnttID. It then writes the Val string of the AGEFunction.
 * 
 * @param Serializer Pointer to a DataWriter object where serialized data will be written into.
 * @param Data Reference to an AGEFunction object that needs to be serialized.
 * 
 * @return void
 */
/**
 * @brief This function serializes the AGEFunction data into a DataWriter object.
 * 
 * The function writes the RefID, bIsUtilFunction flag, and Entt status to the Serializer. If an Entt exists, it also writes the EnttID. Finally, it writes the Val string.
 * 
 * @param[in] Serializer Pointer to a DataWriter object where serialized data will be written.
 * @param[in] Data Reference to an AGEFunction object that contains the data to be serialized.
 * 
 * @return void
 */
static void Serialize(DataWriter* Serializer, const AGEFunction& Data)
		{
			Serializer->WriteRaw<uint64_t>((uint64_t)Data.RefID);
			Serializer->WriteRaw<bool>(Data.bIsUtilFunction);
			if (Data.Entt)
			{
				Serializer->WriteRaw<bool>(true);
				Serializer->WriteRaw<uint64_t>(Data.EnttID);

			}
			else
			{
				Serializer->WriteRaw<bool>(false);
			}

			Serializer->WriteString(Data.Val);
		}

		/**
 * @brief Deserialize function data from a DataReader into an AGEFunction object.
 * 
 * This function reads raw data from the provided DataReader and populates an AGEFunction object with it. The function checks if 'HasEntt' is true, in which case it also reads an EnttID. It then reads a string value for 'Val'.
 * @param Serializer Pointer to the DataReader instance that provides raw data.
 * @param Data Reference to the AGEFunction object where the deserialized data will be stored.
 * 
 * @return void
 */
/**
 * @brief Deserializes data from a DataReader into an AGEFunction object.
 * 
 * This function reads raw data from the provided DataReader and populates an AGEFunction object with it. The function checks if 'HasEntt' is true, in which case it also reads an EnttID. It then reads a string value for 'Val'.
 * @param Serializer Pointer to the DataReader instance that provides raw data.
 * @param Data Reference to the AGEFunction object where the deserialized data will be stored.
 * 
 * @return void
 */
static void Deserialize(DataReader* Serializer, AGEFunction& Data)
		{
			bool HasEntt = false;

			Serializer->ReadRaw<uint64_t>(Data.RefID);
			Serializer->ReadRaw<bool>(Data.bIsUtilFunction);
			Serializer->ReadRaw<bool>(HasEntt);
			if (HasEntt)
			{
				Serializer->ReadRaw<uint64_t>(Data.EnttID);
			}
			Serializer->ReadString(Data.Val);
		}


	protected:

		/**
 * @brief This function is used to execute a method on an entity. It can be either a utility function or a normal method of the entity's class. 
 * 
 * @param Ptr Reference to the entity. If it's not valid, the function will return without doing anything.
 * @param DeltaTime The time step for the update. Default is 0.f.
 * 
 * @return Returns a variant containing the result of the method execution if successful, or an invalid variant otherwise.
 */
/**
 * @brief This function is used to perform some operation on a given entity. It can be either an update function or any other type of function depending on the input parameters and conditions.
 * 
 * @param Ptr A reference to an object of class R.
 * @param DeltaTime The time elapsed since the last frame, default is 0.f.
 * @return rttr::variant Returns a variant that contains the result of the operation performed on the entity. If no valid operation was performed, it returns an empty variant.
 */
rttr::variant Function(Ref<R>& Ptr, TimeStep DeltaTime = 0.f)
		{
			rttr::variant RetVal;
			if (Val == "OnUpdate")
			{
				RetVal = DeltaTime;
				return RetVal;
			}
			if (!Ptr)
			{
				//TODO: Add logging info here to warn user that the pointer passed in wasn't valid assuming it should be.
				return RetVal;
			}
			if (!bIsUtilFunction)
			{
				rttr::type class_type = rttr::type::get_by_name(Entt->GetScriptableEntityType());
				rttr::variant Var = Entt;
				rttr::method Method = class_type.get_method(Val);
				RetVal = Method.invoke(Var);
				if (RetVal.is_valid())
				{
					return RetVal;
				}
				return RetVal;
			}
			else
			{
				//rttr::method Method = rttr::type::get_global_method(Val);
				//RetVal = Method.invoke({}, Args[0].get_value<std::string>(), Args[1].get_value<Ref<Font>>(), Args[2].get_value<Matrix4D>(), Args[3].get_value<Vector4>());
				std::vector<rttr::argument> Params;
				for (auto& A : Args)
				{
					Params.emplace_back(A);
				}
				RetVal = rttr::type::invoke(Val,Params);
				if (RetVal.is_valid())
				{
					return RetVal;
				}
				return RetVal;

			}
			return RetVal;
		}
	};
}

#if 0
			switch ((int)Val)
			{
			case 0:  Ptr->Outputs.back()->Value = DeltaTime; break;
			case 1:  Ptr->Outputs.back()->Boolean = Ptr->Inputs[0]->Value < Ptr->Inputs[1]->Value; break;
			case 2:  Ptr->Outputs.back()->Boolean = Ptr->Inputs[0]->Value > Ptr->Inputs[1]->Value; break;
			case 3:  Ptr->Outputs.back()->Boolean = Ptr->Inputs[0]->Value == Ptr->Inputs[1]->Value; break;
			case 4:  Ptr->Outputs.back()->Boolean = Ptr->Inputs[0]->Value >= Ptr->Inputs[1]->Value; break;
			case 5:  Ptr->Outputs.back()->Boolean = Ptr->Inputs[0]->Value <= Ptr->Inputs[1]->Value; break;
			case 6:
			{
				if (!Entt)
				{
					return;
				}
				Renderer2D::DrawString(Ptr->Inputs[1]->String, Font::GetDefault(), Entt->GetComponent<TransformComponent>().GetTransform(), Vector4(1.f));
				break;
			}
			case 7:
			{
				std::string newString;
				static bool WasActive = false;
				ImGui::PushItemWidth(100.f);
				ImGui::InputText("##edit", &Ptr->Outputs.back()->String);
				ImGui::PopItemWidth();
				if (ImGui::IsItemActive() && !WasActive)
				{
					ax::NodeEditor::EnableShortcuts(false);
					WasActive = true;
				}
				else if (!ImGui::IsItemActive() && WasActive)
				{
					ax::NodeEditor::EnableShortcuts(true);
					WasActive = false;
				}
				ImGui::Spring(0);
				break;
			}
			case 8:
			{
				std::string NewString;
				NewString = Ptr->Inputs[0]->String;
				NewString.append(Ptr->Inputs[1]->String);
				Ptr->Outputs.back()->String = NewString;
				break;
			}
			case 9:  Ptr->Outputs.back()->Vector2D = { Entt->GetLocation().x, Entt->GetLocation().y }; break;
			case 10: Ptr->Outputs.back()->Vector3D = Entt->GetLocation(); break;
			case 11: Entt->SetLocation({ Ptr->Inputs.back()->Vector2D.x, Ptr->Inputs.back()->Vector2D.y,0.f }); break;
			case 12: Entt->SetLocation(Ptr->Inputs.back()->Vector3D); break;
			case 13:
			{
				switch ((int)Ptr->Inputs.back()->Type)
				{
				case 1:     Ptr->Outputs.back()->String = Ptr->Inputs.back()->Boolean ? "True" : "False"; break;
				case 2:     Ptr->Outputs.back()->String = std::to_string(Ptr->Inputs.back()->Integer); break;
				case 3:		Ptr->Outputs.back()->String = std::to_string(Ptr->Inputs.back()->Integer16); break;
				case 4:		Ptr->Outputs.back()->String = std::to_string(Ptr->Inputs.back()->Integer64); break;
				case 5:		Ptr->Outputs.back()->String = std::to_string(Ptr->Inputs.back()->UInteger16); break;
				case 6:		Ptr->Outputs.back()->String = std::to_string(Ptr->Inputs.back()->UInteger32); break;
				case 7:		Ptr->Outputs.back()->String = std::to_string(Ptr->Inputs.back()->UInteger64); break;
				case 8:		Ptr->Outputs.back()->String = (std::string)Ptr->Inputs.back()->Vector2D; break;
				case 9:		Ptr->Outputs.back()->String = (std::string)Ptr->Inputs.back()->Vector3D; break;
				case 10:		Ptr->Outputs.back()->String = (std::string)Ptr->Inputs.back()->Vector4D; break;
				case 11:    Ptr->Outputs.back()->String = std::to_string(Ptr->Inputs.back()->Value); break;
				//case AGEPinType::String:   m_Ptrs.back()->Outputs.back()->String = std:: break;
				//case 12:   Ptr->Outputs.back()->String = reinterpret_cast<ScriptableEntity*>(Ptr->Inputs.back()->ObjPtr)->GetName();  break;
				//case AGEPinType::Function: m_Ptrs.back()->Outputs.back()->String = std:: break;
				//case AGEPinType::Callback: m_Ptrs.back()->Outputs.back()->String = std:: break;
				}
				break;
			}
			case 14: break;
			case 15: Ptr->Outputs.back()->Value = Ptr->Inputs[0]->Value + Ptr->Inputs[1]->Value; break;
			case 16: Ptr->Outputs.back()->Value = Ptr->Inputs[0]->Value - Ptr->Inputs[1]->Value; break;
			case 17: Ptr->Outputs.back()->Value = Ptr->Inputs[0]->Value * Ptr->Inputs[1]->Value; break;
			case 18: Ptr->Outputs.back()->Value = Ptr->Inputs[0]->Value / Ptr->Inputs[1]->Value; break;
			case 19:
				if (Ptr->Inputs[1]->Integer == 0)
				{
					return;
				}
				Ptr->Outputs.back()->Integer = Ptr->Inputs[0]->Integer % Ptr->Inputs[1]->Integer;
				break;
			case 20: Ptr->Outputs.back()->Value = std::powf(Ptr->Inputs[0]->Value, Ptr->Inputs[1]->Value); break;
			case 21: Ptr->Outputs.back()->Value = std::sqrtf(Ptr->Inputs[0]->Value); break;
			case 22: Ptr->Outputs.back()->Value = std::cbrtf(Ptr->Inputs[0]->Value); break;
			case 23: Ptr->Outputs.back()->Value = Math::DotProduct3D(Ptr->Inputs[0]->Vector3D, Ptr->Inputs[1]->Vector3D);  break;
			case 24: Ptr->Outputs.back()->Vector3D = Math::CrossProduct(Ptr->Inputs[0]->Vector3D, Ptr->Inputs[1]->Vector3D); break;
			case 25: Ptr->Outputs.back()->Value = Math::Cos(Ptr->Inputs.back()->Value); break;
			case 26: Ptr->Outputs.back()->Value = Math::Sin(Ptr->Inputs.back()->Value); break;
			default: break;
			}
			return;
#endif

