#pragma once
#include "Scene/Public/ScriptableEntity.h"
#include "Structs/Public/Functions.h"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#ifdef AG_PLATFORM_LINUX
#pragma clang diagnostic ignored "-Wnontrivial-memcall"
#endif
#ifdef AG_PLATFORM_WINDOWS
#pragma clang diagnostic ignored "-Wmicrosoft-unqualified-friend"
#endif
#include <utilities/builders.h>
#include <utilities/widgets.h>
#include <imgui_node_editor.h>
#include <rttr/registration>
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wfloat-conversion"
#ifdef AG_PLATFORM_WINDOWS
#pragma GCC diagnostic ignored "-Wmicrosoft-unqualified-friend"
#endif
#include <rttr/registration>
#include <imgui_node_editor.h>
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(push, 0)
#include <rttr/registration>
#include <imgui_node_editor.h>
#pragma warning(pop)
#else
#error "Compiler is not supported with AGE yet"
#endif

namespace AGE
{

	enum class AGEPinType : uint8_t
	{
		Flow,
		Boolean,
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
		Boolean,
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
		rttr::value("Bool",AGE::AGEPinType::Boolean),
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

		/**
 * @brief Default constructor for the AGEPin class.
 *
 * This function initializes an instance of the AGEPin class with its default values. It does not take any parameters and returns nothing.
 */
/**
 * @brief Default constructor for the AGEPin class.
 */
AGEPin() = default;
		/**
 * @brief Constructs an instance of AGEPin with the given parameters.
 * 
 * This constructor initializes a new instance of AGEPin with the provided UUID, name, and type. The Node pointer is initialized to nullptr, Kind is set to Input, and other members are assigned their respective values.
 * @param id Unique identifier for this pin.
 * @param name Name or label associated with this pin.
 * @param type Specifies the kind of data that this pin can handle.
 * 
 * @return AGEPin
 */
/**
 * @brief Constructs an instance of AGEPin with the given parameters.
 * 
 * This constructor initializes a new instance of AGEPin with the provided UUID, name, and type. The Node pointer is set to nullptr, Kind is initialized as Input.
 * 
 * @param id Unique identifier for this pin.
 * @param name Name or label associated with this pin.
 * @param type Specifies the type of the pin (Input, Output, etc.).
 */
AGEPin(UUID id, const char* name, AGEPinType type)
			: ID(id), Node(nullptr), Name(name), Type(type), Kind(ax::NodeEditor::PinKind::Input)
		{

		}

		/**
 * @brief Virtual destructor for the AGEPin class.
 *
 * This function is responsible for freeing any resources that were allocated by the object, such as memory or file handles. It's a virtual function because it can be overridden in derived classes to provide specific cleanup behavior.
 *
 * @return void
 */
/**
 * @brief Virtual destructor for the AGEPin class.
 *
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime, such as memory or file handles. It does not perform any specific actions related to the AGEPIN object itself. 
 *
 * @return void
 */
virtual ~AGEPin() = default;

		/**
 * @brief GetValue is a function that returns an rttr::variant based on the input AGEPinType.
 * 
 * The function takes one parameter, Type of type AGEPinType and returns an rttr::variant. It uses a switch statement to determine which variant to return based on the integer value of Type.
 * 
 * @param Type An enumeration that specifies the type of variant to be returned.
 * @return The function returns an rttr::variant corresponding to the input AGEPinType. If no matching case is found, it returns nullptr.
 */
/**
 * @brief GetValue is a function that returns an rttr::variant based on the input AGEPinType.
 * 
 * @param Type The type of pin to get the value for. This can be one of several types defined in AGEPinType, including Boolean, Integer, Integer16, etc.
 * @return rttr::variant The variant corresponding to the input type. If the type is not recognized, nullptr is returned.
 */
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
				default: return nullptr;
			}
		}

		/**
 * @brief This function serializes an AGEPin object into a DataWriter.
 * 
 * The function writes various properties of the AGEPin, including its ID, NextNodeID, Name, Type, Kind, String, Boolean, Integer, Integer16, Integer64, UInteger16, UInteger32, UInteger64, Value, Vector2D, Vector3D, and Vector4D.
 * It also handles the case where an object pointer is present in the AGEPin. If it exists, a boolean value of true is written to indicate that an object is being serialized, followed by its UUID. Otherwise, a boolean value of false is written.
 * 
 * @param Serializer Pointer to the DataWriter instance which will be used for serialization.
 * @param Data Const reference to the AGEPin object that needs to be serialized.
 */
/**
 * @brief This function serializes an AGEPin object into a DataWriter.
 * 
 * The function writes various properties of the AGEPin to the provided DataWriter, including its ID, NextNodeID, Name, Type, Kind, String, Boolean, Integer, Integer16, Integer64, UInteger16, UInteger32, UInteger64, Value, Vector2D, Vector3D, and Vector4D.
 * 
 * It also checks if the AGEPin has an associated ScriptableEntity object (ObjPtr). If it does, it writes a true flag followed by the UUID of the associated entity; otherwise, it writes a false flag.
 * 
 * @param Serializer Pointer to the DataWriter where the serialized data will be written.
 * @param Data The AGEPin object that needs to be serialized.
 */
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

		/**
 * @brief Deserialize function for the AGEPin structure.
 * This function reads data from a DataReader object and populates an AGEPin object with it. 
 * The function assumes that the DataReader is correctly initialized and ready to read data.
 * 
 * @param Serializer Pointer to the DataReader object which provides the serialized data.
 * @param Data Reference to the AGEPin object where the deserialized data will be stored.
 */
/**
 * @brief Deserialize function for AGEPin data.
 * 
 * This function reads various types of data from a DataReader object and assigns them to an AGEPin object. It handles different types such as uint64_t, UUID, bool, int, int16_t, int64_t, uint16_t, uint32_t, uint64_t, float, Vector2, Vector3, and Vector4.
 * 
 * @param Serializer Pointer to the DataReader object that provides serialized data.
 * @param Data Reference to the AGEPin object where the deserialized data will be stored.
 */
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
		/**
 * @brief Default constructor for NodeArguments class.
 *
 * This function initializes the object with its default state. It is used to create an instance of the NodeArguments class without any arguments.
 *
 * @return An instance of the NodeArguments class with all members initialized to their default values.
 */
/**
 * @brief Default constructor for NodeArguments class.
 */
NodeArguments() = default;
		std::vector<rttr::variant> Args;

		/**
 * \brief This function is responsible for converting a NodeArguments object into a format that can be easily stored or transmitted. 
 * It does this by iterating over each argument in the NodeArguments and writing its type and value to the DataWriter.
 * The type of each argument is written as a byte, followed by the actual data.
 *
 * @param Serializer A pointer to an object that can write raw bytes or strings to a storage medium.
 * @param Data An object containing the arguments to be serialized.
 */
/**
 * @brief This function serializes the given data into a format that can be easily stored or transmitted.
 * 
 * The function takes in two parameters, a DataWriter object and a NodeArguments object. It writes to the DataWriter object based on the type of each argument in the NodeArguments object.
 * 
 * @param Serializer A pointer to an instance of DataWriter that will be used for writing data.
 * @param Data The arguments to serialize, stored as a NodeArguments object.
 * 
 * @return void This function does not return any value. It directly writes the serialized data into the provided DataWriter object.
 */
static void Serialize(DataWriter* Serializer, const NodeArguments& Data)
		{
			Serializer->WriteRaw<uint64_t>(Data.Args.size());
			for (auto& Arg : Data.Args)
			{
				if (Arg.is_type<bool>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::Boolean);
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
				if (Arg.is_type<Ref<AGEFont>>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::Font);
					Serializer->WriteString(Arg.get_value<Ref<AGEFont>>()->GetAtlasTexture()->GetTextureFilePath());
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
				if (Arg.is_type<std::nullptr_t>())
				{
					Serializer->WriteRaw<uint8_t>((uint8_t)NodeArgType::NullType);
					Serializer->WriteRaw<uint8_t>(0);
				}


			}
		}

		"Deserialize function for NodeArguments."

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
					case NodeArgType::Boolean:
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
						Data.Args.emplace_back(AGEFont::GetDefault());
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


		/**
 * @brief Default constructor for AGENode class.
 *
 * This function initializes an instance of the AGENode class with its default values. It does not take any parameters and returns nothing.
 */
/**
 * @brief Default constructor for AGENode class.
 */
AGENode() = default;

		/**
 * @brief Constructs an instance of AGENode with the given parameters.
 * 
 * This constructor initializes a new instance of AGENode with the provided id, name and color. The default color is white (255, 255, 255).
 * The Type is set to Blueprint by default. Size is initialized as 0.f.
 * @param id Unique identifier for this node.
 * @param name Name of the node.
 * @param color Color of the node in RGB format (default: white).
 */
/**
 * @brief Constructs an instance of AGENode with the given id, name and color.
 * 
 * The function initializes a new instance of AGENode with the provided id, name, and color. It also sets the default type to Blueprint and size to 0.
 * 
 * @param id Unique identifier for the node.
 * @param name Name or label associated with the node.
 * @param color Color used to represent the node in visualizations. Defaults to white (255, 255, 255).
 * 
 * @return An instance of AGENode with the provided id, name and color.
 */
AGENode(ax::NodeEditor::NodeId id, const char* name, ImColor color = ImColor(255, 255, 255))
			:ID(id), Name(name), Color(color), Type(AGENodeType::Blueprint), Size(0.f)
		{

		}

		/**
 * @brief Compares the ID of this node with another node's ID.
 *
 * This function compares the ID of the current node (`this->ID.Get()`) 
 * with the ID of the other node passed as an argument (`Other.ID.Get()`).
 * It returns `true` if the ID of this node is less than that of the other, and `false` otherwise.
 *
 * @param Other The AGENode instance to compare with.
 * @return True if the ID of this node is less than that of the other, false otherwise.
 */
/**
 * @brief Compares the ID of this node with another node's ID.
 *
 * This function compares the ID of the current node (`this->ID.Get()`) 
 * with the ID of another node (`Other.ID.Get()`). It returns `true` if 
 * the ID of this node is less than that of the other, and `false` otherwise.
 *
 * @param Other The AGENode instance to compare against.
 * @return True if the ID of this node is less than the other's, false otherwise.
 */
bool operator<(const AGENode& Other) const
		{
			return (ID.Get() < Other.ID.Get());
		}

		/**
 * @brief Virtual destructor for the AGENode class.
 *
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime. It does not take any parameters and returns no value.
 */
/**
 * @brief Virtual destructor for the AGENode class.
 *
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime. It does not return anything and has no parameters.
 */
virtual ~AGENode() = default;

		
/**
 * @brief This function sets the arguments for a node function based on the input parameters.
 * 
 * The function iterates over each argument in `FunctionArgs` and checks its type. If it's a pointer to string or float, it gets the value of that pointer and adds it to `Func.Args`. For an AGEPinType, if it equals Any, it adds the last input's type and value to `Func.Args`.
 * 
 * @param bCanSkip This flag is used to skip certain iterations in the loop based on its value.
 * @return void No return value. The function modifies `Func.Args` directly.
 */
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
			bool success = true;
			for (auto O : Outputs)
			{
				if (!success)
				{
					return success;
				}
				switch (O->Type)
				{
					case AGEPinType::Flow:
					{
						break;
					}
					case AGEPinType::Boolean:
					{
						rttr::variant RetVal = Func.Execute();
						if (RetVal.is_valid())
						{
							O->Boolean = RetVal.get_value<bool>();
							continue;
						}
						success = false;
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
						success = false;
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
						success = false;
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
						success = false;
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
						success = false;
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
						success = false;
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
						success = false;
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
						success = false;
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
						success = false;
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
						success = false;
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
						success = false;
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
						success = false;
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

			return success;
		}
		
/**
 * @brief Serializes an AGENode object into a DataWriter.
 * 
 * This function takes in a pointer to a DataWriter and an instance of the AGENode class, then writes various properties of the node to the DataWriter.
 * 
 * @param Serializer A pointer to an instance of DataWriter that will be used for serialization.
 * @param Data An instance of the AGENode class whose properties are being serialized.
 */
static void Serialize(DataWriter* Serializer, const AGENode& Data)
		{
			std::vector<AGEPin> Inputs(Data.Inputs.size());
			std::vector<AGEPin> Outputs(Data.Outputs.size());

			for (size_t i = 0; i < Inputs.size(); i++)
			{
				Inputs[i] = *Data.Inputs[i].get();
			}
			for (size_t i = 0; i < Outputs.size(); i++)
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

		/**
 * @brief Deserializes an object of type AGENode from a DataReader instance.
 * 
 * This function reads data from the provided serializer and populates an AGENode object with it. The data read includes the node's ID, name, color, inputs, outputs, type, size, next node ID (if any), state, saved state, function arguments, whether the node is in begin play mode, and if it runs on update.
 * 
 * @param Serializer A pointer to a DataReader instance that provides serialized data.
 * @param Data An lvalue reference to an AGENode object where the deserialized data will be stored.
 */
/**
 * @brief Deserializes an object of type AGENode from a DataReader instance.
 * 
 * This function reads various data types and populates the provided AGENode instance with deserialized data. It uses the DataReader to read raw data, strings, arrays, and objects. The function also handles some basic data types like uint64_t, uint32_t, bool, Vector2, etc.
 * 
 * @param Serializer A pointer to a DataReader instance that provides serialized data.
 * @param Data An lvalue reference to an AGENode object where the deserialized data will be stored.
 */
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

		/**
 * @brief Default constructor for AGENodeLink class.
 *
 * This function initializes an instance of the AGENodeLink class with its members set to their default values.
 * The default value is determined by the C++ standard, which may vary depending on the specific type of each member variable.
 * For example, if a member variable is of type int, it will be initialized to 0; for pointers, they will be initialized to nullptr.
 * If you need more control over initialization, consider using an initializer list in the constructor definition.
 *
 * @return An instance of AGENodeLink with all members set to their default values.
 */
/**
 * @brief Default constructor for AGENodeLink class.
 */
AGENodeLink() = default;

		/**
 * @brief Constructs an instance of AGENodeLink with the given LinkId, StartPinId and EndPinId. The color is set to white (255, 255, 255).
 * 
 * @param LID The unique identifier for this link.
 * @param SPID The id of the start pin of this link.
 * @param EPID The id of the end pin of this link.
 */
/**
 * @brief Constructs an instance of AGENodeLink with the given LinkId, StartPinId and EndPinId. The color is set to white (255, 255, 255).
 * @param LID Unique identifier for the link.
 * @param SPID Identifier for the start pin of the link.
 * @param EPID Identifier for the end pin of the link.
 */
AGENodeLink(ax::NodeEditor::LinkId LID, ax::NodeEditor::PinId SPID, ax::NodeEditor::PinId EPID)
			: ID(LID), StartPinID(SPID), EndPinID(EPID), Color(255, 255, 255)
		{

		}

		/**
 * @brief Virtual destructor for the AGENodeLink class.
 *
 * This function is responsible for freeing any resources that were allocated by the object during its lifetime. It does not take any parameters and returns void.
 */
/**
 * @brief Virtual destructor for the AGENodeLink class.
 *
 * This function is responsible for releasing any resources that were acquired by the object during its lifetime. It does not take any parameters and returns void.
 */
virtual ~AGENodeLink() = default;

		/**
 *  @brief This function serializes an AGENodeLink object into a DataWriter.
 *  
 *  The function writes the ID, StartPinID, EndPinID and Color of the given AGENodeLink to the provided DataWriter.
 *  It uses WriteRaw method from DataWriter to write each value as raw binary data.
 *
 *  @param Serializer Pointer to a DataWriter object that will be used for serialization.
 *  @param Data Reference to an AGENodeLink object that needs to be serialized.
 */
/**
 * @brief This function serializes an AGENodeLink object into a DataWriter.
 * 
 * The function writes the ID, StartPinID, EndPinID and Color of the given AGENodeLink to the provided DataWriter.
 * It uses WriteRaw method for each data type (uint64_t, uint32_t) to write the respective values into the serializer.
 * 
 * @param Serializer Pointer to a DataWriter object where the serialized data will be written.
 * @param Data Reference to an AGENodeLink object that needs to be serialized.
 */
static void Serialize(DataWriter* Serializer, const AGENodeLink& Data)
		{
			Serializer->WriteRaw<uint64_t>((uint64_t)Data.ID);
			Serializer->WriteRaw<uint64_t>((uint64_t)Data.StartPinID);
			Serializer->WriteRaw<uint64_t>((uint64_t)Data.EndPinID);
			Serializer->WriteRaw<uint32_t>(Data.Color);

		}

		/**
 * @brief Deserializes data from a DataReader into an AGENodeLink object.
 * 
 * This function reads raw data from the provided DataReader and populates an AGENodeLink object with it. The data read includes IDs for the node link, start pin ID, end pin ID, and color of the link.
 * 
 * @param Serializer A pointer to a DataReader that provides the serialized data.
 * @param Data An AGENodeLink object where the deserialized data will be stored.
 * 
 * @return void
 */
/**
 * @brief Deserialize function for AGENodeLink data structure.
 * This function reads raw data from a DataReader object and populates an AGENodeLink object with the deserialized data.
 * 
 * @param Serializer Pointer to the DataReader object that provides the serialized data.
 * @param Data Reference to the AGENodeLink object where the deserialized data will be stored.
 */
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
		/**
 * @brief Compares two NodeIds for less than comparison.
 *
 * This function compares the underlying pointers of two NodeId objects and returns true if the pointer of lhs is less than that of rhs, otherwise it returns false.
 * 
 * @param lhs The first NodeId to compare.
 * @param rhs The second NodeId to compare.
 * @return True if the pointer of lhs is less than that of rhs, False otherwise.
 */
/**
 * @brief Compares two NodeIds for less than comparison.
 *
 * This function compares the underlying pointers of two NodeId objects and returns true if the left hand side is less than the right hand side, otherwise it returns false.
 * 
 * @param lhs The first NodeId to compare.
 * @param rhs The second NodeId to compare.
 * @return True if lhs < rhs, False otherwise.
 */
bool operator()(const ax::NodeEditor::NodeId& lhs, const ax::NodeEditor::NodeId rhs) const
		{
			return lhs.AsPointer() < rhs.AsPointer();
		}
	};
}

