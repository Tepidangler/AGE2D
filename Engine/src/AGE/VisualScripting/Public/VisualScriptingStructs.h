#pragma once
#include <imgui_node_editor.h>
#include <utilities/builders.h>
#include <utilities/widgets.h>
#include "Scene/Public/ScriptableEntity.h"
#include "Structs/Public/Functions.h"
#include <rttr/registration>
namespace AGE
{

	enum class AGEPinType : uint8_t
	{
		Flow,
		Bool,
		Int,
		Int16,
		Int64,
		UInt16,
		UInt32,
		UInt64,
		Vector2D,
		Vector3D,
		Vector4D,
		Float,
		String,
		Object,
		Function,
		Callback,
		Any
	};
	enum class NodeArgType : uint8_t
	{
		Bool,
		Int,
		Int16,
		Int64,
		UInt16,
		UInt32,
		UInt64,
		Vector2D,
		Vector3D,
		Vector4D,
		Float,
		String,
		Object,
		Matrix2D,
		Matrix3D,
		Matrix4D,
		Font,
		PinType,
		NullType
	};
	RTTR_REGISTRATION
{
	rttr::registration::enumeration<AGE::AGEPinType>("AGEPinType")(
		rttr::value("Flow",AGE::AGEPinType::Flow),
		rttr::value("Bool",AGE::AGEPinType::Bool),
		rttr::value("Int",AGE::AGEPinType::Int),
		rttr::value("Int16",AGE::AGEPinType::Int16),
		rttr::value("Int64",AGE::AGEPinType::Int64),
		rttr::value("UInt16",AGE::AGEPinType::UInt16),
		rttr::value("UInt32",AGE::AGEPinType::UInt32),
		rttr::value("UInt64",AGE::AGEPinType::UInt64),
		rttr::value("Vector2D",AGE::AGEPinType::Vector2D),
		rttr::value("Vector3D",AGE::AGEPinType::Vector3D),
		rttr::value("Vector4D",AGE::AGEPinType::Vector4D),
		rttr::value("Float",AGE::AGEPinType::Float),
		rttr::value("String",AGE::AGEPinType::String),
		rttr::value("Object",AGE::AGEPinType::Object),
		rttr::value("Function",AGE::AGEPinType::Function),
		rttr::value("Callback",AGE::AGEPinType::Callback),
		rttr::value("Any",AGE::AGEPinType::Any)


		);
}

	enum class AGENodeType
	{
		Blueprint,
		Simple,
		Tree,
		Comment,
		Narrative
	};

	struct AGENode;

	struct AGEPin
	{
		ax::NodeEditor::PinId ID;
		ax::NodeEditor::NodeId NextNodeID;
		Ref<AGENode> Node;
		std::string Name;
		AGEPinType Type;
		ax::NodeEditor::PinKind Kind;

		std::string String = "";
		bool Boolean = false;
		int Integer = 0;
		int16_t  Integer16 = 0;
		int64_t  Integer64 = 0;
		uint16_t UInteger16 = 0;
		uint32_t UInteger32 = 0;
		uint64_t UInteger64 = 0;
		float Value = 0.f;
		Vector2 Vector2D = { 0.f,0.f };
		Vector3 Vector3D = { 0.f,0.f,0.f };
		Vector4 Vector4D = { 0.f,0.f,0.f,0.f };

		Ref<ScriptableEntity> ObjPtr= nullptr;

		AGEPin() = default;
		AGEPin(UUID id, const char* name, AGEPinType type)
			: ID(id), Node(nullptr), Name(name), Type(type), Kind(ax::NodeEditor::PinKind::Input)
		{

		}

		virtual ~AGEPin() = default;

		rttr::variant GetValue(AGEPinType Type)
		{
			switch ((int)Type)
			{
				case 1:     return Boolean;
				case 2:     return Integer;
				case 3:		return Integer16;
				case 4:		return Integer64;
				case 5:		return UInteger16;
				case 6:		return UInteger32;
				case 7:		return UInteger64;
				case 8:		return Vector2D;
				case 9:		return Vector3D;
				case 10:	return Vector4D;
				case 11:    return Value;
				case 16:	return nullptr;
					//case AGEPinType::String:   m_Ptrs.back()->Outputs.back()->String = std:: break;
					//case 12:   Ptr->Outputs.back()->String = reinterpret_cast<ScriptableEntity*>(Ptr->Inputs.back()->ObjPtr)->GetName();  break;
					//case AGEPinType::Function: m_Ptrs.back()->Outputs.back()->String = std:: break;
					//case AGEPinType::Callback: m_Ptrs.back()->Outputs.back()->String = std:: break;
			}
		}

		static void Serialize(DataWriter* Serializer, const AGEPin& Data)
		{
			Serializer->WriteRaw<uint64_t>((uint64_t)Data.ID);
			Serializer->WriteRaw<uint64_t>((uint64_t)Data.NextNodeID);
			Serializer->WriteString(Data.Name);
			Serializer->WriteRaw<AGEPinType>(Data.Type);
			Serializer->WriteRaw<ax::NodeEditor::PinKind>(Data.Kind);
			Serializer->WriteString(Data.String);
			Serializer->WriteRaw<bool>(Data.Boolean);
			Serializer->WriteRaw<int>(Data.Integer);
			Serializer->WriteRaw<int16_t>(Data.Integer16);
			Serializer->WriteRaw<int64_t>(Data.Integer64);
			Serializer->WriteRaw<uint16_t>(Data.UInteger16);
			Serializer->WriteRaw<uint32_t>(Data.UInteger32);
			Serializer->WriteRaw<uint64_t>(Data.UInteger64);
			Serializer->WriteRaw<float>(Data.Value);
			Serializer->WriteRaw<Vector2>(Data.Vector2D);
			Serializer->WriteRaw<Vector3>(Data.Vector3D);
			Serializer->WriteRaw<Vector4>(Data.Vector4D);
			if (Data.ObjPtr)
			{
				ScriptableEntity* E = Data.ObjPtr.get();
				Serializer->WriteRaw<bool>(true);
				Serializer->WriteRaw<UUID>(E->GetID());
			}
			else
			{
				Serializer->WriteRaw<bool>(false);
			}
		}

		static void Deserialize(DataReader* Serializer, AGEPin& Data)
		{
			uint64_t ID;
			uint64_t NextNodeID;
			UUID UID;
			bool HasObjPtr = false;
			Serializer->ReadRaw<uint64_t>(ID);
			Data.ID = ID;
			Serializer->ReadRaw<uint64_t>(NextNodeID);
			Data.NextNodeID = NextNodeID;
			Serializer->ReadString(Data.Name);
			Serializer->ReadRaw<AGEPinType>(Data.Type);
			Serializer->ReadRaw<ax::NodeEditor::PinKind>(Data.Kind);
			Serializer->ReadString(Data.String);
			Serializer->ReadRaw<bool>(Data.Boolean);
			Serializer->ReadRaw<int>(Data.Integer);
			Serializer->ReadRaw<int16_t>(Data.Integer16);
			Serializer->ReadRaw<int64_t>(Data.Integer64);
			Serializer->ReadRaw<uint16_t>(Data.UInteger16);
			Serializer->ReadRaw<uint32_t>(Data.UInteger32);
			Serializer->ReadRaw<uint64_t>(Data.UInteger64);
			Serializer->ReadRaw<float>(Data.Value);
			Serializer->ReadRaw<Vector2>(Data.Vector2D);
			Serializer->ReadRaw<Vector3>(Data.Vector3D);
			Serializer->ReadRaw<Vector4>(Data.Vector4D);
			Serializer->ReadRaw<bool>(HasObjPtr);
			if (HasObjPtr)
			{
				Serializer->ReadRaw<UUID>(UID);

			}
		}
	};

	struct NodeArguments
	{
		NodeArguments() = default;
		std::vector<rttr::variant> Args;

		static void Serialize(DataWriter* Serializer, const NodeArguments& Data)
		{
			Serializer->WriteRaw<uint64_t>(Data.Args.size());
			for (auto& Arg : Data.Args)
			{
				if (Arg.is_type<bool>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::Bool);
					Serializer->WriteRaw<bool>(Arg.get_value<bool>());
					continue;
				}

				if (Arg.is_type<int>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::Int);
					Serializer->WriteRaw<int>(Arg.get_value<int>());
					continue;
				}
				if (Arg.is_type<int*>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::Int);
					Serializer->WriteRaw<int>(*Arg.get_value<int*>());
					continue;
				}
				if (Arg.is_type<int16_t>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::Int16);
					Serializer->WriteRaw<int16_t>(Arg.get_value<int16_t>());
					continue;
				}
				if (Arg.is_type<int64_t>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::Int64);
					Serializer->WriteRaw<int64_t>(Arg.get_value<int64_t>());
					continue;
				}
				if (Arg.is_type<uint16_t>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::UInt16);
					Serializer->WriteRaw<uint16_t>(Arg.get_value<uint16_t>());
					continue;
				}
				if (Arg.is_type<uint32_t>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::UInt32);
					Serializer->WriteRaw<uint32_t>(Arg.get_value<uint32_t>());
					continue;
				}
				if (Arg.is_type<uint64_t>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::UInt64);
					Serializer->WriteRaw<uint64_t>(Arg.get_value<uint64_t>());
					continue;
				}
				if (Arg.is_type<Vector2>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::Vector2D);
					Serializer->WriteRaw<Vector2>(Arg.get_value<Vector2>());
					continue;
				}
				if (Arg.is_type<Vector3>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::Vector3D);
					Serializer->WriteRaw<Vector3>(Arg.get_value<Vector3>());
					continue;
				}
				if (Arg.is_type<Vector3*>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::Vector3D);
					Serializer->WriteRaw<Vector3>(*Arg.get_value<Vector3*>());
					continue;
				}
				if (Arg.is_type<Vector4>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::Vector4D);
					Serializer->WriteRaw<Vector4>(Arg.get_value<Vector4>());
					continue;
				}
				if (Arg.is_type<float>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::Float);
					Serializer->WriteRaw<float>(Arg.get_value<float>());
					continue;
				}
				if (Arg.is_type<float*>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::Float);
					Serializer->WriteRaw<float>(*Arg.get_value<float*>());
					continue;
				}
				if (Arg.is_type<std::string*>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::String);
					Serializer->WriteString(*Arg.get_value<std::string*>());
					continue;
				}
				if (Arg.is_type<std::string>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::String);
					Serializer->WriteString(Arg.get_value<std::string>());
					continue;
				}
				if (Arg.is_type<Ref<Font>>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::Font);
					Serializer->WriteString(Arg.get_value<Ref<Font>>()->GetAtlasTexture()->GetTextureFilePath());
					continue;
				}
				if (Arg.is_type<Matrix4D>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::Matrix4D);
					Serializer->WriteRaw<Matrix4D>(Arg.get_value<Matrix4D>());
					continue;
				}
				if (Arg.is_type<AGEPinType>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::PinType);
					Serializer->WriteRaw<AGEPinType>(Arg.get_value<AGEPinType>());
					continue;
				}
				if (Arg.is_type<nullptr_t>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::NullType);
					Serializer->WriteRaw<uint8_t>(0);
				}


			}
		}

		static void Deserialize(DataReader* Serializer, NodeArguments& Data)
		{
			uint64_t Size;
			Serializer->ReadRaw<uint64_t>(Size);
			for (int i = 0; i < Size; ++i)
			{
				uint8_t Type;
				Serializer->ReadRaw<uint8_t>(Type);

				switch((NodeArgType)Type)
				{
					case NodeArgType::Bool:
					{
						bool Value;
						Serializer->ReadRaw<bool>(Value);
						Data.Args.emplace_back(Value);
						continue;
					}
					case NodeArgType::Int:
					{
						int Value;
						Serializer->ReadRaw<int>(Value);
						Data.Args.emplace_back(Value);
						continue;
					}
					case NodeArgType::Int16:
					{
						int16_t Value;
						Serializer->ReadRaw<int16_t>(Value);
						Data.Args.emplace_back(Value);
					continue;
					}
					case NodeArgType::Int64:
					{
						int64_t Value;
						Serializer->ReadRaw<int64_t>(Value);
						Data.Args.emplace_back(Value);
					continue;
					}
					case NodeArgType::UInt16:
					{
						uint16_t Value;
						Serializer->ReadRaw<uint16_t>(Value);
						Data.Args.emplace_back(Value);
					continue;
					}
					case NodeArgType::UInt32:
					{
						uint32_t Value;
						Serializer->ReadRaw<uint32_t>(Value);
						Data.Args.emplace_back(Value);
					continue;
					}
					case NodeArgType::UInt64:
					{
						uint64_t Value;
						Serializer->ReadRaw<uint64_t>(Value);
						Data.Args.emplace_back(Value);
					continue;
					}
					case NodeArgType::Vector2D:
					{
						Vector2 Value;
						Serializer->ReadRaw<Vector2>(Value);
						Data.Args.emplace_back(Value);
					continue;
					}
					case NodeArgType::Vector3D:
					{
						Vector3 Value;
						Serializer->ReadRaw<Vector3>(Value);
						Data.Args.emplace_back(Value);
					continue;
					}
					case NodeArgType::Vector4D:
					{
						Vector4 Value;
						Serializer->ReadRaw<Vector4>(Value);
						Data.Args.emplace_back(Value);
					continue;
					}
					case NodeArgType::Float:
					{
						float Value;
						Serializer->ReadRaw<float>(Value);
						Data.Args.emplace_back(Value);
					continue;
					}
					case NodeArgType::String:
					{
						std::string Value;
						Serializer->ReadString(Value);
						Data.Args.emplace_back(Value);
					continue;
					}
					case NodeArgType::Object:
					{
					continue;
					}
					case NodeArgType::Matrix2D:
					{
					continue;
					}
					case NodeArgType::Matrix3D:
					{
					continue;
					}
					case NodeArgType::Matrix4D:
					{
						Matrix4D Value;
						Serializer->ReadRaw<Matrix4D>(Value);
						Data.Args.emplace_back(Value);
					continue;
					}
					case NodeArgType::Font:
					{
						std::string Value;
						Serializer->ReadString(Value);
						Data.Args.emplace_back(Font::GetDefault());
					continue;
					}
					case NodeArgType::PinType:
					{
						AGEPinType Value;
						Serializer->ReadRaw<AGEPinType>(Value);
						Data.Args.emplace_back(Value);
					continue;
					}
					case NodeArgType::NullType:
					{
						uint8_t nullbyte;
						Serializer->ReadRaw<uint8_t>(nullbyte);
						Data.Args.emplace_back(nullptr);
					continue;
					}
				}
			}
		}
	};

	struct AGENode : public std::enable_shared_from_this<AGENode>
	{
		ax::NodeEditor::NodeId ID;
		std::string Name;
		std::vector<Ref<AGEPin>> Inputs;
		std::vector<Ref<AGEPin>> Outputs;
		ImColor Color;
		AGENodeType Type;
		Vector2 Size;

		Ref<AGENode> NextNode;
		uint32_t NextNodeID = 0;

		std::string State;
		std::string SavedState;
		NodeArguments FunctionArgs;
		bool bIsBeginPlay = false;
		bool bIsOnUpdate = false;

		AGEFunction<AGENode, ScriptableEntity> Func;


		AGENode() = default;

		AGENode(uint32_t id, const char* name, ImColor color = ImColor(255, 255, 255))
			:ID(id), Name(name), Color(color), Type(AGENodeType::Blueprint), Size(0.f)
		{

		}

		bool operator<(const AGENode& Other) const
		{
			return (ID.Get() < Other.ID.Get());
		}

		virtual ~AGENode() = default;

		void SetNodeFuncArguments()
		{
			bool bCanSkip = false;
			Func.Args.clear();
			for (auto& A : FunctionArgs.Args)
			{
				if (bCanSkip)
				{
					continue;
				}
				if (A.is_type<std::string*>())
				{
					Func.Args.emplace_back(*A.get_value<std::string*>());
					continue;
				}
				if (A.is_type<float*>())
				{
					Func.Args.emplace_back(*A.get_value<float*>());
					continue;

				}
				if (A.is_type<AGEPinType>())
				{
					if (A.get_value<AGEPinType>() ==  AGEPinType::Any)
					{
						Func.Args.emplace_back(Inputs.back()->Type);
						Func.Args.emplace_back(Inputs.back()->GetValue(Inputs.back()->Type));
						bCanSkip = true;
						continue;
					}
				}
				Func.Args.emplace_back(A);
			}


		}
		bool CompileOutputPins()
		{
			bool Success = true;
			for (auto O : Outputs)
			{
				if (!Success)
				{
					return Success;
				}
				switch (O->Type)
				{
					case AGEPinType::Flow:
					{
						break;
					}
					case AGEPinType::Bool:
					{
						rttr::variant RetVal = Func.Execute();
						if (RetVal.is_valid())
						{
							O->Boolean = RetVal.get_value<bool>();
							continue;
						}
						Success = false;
						break;
					}
					case AGEPinType::Int:
					{
						rttr::variant RetVal = Func.Execute();
						if (RetVal.is_valid())
						{
							O->Integer = RetVal.get_value<int>();
							continue;
						}
						Success = false;
						break;
					}
					case AGEPinType::Int16:
					{
						rttr::variant RetVal = Func.Execute();
						if (RetVal.is_valid())
						{
							O->Integer16 = RetVal.get_value<int16_t>();
							continue;
						}
						Success = false;
						break;
					}
					case AGEPinType::Int64:
					{
						rttr::variant RetVal = Func.Execute();
						if (RetVal.is_valid())
						{
							O->Integer64 = RetVal.get_value<int64_t>();
							continue;
						}
						Success = false;
						break;
					}
					case AGEPinType::UInt16:
					{
						rttr::variant RetVal = Func.Execute();
						if (RetVal.is_valid())
						{
							O->UInteger16 = RetVal.get_value<uint16_t>();
							continue;
						}
						Success = false;
						break;
					}
					case AGEPinType::UInt32:
					{
						rttr::variant RetVal = Func.Execute();
						if (RetVal.is_valid())
						{
							O->UInteger32 = RetVal.get_value<uint32_t>();
							continue;
						}
						Success = false;
						break;
					}
					case AGEPinType::UInt64:
					{
						rttr::variant RetVal = Func.Execute();
						if (RetVal.is_valid())
						{
							O->UInteger64 = RetVal.get_value<uint64_t>();
							continue;
						}
						Success = false;
						break;
					}
					case AGEPinType::Vector2D:
					{
						rttr::variant RetVal = Func.Execute();
						if (RetVal.is_valid())
						{
							O->Vector2D  = RetVal.get_value<Vector2>();
							continue;
						}
						Success = false;
						break;
					}
					case AGEPinType::Vector3D:
					{
						rttr::variant RetVal = Func.Execute();
						if (RetVal.is_valid())
						{
							O->Vector3D = RetVal.get_value<Vector3>();
							continue;
						}
						Success = false;
						break;
					}
					case AGEPinType::Vector4D:
					{
						rttr::variant RetVal = Func.Execute();
						if (RetVal.is_valid())
						{
							O->Vector4D = RetVal.get_value<Vector4>();
							continue;
						}
						Success = false;
						break;
					}
					case AGEPinType::Float:
					{
						rttr::variant RetVal = Func.Execute();
						if (RetVal.is_valid())
						{
							O->Value = RetVal.get_value<float>();
							continue;
						}
						Success = false;
						break;
					}
					case AGEPinType::String:
					{
						rttr::variant RetVal = Func.Execute();
						if (RetVal.is_valid())
						{
							O->String = RetVal.get_value<std::string>();
							continue;
						}
						Success = false;
						break;
					}
					case AGEPinType::Object:
					{
						break;
					}
					case AGEPinType::Function:
					{
						break;
					}
					case AGEPinType::Callback:
					{
						break;
					}
					default:
					{
						return false;
					}
				}
			}

			return Success;
		}
		static void Serialize(DataWriter* Serializer, const AGENode& Data)
		{
			std::vector<AGEPin> Inputs(Data.Inputs.size());
			std::vector<AGEPin> Outputs(Data.Outputs.size());

			for (int i = 0; i < Inputs.size(); i++)
			{
				Inputs[i] = *Data.Inputs[i].get();
			}
			for (int i = 0; i < Outputs.size(); i++)
			{
				Outputs[i] = *Data.Outputs[i].get();
			}

			Serializer->WriteRaw<uint64_t>((uint64_t)Data.ID);
			Serializer->WriteString(Data.Name);
			Serializer->WriteRaw<uint32_t>((ImU32)Data.Color);
			Serializer->WriteArray<AGEPin>(Inputs);
			Serializer->WriteArray<AGEPin>(Outputs);
			Serializer->WriteRaw<AGENodeType>(Data.Type);
			Serializer->WriteRaw<Vector2>(Data.Size);
			if (Data.NextNode)
			{
				Serializer->WriteRaw<bool>(true);
				Serializer->WriteRaw<uint64_t>((uint64_t)Data.NextNode->ID);
			}
			else
			{
				Serializer->WriteRaw<bool>(false);
			}
			Serializer->WriteString(Data.State);
			Serializer->WriteString(Data.SavedState);
			Serializer->WriteObject<NodeArguments>(Data.FunctionArgs);
			Serializer->WriteRaw<bool>(Data.bIsBeginPlay);
			Serializer->WriteRaw<bool>(Data.bIsOnUpdate);
			Serializer->WriteObject<AGEFunction< AGENode, ScriptableEntity>>(Data.Func);
		}

		static void Deserialize(DataReader* Serializer, AGENode& Data)
		{
			uint64_t ID;
			uint32_t Color;
			bool HasNextNode;
			std::vector<AGEPin> Inputs;
			std::vector<AGEPin> Outputs;
			Serializer->ReadRaw<uint64_t>(ID);
			Data.ID = ID;
			Serializer->ReadString(Data.Name);
			Serializer->ReadRaw<uint32_t>(Color);
			Data.Color = Color;

			Serializer->ReadArray<AGEPin>(Inputs);
			for (auto& P : Inputs)
			{
				Data.Inputs.emplace_back(CreateRef<AGEPin>(P));
			}
			Serializer->ReadArray<AGEPin>(Outputs);
			for (auto& P : Outputs)
			{
				Data.Outputs.emplace_back(CreateRef<AGEPin>(P));
			}
			Serializer->ReadRaw<AGENodeType>(Data.Type);
			Serializer->ReadRaw<Vector2>(Data.Size);
			Serializer->ReadRaw<bool>(HasNextNode);
			if (HasNextNode)
			{
				Serializer->ReadRaw<uint32_t>(Data.NextNodeID);
				
			}
			Serializer->ReadString(Data.State);
			Serializer->ReadString(Data.SavedState);
			Serializer->ReadObject<NodeArguments>(Data.FunctionArgs);
			Serializer->ReadRaw<bool>(Data.bIsBeginPlay);
			Serializer->ReadRaw<bool>(Data.bIsOnUpdate);

			Serializer->ReadObject<AGEFunction< AGENode, ScriptableEntity>>(Data.Func);

			Data.SetNodeFuncArguments();
			Data.CompileOutputPins();
		}

	};
	struct AGENodeLink
	{
		ax::NodeEditor::LinkId ID;
		ax::NodeEditor::PinId StartPinID;
		ax::NodeEditor::PinId EndPinID;

		ImColor Color;

		AGENodeLink() = default;

		AGENodeLink(ax::NodeEditor::LinkId LID, ax::NodeEditor::PinId SPID, ax::NodeEditor::PinId EPID)
			: ID(LID), StartPinID(SPID), EndPinID(EPID), Color(255, 255, 255)
		{

		}

		virtual ~AGENodeLink() = default;

		static void Serialize(DataWriter* Serializer, const AGENodeLink& Data)
		{
			Serializer->WriteRaw<uint64_t>((uint64_t)Data.ID);
			Serializer->WriteRaw<uint64_t>((uint64_t)Data.StartPinID);
			Serializer->WriteRaw<uint64_t>((uint64_t)Data.EndPinID);
			Serializer->WriteRaw<uint32_t>(Data.Color);

		}

		static void Deserialize(DataReader* Serializer, AGENodeLink& Data)
		{
			uint64_t Id;
			uint32_t color;
			Serializer->ReadRaw<uint64_t>(Id);
			Data.ID = Id;
			Serializer->ReadRaw<uint64_t>(Id);
			Data.StartPinID = Id;
			Serializer->ReadRaw<uint64_t>(Id);
			Data.EndPinID = Id;
			Serializer->ReadRaw<uint32_t>(color);
			Data.Color = color;
		}
	};

	struct NodeIdLess
	{
		bool operator()(const ax::NodeEditor::NodeId& lhs, const ax::NodeEditor::NodeId rhs) const
		{
			return lhs.AsPointer() < rhs.AsPointer();
		}
	};
}

