#pragma once
#include "Core/Public/Core.h"
#include "Serializers/Public/DataReader.h"
#include "Serializers/Public/DataWriter.h"
#include "Render/Public/Renderer2D.h"
#include "Scene/Public/Entity.h"
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <imgui_internal.h>
#include <imgui_node_editor.h>
#include <rttr/type>


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
		AGEFunction() = default;

		AGEFunction(const std::string& Exec,  std::vector<rttr::variant> Arguments, E* Value = nullptr, Ref<R>& Ptr = nullptr)
			: Entt(Value), Val(Exec), Reference(Ptr), Args(Arguments)
		{
		}

		AGEFunction(const AGEFunction&) = default;
		virtual ~AGEFunction() = default;


		Ref<R> Reference;
		E* Entt;
		std::string Val;
		std::vector<rttr::variant> Args;
		uint64_t RefID;
		uint64_t EnttID;
		bool bIsUtilFunction = false;

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

