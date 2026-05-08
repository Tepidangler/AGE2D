#include "AGEpch.hpp"
#include "Core/Public/App.h"
#include "Utils/Public/Serializers.h"
#include "Scene/Public/Entity.h"
#include "Scene/Public/Components.h"
#include "Controllers/Public/CameraController.h"
#include "Controllers/Public/PlayerController.h"
#include "Controllers/Public/AudioController.h"
#include "Characters/Public/Character.h"
#include "Quests/Public/QuestComponent.h"
#include "Serializers/Public/DataWriter.h"
#include "Serializers/Public/DataReader.h"
#include "Sprite/Public/SpriteAPI.h"
#include "Animation/Public/Animation.h"

#include "Assets/Public/AssetManager.h"
#include <yaml-cpp/yaml.h>

namespace YAML
{
	template<>
	struct convert<AGE::Vector2>
	{
		/**
 * @brief Encodes a 2D vector into a Node object.
 *
 * This function takes a const reference to an AGE::Vector2 object and encodes it into a Node object by pushing the x and y coordinates of the Vector2 into the Node. The encoded Node is then returned.
 *
 * @param rhs The 2D vector to be encoded.
 * @return The encoded Node containing the x and y coordinates of the input Vector2.
 */
static Node encode(const AGE::Vector2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);

			return node;
		}

		/**
 * @brief Decodes a Node object into an AGE::Vector2 object.
 *
 * This function attempts to decode the given Node object into an AGE::Vector2 object. 
 * The Node object should be a sequence with exactly two elements, where each element is convertible to float.
 * If the input Node object meets these requirements, it will be successfully decoded and true will be returned. Otherwise, false will be returned.
 *
 * @param node The Node object to be decoded.
 * @param rhs The AGE::Vector2 object where the decoded data will be stored.
 * 
 * @return True if the input Node object was successfully decoded into an AGE::Vector2 object, false otherwise.
 */
static bool decode(const Node& node, AGE::Vector2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
			{
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<AGE::Vector3>
	{
		/**
 * @brief Encodes a Vector3 object into a Node object.
 * 
 * This function takes an instance of the AGE::Vector3 class and encodes its x, y, and z values into a Node object. The encoded data is then returned as a Node object.
 * 
 * @param rhs An instance of the AGE::Vector3 class to be encoded.
 * @return Node Returns a Node object containing the encoded Vector3 data (x, y, z).
 */
static Node encode(const AGE::Vector3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);

			return node;
		}

		/**
 * @brief Decodes a Node object into an AGE::Vector3 object.
 *
 * This function takes in a const reference to a Node object and a reference to an AGE::Vector3 object. 
 * It checks if the Node is a sequence and has exactly three elements (x, y, z). If these conditions are met, it assigns the x, y, and z values of the Node to the Vector3 object and returns true. Otherwise, it returns false.
 *
 * @param node The input Node object to be decoded.
 * @param rhs The output AGE::Vector3 object where the decoded data will be stored.
 * 
 * @return True if the Node was successfully decoded into an AGE::Vector3, False otherwise.
 */
static bool decode(const Node& node, AGE::Vector3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
			{
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};


	template<>
	struct convert<AGE::Vector4>
	{
		/**
 * @brief Encodes a Vector4 into a Node object.
 * 
 * This function takes an instance of the AGE::Vector4 class and encodes its four components (x, y, z, w) into a Node object. The encoded data is pushed back onto the node in that order.
 * @param rhs The Vector4 to be encoded.
 * @return Node containing the encoded data.
 */
static Node encode(const AGE::Vector4& rhs)
		{
			Node node;

			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);

			return node;
		}

		/**
 * @brief Decodes a Node object into an AGE::Vector4.
 *
 * This function takes in a const reference to a Node object and a reference to an AGE::Vector4. 
 * It checks if the Node is a sequence (i.e., it contains elements) and if its size is equal to 4. 
 * If these conditions are met, it proceeds to decode the values from the Node into the Vector4. 
 * The function returns true if successful, false otherwise.
 *
 * @param node A const reference to a Node object.
 * @param rhs A reference to an AGE::Vector4.
 * @return True if successfully decoded, false otherwise.
 */
static bool decode(const Node& node, AGE::Vector4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
			{
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
	template<>
	struct convert<AGE::Ref<AGE::Texture2D>>
	{
		/**
 * @brief Encodes a texture into a Node object.
 * 
 * This function takes in a reference to an AGE::Texture2D object and encodes it into a Node object. The encoded data is then pushed back onto the Node object.
 * 
 * @param rhs Reference to an AGE::Texture2D object to be encoded.
 * @return Encoded texture as a Node object.
 */
static Node encode(const AGE::Ref<AGE::Texture2D>& rhs)
		{
			Node node;

			node.push_back(rhs);

			return node;
		}

		/**
 * @brief Decodes a Node object into an AGE::Ref<AGE::Texture2D>.
 *
 * This function checks if the input node is a sequence and has exactly one element. If it does, 
 * it attempts to convert that single element into an AGE::Ref<AGE::Texture2D> and assigns it to rhs. 
 * The function returns true on success and false otherwise.
 *
 * @param[in] node The Node object to decode.
 * @param[out] rhs The AGE::Ref<AGE::Texture2D> to store the result in.
 * @return True if the operation was successful, false otherwise.
 */
static bool decode(const Node& node, AGE::Ref<AGE::Texture2D>& rhs)
		{
			if (!node.IsSequence() || node.size() != 1)
			{
				return false;
			}

			rhs = node[0].as<AGE::Ref<AGE::Texture2D>>();
			return true;
		}
	};
	template<>
	struct convert<AGE::Ref<AGE::AudioSource>>
	{
		/**
 * @brief Encodes an audio source into a Node object.
 * 
 * This function takes in a reference to an AudioSource and encodes it into a Node object. The encoded data is then pushed back onto the Node object.
 * 
 * @param rhs A reference to an AudioSource object that needs to be encoded.
 * @return Returns a Node object containing the encoded audio source.
 */
static Node encode(const AGE::Ref<AGE::AudioSource>& rhs)
		{
			Node node;

			node.push_back(rhs);

			return node;
		}

		/**
 * @brief Decodes a Node object into an AGE::Ref<AGE::AudioSource>.
 *
 * This function attempts to decode the given Node object into an instance of 
 * AGE::Ref<AGE::AudioSource>. If the node is not a sequence or if it's empty, 
 * the function returns false indicating failure. Otherwise, it assigns the first 
 * element of the node to rhs and returns true.
 *
 * @param[in] node The Node object to be decoded.
 * @param[out] rhs The AGE::Ref<AGE::AudioSource> where the decoded data will be stored.
 * @return True if successful, false otherwise.
 */
static bool decode(const Node& node, AGE::Ref<AGE::AudioSource>& rhs)
		{
			if (!node.IsSequence() || node.size() <= 0)
			{
				return false;
			}

			rhs = node[0].as<AGE::Ref<AGE::AudioSource>>();
			return true;
		}
	};

	template<>
	struct convert <std::vector<std::pair<std::string, std::vector<uint8_t>>>>
	{
		/**
 * @brief Encodes a vector of pairs into a Node object.
 *
 * This function takes in a const reference to a std::vector of std::pairs, where each pair contains a string and a vector of uint8_t. 
 * It iterates over the input vector, assigning each pair's first element to the node as a key and its second element to the node as value. 
 * After processing all pairs, it returns the encoded Node object.
 *
 * @param rhs The const reference to std::vector of std::pairs to be encoded.
 * @return The encoded Node object.
 */
static Node encode(const std::vector<std::pair<std::string, std::vector<uint8_t>>>& rhs)
		{
			Node node;
			for (size_t i = 0; i < rhs.size(); i++)
			{
				node = rhs[i].first;
				node = rhs[i].second;
				node.push_back(node);
			}
			return node;
		}

		/**
 * @brief Decodes a Node object into a vector of pairs.
 *
 * This function takes in a const reference to a Node object and a reference to a 
 * std::vector of std::pair<std::string, std::vector<uint8_t>>. It first resizes the output vector based on the size of the input node.
 * Then it checks if the "second" field in the node is a sequence and has more than zero elements. If not, it returns false. 
 * Otherwise, it iterates over each element in the node, checking if the key is a scalar string equal to either "first" or "second". 
 * For each matching key-value pair, it updates the corresponding field in Pair and adds Pair to rhs at index i. Finally, it returns true.
 *
 * @param[in] node The Node object to be decoded.
 * @param[out] rhs The output vector of pairs.
 * 
 * @return True if the function successfully decodes the node and false otherwise.
 */
static bool decode(const Node& node, std::vector<std::pair<std::string, std::vector<uint8_t>>>& rhs)
		{		
			rhs.resize(node.size()*(uint64_t)(.5f));
  			std::cout << Dump(node) << std::endl;
			if (!node["second"].IsSequence() || node["second"].size() <= 0)
			{
				return false;
			}
			size_t i = 0;
			std::pair<std::string, std::vector<uint8_t>> Pair;
			for (auto& N: node)
			{
				if (N.first.IsScalar() && N.first.as<std::string>() == "first")
				{
					Pair.first = N.second.as<std::string>();
				}
				else if (N.first.IsScalar() && N.first.as<std::string>() == "second")
				{
					Pair.second = N.second.as<std::vector<uint8_t>>();
					rhs[i] = Pair;
					i++;
				}
			}
			return true;
		}
	};

	template<>
	struct convert <std::vector<uint8_t>>
	{
		/**
 * @brief Encodes a vector of uint8_t into a Node object.
 *
 * This function takes an input vector of uint8_t and encodes it into a Node object by assigning each element in the vector to a corresponding index in the Node object. 
 * The encoding process is straightforward: for every i-th element in the input vector, we set the i-th value of the Node object to be equal to this element.
 *
 * @param rhs A const reference to an std::vector<uint8_t> that contains the data to be encoded.
 * 
 * @return Returns a Node object containing the encoded data from the input vector.
 */
static Node encode(const std::vector<uint8_t>& rhs)
		{
			Node node;
			for (size_t i = 0; i < rhs.size(); i++)
			{
				node[i] = rhs[i];
			}
			return node;
		}

		/**
 * @brief Decodes a Node object into an std::vector of uint8_t values.
 *
 * This function takes in a const reference to a Node object and a reference to an 
 * std::vector of unsigned char (uint8_t). It checks if the node is a sequence and 
 * has size greater than zero, returning false otherwise. If the check passes, it resizes 
 * the vector to match the size of the node and fills in the values by converting each 
 * string value from the Node object into its corresponding unsigned char value. Finally, 
 * it returns true indicating successful decoding.
 *
 * @param[in] node The input Node object to be decoded.
 * @param[out] rhs The output vector of uint8_t values.
 *
 * @return True if the function successfully decodes the Node, false otherwise.
 */
static bool decode(const Node& node, std::vector<uint8_t>& rhs)
		{
			if (!node.IsSequence() || node.size() <= 0)
			{
				return false;
			}

			rhs.resize(node.size());
			for (size_t i = 0; i < node.size(); i++)
			{
				//part of this potential workaround
				std::string s = node[i].as<std::string>();
				rhs[i] = (unsigned char)*s.data();
			}

			return true;
		}
	};
	template<>
	struct convert <AGE::AnimationSpecification>
	{
		/**
 * @brief Encodes an AnimationSpecification object into a Node object.
 * 
 * This function takes an instance of the AnimationSpecification class and encodes it into a Node object, which is then returned by the function. The encoding process involves pushing back several properties of the AnimationSpecification object onto the Node object in specific order: Name, NumberOfFrames, MovementStatus, Width, Height, TextureFilePath, bIsReadyToLoad.
 * 
 * @param rhs The AnimationSpecification object to be encoded.
 * @return A Node object containing the encoded data from the AnimationSpecification object.
 */
static Node encode(const AGE::AnimationSpecification& rhs)
		{
			Node node;
			node.push_back(rhs.Name);
			node.push_back(rhs.NumberOfFrames);
			node.push_back((int)rhs.MovementStatus);
			node.push_back(rhs.Width);
			node.push_back(rhs.Height);
			node.push_back(rhs.Texture->GetTextureFilePath());
			node.push_back(rhs.bIsReadyToLoad);

			return node;
		}

		/**
 * @brief Decodes a Node object into an AnimationSpecification object.
 *
 * This function takes in a const reference to a Node object and a reference to an 
 * AGE::AnimationSpecification object. It checks if the Node is a sequence and if it has any elements. If these conditions are not met, it returns false. Otherwise, it populates the AnimationSpecification with data from the Node. The function then returns true.
 *
 * @param node The input Node to be decoded.
 * @param rhs The output AnimationSpecification object that will hold the decoded data.
 * 
 * @return Returns true if successful, false otherwise.
 */
static bool decode(const Node& node, AGE::AnimationSpecification& rhs)
		{
			if (!node.IsSequence() || node.size() <= 0)
			{
				return false;
			}

			rhs.Name = node[0].as<std::string>();
			rhs.NumberOfFrames = node[1].as<int>();
			rhs.MovementStatus = (AGE::CharMovementStatus)node[2].as<int>();
			rhs.Width = node[3].as<float>();
			rhs.Height = node[4].as<float>();
			rhs.Texture = AGE::Texture2D::Create(node[5].as<std::string>());
			rhs.bIsReadyToLoad = node[6].as<bool>();

			return true;
		}
	};
}

namespace AGE
{
	/**
 * @brief Overload of the << operator for YAML::Emitter and AGE::Vector2.
 * This function allows to output an instance of Vector2 in a format that can be easily parsed by YAML.
 * 
 * @param Out The YAML emitter object to which we are appending data.
 * @param v The Vector2 object whose values we want to output.
 * @return A reference to the modified YAML::Emitter object.
 */
YAML::Emitter& operator <<(YAML::Emitter& Out, const AGE::Vector2& v)
	{
		Out << YAML::Flow;
		Out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
		return Out;
	}

	/**
 * @brief Overload of the << operator for YAML::Emitter and AGE::Vector3.
 * This function allows to output an AGE::Vector3 object in a format that can be easily parsed by YAML.
 * 
 * @param Out The YAML emitter to which the vector will be appended.
 * @param v The Vector3 object to be appended to the YAML emitter.
 * @return A reference to the modified YAML::Emitter.
 */
YAML::Emitter& operator <<(YAML::Emitter& Out, const AGE::Vector3& v)
	{
		Out << YAML::Flow;
		Out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return Out;
	}
	/**
 * @brief Overload of the << operator for YAML::Emitter and AGE::Vector4.
 * This function allows to output an AGE::Vector4 object in a format that can be easily parsed by YAML.
 * 
 * @param Out The YAML emitter to which the vector will be appended.
 * @param v The Vector4 object to be appended to the emitter.
 * @return YAML::Emitter& Reference to the modified emitter.
 */
YAML::Emitter& operator <<(YAML::Emitter& Out, const AGE::Vector4& v)
	{
		Out << YAML::Flow;
		Out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return Out;
	}
	/**
 * @brief Overload of the << operator for YAML::Emitter and std::unordered_map<std::string, Ref<Texture2D>>. 
 * This function serializes an unordered map where keys are strings and values are references to Texture2D objects into a YAML format.
 * @param Out The emitter object that will be used for outputting the serialized data.
 * @param um The unordered map of string-to-Texture2D reference pairs which needs to be serialized.
 * @return Returns the modified emitter object with the serialized data included.
 */
YAML::Emitter& operator <<(YAML::Emitter& Out, const std::unordered_map<std::string, Ref<Texture2D>>& um)
	{
		Out << YAML::Flow;
		for (auto KV : um)
		{
			Out << YAML::BeginMap << YAML::Key << KV.first << YAML::Value << KV.second->GetTextureFilePath() << YAML::EndMap;
		}
		return Out;
	}
	/**
 * @brief Overload of the << operator for YAML::Emitter and std::vector<Ref<AudioSource>>.
 * This function serializes a vector of Ref<AudioSource> objects into a YAML sequence, where each element is the file path of an AudioSource object.
 * 
 * @param Out The YAML emitter to which the data will be appended.
 * @param sound A reference to the std::vector<Ref<AudioSource>> that needs to be serialized.
 * @return YAML::Emitter& Returns a reference to the modified YAML emitter.
 */
YAML::Emitter& operator <<(YAML::Emitter& Out, const std::vector<Ref<AudioSource>>& sound)
	{
		Out << YAML::Flow;
		Out << YAML::BeginSeq;
		for (Ref<AudioSource> S : sound)
		{
			Out << S->GetFilePath();
		}
		Out << YAML::EndSeq;
		return Out;
	}

	/**
 * @brief Overload of the << operator for outputting a vector of pairs to an Emitter.
 *
 * This function takes as input a reference to an Emitter and a vector of pairs, where each pair contains a string and a sequence of uint8_t values. 
 * It outputs the data in a specific format using the << operator on the Emitter object. The output is formatted as a flow map with keys "first" and "second". 
 * Each pair's second value is outputted as a sequence of characters, converted from uint8_t values.
 *
 * @param[in] Bindings - A vector of pairs to be outputted.
 * @return Reference to the Emitter object after all data has been written.
 */
YAML::Emitter& operator <<(YAML::Emitter& Out, const std::vector<std::pair<std::string, std::vector<uint8_t>>> Bindings)
	{
		Out << YAML::Flow;
		Out << YAML::BeginMap;
		for (auto& B : Bindings)
		{
			Out << YAML::Key << "first"  << YAML::Value << B.first << YAML::Key << "second" << YAML::Value << YAML::BeginSeq;
			//Ignorant workaround, but this should be looked into for fixing
			for (auto& i : B.second)
			{
				unsigned char c = i;
				std::string s;
				s += (char)c;
				Out << s;
			}
			Out << YAML::EndSeq;
		}
		Out << YAML::EndMap;
		return Out;
	}

	/**
 * @brief This function overloads the << operator to serialize an object of type AGE::AnimationSpecification into a YAML emitter.
 * 
 * @param[in,out] Out The YAML emitter that will be used for outputting the data.
 * @param[in] Anim The animation specification whose details are to be serialized.
 * 
 * @return A reference to the modified YAML emitter.
 */
YAML::Emitter& operator <<(YAML::Emitter& Out, AGE::AnimationSpecification Anim)
	{
		Out << YAML::Flow;
		Out << YAML::BeginSeq;
		Out << Anim.Name;
		Out << Anim.NumberOfFrames;
		Out << (int)Anim.MovementStatus;
		Out << Anim.Width;
		Out << Anim.Height;
		Out << Anim.Texture->GetTextureFilePath();
		Out << Anim.bIsReadyToLoad;
		Out << YAML::EndSeq;
	
		return Out;
	}

	

	/**
 * @brief Converts a RigidBody2D body type to its string representation.
 *
 * This function takes in an enumerated value of the `BodyType` and returns its corresponding string representation.
 * The possible values are "Static", "Dynamic" or "Kinematic". If the input is not one of these, it asserts false 
 * with a message indicating that the body type is unknown.
 *
 * @param BodyType - An enumerated value representing the body type to convert.
 * @return A string representation of the body type. Possible values are "Static", "Dynamic" or "Kinematic".
 */
static std::string RigidBody2DBodyTypeToString(BodyType BodyType)
	{
		switch (BodyType)
		{
		case BodyType::Static:
		{
			return "Static";
		}
		case BodyType::Dynamic:
		{
			return "Dynamic";
		}
		case BodyType::Kinematic:
		{
			return "Kinematic";
		}
		}

		CoreLogger::Assert(false, "Unknown Body Type");
		return {};
	}

	/**
 * @brief Converts a string to its corresponding RigidBody2D type.
 *
 * This function takes in a string and converts it into the equivalent RigidBody2D type. 
 * The possible inputs are "Static", "Dynamic" or "Kinematic". If an unknown input is given, 
 * the function will assert with a message of "Unknown Body Type".
 *
 * @param BodyTypeString A string representing the body type to be converted.
 * @return The corresponding RigidBody2D type if successful, else it returns BodyType::Static.
 */
static BodyType RigidBody2DTypeFromString(const std::string& BodyTypeString)
	{
		if (BodyTypeString == "Static")
		{
			return BodyType::Static;
		}
		if (BodyTypeString == "Dynamic")
		{
			return BodyType::Dynamic;
		}
		if (BodyTypeString == "Kinematic")
		{
			return BodyType::Kinematic;
		}

		CoreLogger::Assert(false, "Unknown Body Type");
		
		return BodyType::Static;

	}

	/**
 *  @brief Constructs a SceneSerializer object with the given scene reference.
 *  
 *  This constructor takes a const reference to a Scene object and assigns it to m_Scene member variable.
 *  
 *  @param S A constant reference to a Scene object.
 */
SceneSerializer::SceneSerializer(const Ref<Scene>& S)
		:m_Scene(S)
	{
	}

	Unknown
static void SerializeEntity(YAML::Emitter& Out, Entity E)
	{
		CoreLogger::Assert(E.HasComponent<IDComponent>(), "No ID Component present!");
		Out << YAML::BeginMap;
		Out << YAML::Key << "Entity";
		Out << YAML::Value << (uint64_t)E.GetUUID();


		if (E.HasComponent<TagComponent>())
		{
			Out << YAML::Key << "TagComponent";
			Out << YAML::BeginMap;

			auto& Tag = E.GetComponent<TagComponent>().Tag;
			Out << YAML::Key << "Tag";
			Out << YAML::Value << Tag;

			Out << YAML::EndMap;
		}	

		if (E.HasComponent<CameraComponent>())
		{
			Out << YAML::Key << "CameraComponent";
			Out << YAML::BeginMap;

			auto& CamComp = E.GetComponent<CameraComponent>();
			auto& Camera = E.GetComponent<CameraComponent>().Cam;

			Out << YAML::Key << "Camera" << YAML::Value;
			Out << YAML::BeginMap;
			Out << YAML::Key << "ProjectionType" << YAML::Value << (int)Camera.GetProjectionType();
			Out << YAML::Key << "PerspectiveFOV" << YAML::Value << Camera.GetPerspectiveVerticalFOV();
			Out << YAML::Key << "PerspectiveNear" << YAML::Value << Camera.GetPerspectiveNearClip();
			Out << YAML::Key << "PerspectiveFar" << YAML::Value << Camera.GetPerspectiveFarClip();
			Out << YAML::Key << "OrthographicSize" << YAML::Value << Camera.GetOrthographicSize();
			Out << YAML::Key << "OrthographicNear" << YAML::Value << Camera.GetOrthographicNearClip();
			Out << YAML::Key << "OrthographicFar" << YAML::Value << Camera.GetOrthographicFarClip();
			Out << YAML::EndMap;

			Out << YAML::Key << "Primary" << YAML::Value << CamComp.bPrimary;
			Out << YAML::Key << "FixedAspectRatio" << YAML::Value << CamComp.bFixedAspectRatio;
			Out << YAML::Key << "Recording" << YAML::Value << CamComp.bRecording;
			Out << YAML::EndMap;

		}

		if (E.HasComponent<TransformComponent>())
		{
			Out << YAML::Key << "TransformComponent";
			Out << YAML::BeginMap;

			auto& Translation = E.GetComponent<TransformComponent>().Translation;
			auto& Rotation = E.GetComponent<TransformComponent>().Rotation;
			auto& Scale = E.GetComponent<TransformComponent>().Scale;

			Out << YAML::Key << "Translation" << YAML::Value << Translation;
			Out << YAML::Key << "Rotation" << YAML::Value << Rotation;
			Out << YAML::Key << "Scale" << YAML::Value << Scale;
			Out << YAML::EndMap;
		}

		if (E.HasComponent<SpriteRendererComponent>())
		{
			Out << YAML::Key << "SpriteRendererComponent";
			Out << YAML::BeginMap;

			auto& Color = E.GetComponent<SpriteRendererComponent>().Color;
			auto& MovementStatus = E.GetComponent<SpriteRendererComponent>().MovementStatus;
			auto& Texture = E.GetComponent<SpriteRendererComponent>().Texture;
			auto& Anims = E.GetComponent<SpriteRendererComponent>().AnimTextures;
			auto& SubTexture = E.GetComponent<SpriteRendererComponent>().SubTexture;
			auto& TileID = E.GetComponent<SpriteRendererComponent>().TileID;
			auto& Width = E.GetComponent<SpriteRendererComponent>().TileWidth;
			auto& Height = E.GetComponent<SpriteRendererComponent>().TileHeight;
			auto& Location = E.GetComponent<SpriteRendererComponent>().TileLocation;
			auto& IsTile = E.GetComponent<SpriteRendererComponent>().bTile;
			auto& Layer = E.GetComponent<SpriteRendererComponent>().TilesLayer;
			//auto& Color = E.GetComponent<SpriteRendererComponent>().Color;
			//auto& Color = E.GetComponent<SpriteRendererComponent>().Color;

			Out << YAML::Key << "Color" << YAML::Value << Color;
			Out << YAML::Key << "MovementStatus" << YAML::Value << (int)MovementStatus;
			if (Anims.size() > 0)
			{
				Out << YAML::Key << "Animations" << YAML::BeginSeq;
				for (auto& A : Anims)
				{
					Out << YAML::Value << A;
				}
				Out << YAML::EndSeq;

			}
			if (Texture)
			{
				Out << YAML::Key << "Texture" << YAML::Value << Texture->GetTextureFilePath();
			}
			if (TileID > -1)
			{
				Out << YAML::Key << "TileID" << YAML::Value << TileID;
				Out << YAML::Key << "TileLocation" << YAML::Value << Location;
				Out << YAML::Key << "TileWidth" << YAML::Value << Width;
				Out << YAML::Key << "TileHeight" << YAML::Value << Height;
				Out << YAML::Key << "Layer" << YAML::Value << Layer;
			}
			Out << YAML::Key << "IsTile" << YAML::Value << IsTile;
			Out << YAML::EndMap;
		}

		if (E.HasComponent<TileMapRendererComponent>())
		{
			Out << YAML::Key << "TileMapRendererComponent";
			Out << YAML::BeginMap;

			auto& Name = E.GetComponent<TileMapRendererComponent>().Name;
			auto& Path = E.GetComponent<TileMapRendererComponent>().TileMapPath;

			Out << YAML::Key << "Name" << YAML::Value << Name;
			Out << YAML::Key << "Path" << YAML::Value << Path;
			Out << YAML::Key << "FirstPass" << YAML::Value << E.GetComponent<TileMapRendererComponent>().bFirstPass;
			Out << YAML::EndMap;
		}
		if (E.HasComponent<CircleRendererComponent>())
		{
			Out << YAML::Key << "CircleRendererComponent";
			Out << YAML::BeginMap;

			auto& Color = E.GetComponent<CircleRendererComponent>().Color;
			auto& Thickness = E.GetComponent<CircleRendererComponent>().Thickness;
			auto& Fade = E.GetComponent<CircleRendererComponent>().Fade;

			Out << YAML::Key << "Color" << YAML::Value << Color;
			Out << YAML::Key << "Thickness" << YAML::Value << Thickness;
			Out << YAML::Key << "Fade" << YAML::Value << Fade;
			Out << YAML::EndMap;
		}

		if (E.HasComponent<NativeScriptComponent>())
		{
			auto& NSC = E.GetComponent<NativeScriptComponent>();
			Out << YAML::Key << "NativeScriptComponent";
			Out << YAML::BeginMap;
			Out << YAML::Key << "ScriptableEntity" << YAML::Value << NSC.Instance->GetScriptableEntityType();
			Out << YAML::EndMap;
		}
		
		if (E.HasComponent<AudioComponent>())
		{
			auto& AC = E.GetComponent<AudioComponent>();
			Out << YAML::Key << "AudioComponent";
			Out << YAML::BeginMap;
			Out << YAML::Key << "SoundFiles" << YAML::Value << AC.Sounds;
			Out << YAML::EndMap;
		}

		if (E.HasComponent<RigidBody2DComponent>())
		{
			Out << YAML::Key << "RigidBody2DComponent";
			Out << YAML::BeginMap;

			auto& RB2D = E.GetComponent<RigidBody2DComponent>();

			Out << YAML::Key << "BodyType" << YAML::Value << RigidBody2DBodyTypeToString(RB2D.Type);
			Out << YAML::Key << "FixedRotation" << YAML::Value << RB2D.FixedRotation;
			Out << YAML::Key << "Interactable" << YAML::Value << RB2D.bInteractable;

			Out << YAML::EndMap;
		}

		if (E.HasComponent<BoxCollider2DComponent>())
		{
			Out << YAML::Key << "BoxCollider2DComponent";
			Out << YAML::BeginMap;

			auto& BC2D = E.GetComponent<BoxCollider2DComponent>();

			Out << YAML::Key << "Offset" << YAML::Value << BC2D.Offset;
			Out << YAML::Key << "Size" << YAML::Value << BC2D.Size;
			Out << YAML::Key << "Density" << YAML::Value << BC2D.Density;
			Out << YAML::Key << "Friction" << YAML::Value << BC2D.Friction;
			Out << YAML::Key << "Restitution" << YAML::Value << BC2D.Restitution;

			Out << YAML::EndMap;
		}
		if (E.HasComponent<CapsuleCollider2DComponent>())
		{
			Out << YAML::Key << "CapsuleCollider2DComponent";
			Out << YAML::BeginMap;

			auto& CC2D = E.GetComponent<CapsuleCollider2DComponent>();

			Out << YAML::Key << "Offset" << YAML::Value << CC2D.Offset;
			Out << YAML::Key << "Radius" << YAML::Value << CC2D.Radius;
			Out << YAML::Key << "Density" << YAML::Value << CC2D.Density;
			Out << YAML::Key << "Friction" << YAML::Value << CC2D.Friction;
			Out << YAML::Key << "Restitution" << YAML::Value << CC2D.Restitution;
			Out << YAML::Key << "GeneratePhysics" << YAML::Value << CC2D.bGeneratePhysicsEvents;

			Out << YAML::EndMap;
		}
		if (E.HasComponent<SegmentCollider2DComponent>())
		{
			Out << YAML::Key << "SegmentCollider2DComponent";
			Out << YAML::BeginMap;

			auto& SC2D = E.GetComponent<SegmentCollider2DComponent>();

			Out << YAML::Key << "Offset" << YAML::Value << SC2D.Offset;
			Out << YAML::Key << "Size" << YAML::Value << SC2D.Size;
			Out << YAML::Key << "Density" << YAML::Value << SC2D.Density;
			Out << YAML::Key << "Friction" << YAML::Value << SC2D.Friction;
			Out << YAML::Key << "Restitution" << YAML::Value << SC2D.Restitution;

			Out << YAML::EndMap;
		}

		Out << YAML::EndMap;

	}

	/**
 * @brief This function serializes the current scene into a YAML file at the specified path.
 * 
 * The function takes in a string parameter representing the file path where the serialized data will be saved. It extracts the filename from the provided file path, sets this as the name of the scene and then proceeds to write the scene details along with all entities into a YAML format.
 *
 * @param FilePath The path to the file where the scene should be serialized.
 */
void SceneSerializer::Serialize(const std::string& FilePath)
	{

		std::string base = FilePath.substr(FilePath.find_last_of("/\\") + 1);
		std::string::size_type const p(base.find_last_of('.'));
		std::string filename = base.substr(0, p);
		m_Scene->m_Name = filename;
		YAML::Emitter Out;

		Out << YAML::BeginMap;
		Out << YAML::Key << "Scene";
		Out << YAML::Value << m_Scene->m_Name;
		Out << YAML::Key << "Entities";
		Out << YAML::Value << YAML::BeginSeq;
		m_Scene->m_Registry.view<entt::entity>().each([&](auto EntityID)
			{
				Entity E = { EntityID, m_Scene.get() };
				if (!E)
				{
					return;
				}

				SerializeEntity(Out, E);
			});

		Out << YAML::EndSeq;
		Out << YAML::EndMap;
		std::ofstream Fout(FilePath, std::ios::out);
		Fout << Out.c_str();
	}

	
bool SceneSerializer::Deserialize(const std::string& FilePath)
	{
		std::ifstream Stream(FilePath);

		std::stringstream StrStream;

		StrStream << Stream.rdbuf();

		YAML::Node Data = YAML::Load(StrStream.str());

		if (!Data["Scene"])
		{
			return false;
		}

		std::string SceneName = Data["Scene"].as<std::string>();
		m_Scene->m_Name = SceneName;

		CoreLogger::Trace("Deserializing Scene: {0}", SceneName);

		auto Entities = Data["Entities"];
		if (Entities)
		{
			for (auto E : Entities)
			{
				uint64_t UUID = E["Entity"].as<uint64_t>();

				std::string Name;
				auto TagComponent = E["TagComponent"];
				if (TagComponent)
				{
					Name = TagComponent["Tag"].as<std::string>();
					CoreLogger::Trace("Deserialized Entity ID: {0}, Name: {1}", UUID, Name);
				}

				Entity DeserializedEntity = m_Scene->CreateEntityWithUUID(UUID,Name);

				auto TransComp = E["TransformComponent"];
				if (TransComp)
				{
					auto& TC = DeserializedEntity.GetComponent<TransformComponent>();

					TC.Translation = TransComp["Translation"].as<AGE::Vector3>();
					TC.Rotation = TransComp["Rotation"].as<AGE::Vector3>();
					TC.Scale = TransComp["Scale"].as<AGE::Vector3>();
				}

				auto CamComp = E["CameraComponent"];
				if (CamComp)
				{
					auto& CC = DeserializedEntity.AddComponent<CameraComponent>();

					auto CamProps = CamComp["Camera"];

					CC.Cam.SetProjectionType((ProjectionType)CamProps["ProjectionType"].as<int>());
					CC.Cam.SetPerspectiveVerticalFOV(CamProps["PerspectiveFOV"].as<float>());
					CC.Cam.SetPerspectiveNearClip(CamProps["PerspectiveNear"].as<float>());
					CC.Cam.SetPerspectiveFarClip(CamProps["PerspectiveFar"].as<float>());
					CC.Cam.SetOrthographicSize(CamProps["OrthographicSize"].as<float>());
					CC.Cam.SetOrthographicNearClip(CamProps["OrthographicNear"].as<float>());
					CC.Cam.SetOrthographicFarClip(CamProps["OrthographicFar"].as<float>());
					CC.bPrimary = CamComp["Primary"].as<bool>();
					CC.bFixedAspectRatio = CamComp["FixedAspectRatio"].as<bool>();
					CC.bRecording = CamComp["Recording"].as<bool>();
				}

				auto TMRC = E["TileMapRendererComponent"];
				if (TMRC)
				{
					auto& Comp = DeserializedEntity.AddComponent<TileMapRendererComponent>();

					Comp.Name = TMRC["Name"].as<std::string>();
					Comp.TileMapPath = TMRC["Path"].as<std::string>();
					Comp.bFirstPass = TMRC["FirstPass"].as<bool>();
				}
				auto SRC = E["SpriteRendererComponent"];
				if (SRC)
				{
					auto& Comp = DeserializedEntity.AddComponent<SpriteRendererComponent>();

					if (SRC["Color"])
					{
						Comp.Color = SRC["Color"].as<AGE::Vector4>();
					}
					if (SRC["MovementStatus"])
					{
						Comp.MovementStatus = (CharMovementStatus)SRC["MovementStatus"].as<int>();
					}
					Comp.bTile = false;
					if (SRC["IsTile"])
					{
						Comp.bTile = SRC["IsTile"].as<bool>();
					}
					if (Comp.bTile)
					{
						Comp.TileID = SRC["TileID"].as<int>();
						Comp.TileWidth = SRC["TileWidth"].as<float>();
						Comp.TileHeight = SRC["TileHeight"].as<float>();
						Comp.TileLocation = SRC["TileLocation"].as<AGE::Vector2>();
						Comp.TilesLayer = SRC["Layer"].as<int>();
					}


					if (SRC["Texture"])
					{
						Comp.Texture = AssetManager::Get().LoadTexture(SRC["Texture"].as<std::string>());
					}

					if (SRC["Animations"])
					{
						auto Anims = SRC["Animations"];

						for (auto A : Anims)
						{
							Comp.AnimTextures.emplace_back(A.as<AnimationSpecification>());
						}

						if (!Comp.AnimTextures.empty())
						{
							Comp.AnimInstance.LoadAnimations(Comp.AnimTextures);
						}
					}
				}

				auto CRC = E["CircleRendererComponent"];
				if (CRC)
				{
					auto& Comp = DeserializedEntity.AddComponent<CircleRendererComponent>();

					Comp.Color = CRC["Color"].as<Vector4>();
					Comp.Thickness = CRC["Thickness"].as<float>();
					Comp.Fade = CRC["Fade"].as<float>();

				}

				auto NSC = E["NativeScriptComponent"];
				if (NSC)
				{

					if (NSC["ScriptableEntity"].as<std::string>() == "PlayerController")
					{
						DeserializedEntity.AddComponent<NativeScriptComponent>().Bind<GameFramework::PlayerController>();
					}

					if (NSC["ScriptableEntity"].as<std::string>() == "CameraController")
					{
						DeserializedEntity.AddComponent<NativeScriptComponent>().Bind<GameFramework::CameraController>();
					}

					if (NSC["ScriptableEntity"].as<std::string>() == "AudioController")
					{
						DeserializedEntity.AddComponent<NativeScriptComponent>().Bind<GameFramework::AudioController>();
					}
					if (NSC["ScriptableEntity"].as<std::string>() == "CharacterComponent")
					{
						DeserializedEntity.AddComponent<NativeScriptComponent>().Bind<GameFramework::Character>();
					}
				}

				auto AC = E["AudioComponent"];
				if (AC)
				{
					for (int i = 0; i < AC["SoundFiles"].size(); i++)
					{
						DeserializedEntity.GetComponent<AudioComponent>().AddSound(CreateRef<AudioSource>(AC["SoundFiles"][i].as<std::string>()));
					}

				}

				auto RB = E["RigidBody2DComponent"];
				if (RB)
				{
					auto& RB2D = DeserializedEntity.AddComponent<RigidBody2DComponent>();
					RB2D.Type = RigidBody2DTypeFromString(RB["BodyType"].as<std::string>());
					RB2D.FixedRotation = RB["FixedRotation"].as<bool>();
					RB2D.bInteractable = RB["Interactable"].as<bool>();
				}

				auto BC = E["BoxCollider2DComponent"];
				if (BC)
				{
					auto& BC2D = DeserializedEntity.AddComponent<BoxCollider2DComponent>();
					BC2D.Offset = BC["Offset"].as<Vector2>();
					BC2D.Size = BC["Size"].as<Vector2>();
					BC2D.Density = BC["Density"].as<float>();
					BC2D.Friction = BC["Friction"].as<float>();
					BC2D.Restitution = BC["Restitution"].as<float>();
				}

				auto CC = E["CapsuleCollider2DComponent"];
				if (CC)
				{
					auto& CC2D = DeserializedEntity.AddComponent<CapsuleCollider2DComponent>();
					CC2D.Offset = CC["Offset"].as<Vector2>();
					CC2D.Radius = CC["Radius"].as<float>();
					CC2D.Density = CC["Density"].as<float>();
					CC2D.Friction = CC["Friction"].as<float>();
					CC2D.Restitution = CC["Restitution"].as<float>();
					CC2D.bGeneratePhysicsEvents = CC["GeneratePhysics"].as<bool>();
				}

				auto SC = E["SegmentCollider2DComponent"];
				if (SC)
				{
					auto& SC2D = DeserializedEntity.AddComponent<SegmentCollider2DComponent>();
					SC2D.Offset = SC["Offset"].as<Vector2>();
					SC2D.Size = SC["Size"].as<Vector2>();
					SC2D.Density = SC["Density"].as<float>();
					SC2D.Friction = SC["Friction"].as<float>();
					SC2D.Restitution = SC["Restitution"].as<float>();
				}
			}
		}


		return true;
	}

	/**
 * @brief Constructs a new instance of the ProjectSerializer class with the given project.
 * 
 * This constructor initializes the m_Project member variable with the provided project object.
 * The function does not perform any specific operations on the project, it simply stores it for later use.
 * 
 * @param Project A reference to a Project object that will be stored and used by this instance of the class.
 */
ProjectSerializer::ProjectSerializer(Ref<Project> Project)
		:m_Project(Project)
	{

	}
	/**
 * @brief Serializes the project configuration and information into a YAML file.
 *
 * This function serializes the project's configuration and information into a YAML file at the specified path. The 
 * configuration includes details such as the project name, starting scene, asset directory, C++ namespace, copyright 
 * notice, audio engine used, renderer used, quest path, config path, and built scenes. It uses the YAML library to 
 * generate the serialized data in a human-readable format. The function returns true if the serialization is successful, 
 * false otherwise.
 *
 * @param FilePath The path where the serialized data will be written.
 * @return True if the serialization was successful, false otherwise.
 */
bool ProjectSerializer::Serialize(const std::filesystem::path& FilePath)
	{
		const auto& Config = m_Project->GetConfig();
		const auto& Info = m_Project->GetInfo();

		YAML::Emitter Out;
		{
			Out << YAML::BeginMap;
			Out << YAML::Key << "Project" << YAML::Value;
			{
				Out << YAML::BeginMap;// Project
				Out << YAML::Key << "Name" << YAML::Value << Config.Name;
				Out << YAML::Key << "StartScene" << YAML::Value << Config.StartScene.string();
				Out << YAML::Key << "AssetDirectory" << YAML::Value << Config.AssetDirectory.string();
				Out << YAML::Key << "CodeNamespace" << YAML::Value << Config.CppNameSpace;
				Out << YAML::Key << "CopyrightNotice" << YAML::Value << Config.CopyrightNotice;
				Out << YAML::Key << "AudioEngine" << YAML::Value << Info.AudioEngine;
				Out << YAML::Key << "Renderer" << YAML::Value << Info.Renderer;
				Out << YAML::Key << "QuestPath" << YAML::Value << Info.QuestFilepath.string();
				Out << YAML::Key << "ConfigPath" << YAML::Value << Info.ConfigFilepath.string();
				Out << YAML::Key << "Scenes" << YAML::Value << YAML::BeginSeq;
				for (auto& S : Info.BuiltScenes)
				{
					Out << S.string();
				}
				Out << YAML::EndSeq;
				Out << YAML::EndMap;
			}
			Out << YAML::EndMap;
		}

		std::ofstream Fout(FilePath);
		Fout << Out.c_str();
		return true;
	}
	
void ProjectSerializer::SerializeBinary(const std::filesystem::path& FilePath)
	{
		AppConfig Config = App::Get().GetAppConfig();
		std::time_t t = std::time(nullptr);
		std::tm tm;
#ifdef AG_PLATFORM_WINDOWS
		localtime_s(&tm, &t);
#else
		localtime_r(&t, &tm);
#endif
		std::ostringstream out;
		out << std::put_time(&tm, "%y%d%m%H%M%S");
		std::map<uint64_t, Scene> SceneMap;
		std::map<uint64_t, Entity> AssetMap;
		size_t CurrentOffset = 0;

		FileStreamWriter Stream(FilePath);
		std::string Header = "AGEPakFile";
		int VersionNumber = 1;
		uint64_t BuildVersion = std::stoull(out.str());

		Stream.WriteString(Header);
		CurrentOffset += strlen(Header.c_str());
		Stream.WriteRaw<int>(VersionNumber);
		CurrentOffset += sizeof(int);
		Stream.WriteRaw<uint64_t>(BuildVersion);
		CurrentOffset += sizeof(uint64_t);
		for (const auto& Scene : std::filesystem::directory_iterator(Config.CurrentProjectPath.string() + "/" + m_Project->GetConfig().Name + "/BuiltScenes/"))
		{
			std::string Result;
#ifdef AG_PLATFORM_WINDOWS
			std::ifstream In(Scene.path().string(), std::ios::in,std::ios::binary);
#else
			std::ifstream In(Scene.path().string(), std::ios::in | std::ios::binary);
#endif
			if (In)
			{
				std::string base = Scene.path().string().substr(Scene.path().string().find_last_of("/\\") + 1);
				std::string::size_type const p(base.find_last_of('.'));
				std::string filename = base.substr(0, p);
				In.seekg(0, std::ios::end);
				Result.resize((size_t)In.tellg());
				CurrentOffset += filename.size();
				CurrentOffset += Result.size();
				Stream.WriteRaw<size_t>(CurrentOffset);
				Stream.WriteString(filename);
			}

		}

		for (const auto& Scene : std::filesystem::directory_iterator(Config.CurrentProjectPath.string()+"/"+m_Project->GetConfig().Name + "/BuiltScenes/"))
		{
			std::string Result;
#ifdef AG_PLATFORM_WINDOWS
			std::ifstream In(Scene.path().string(), std::ios::in,std::ios::binary);
#else
			std::ifstream In(Scene.path().string(), std::ios::in | std::ios::binary);
#endif
			if (In)
			{
				In.seekg(0, std::ios::end);
				Result.resize((size_t)In.tellg());
				In.seekg(0, std::ios::beg);
#ifdef __clang__
				In.read(&Result[0], (long)Result.size());
#else
				In.read(&Result[0], Result.size());
#endif
				Stream.WriteRaw<const char*>(Result.c_str());
			}

		}
	}
	/**
 * @brief Deserializes a project from a YAML file.
 * 
 * This function reads the contents of a YAML file and populates the internal configuration and info structures with data from the file. If the file cannot be loaded, an error message is logged and false is returned.
 * 
 * @param FilePath The path to the YAML file containing project information.
 * @return True if the deserialization was successful, false otherwise.
 */
bool ProjectSerializer::Deserialize(const std::filesystem::path& FilePath)
	{
		auto& Config = m_Project->GetConfig();
		auto& Info = m_Project->GetInfo();

		YAML::Node Data;

		try
		{
			Data = YAML::LoadFile(FilePath.string());
		}
		catch (YAML::ParserException E)
		{
			CoreLogger::Error("Failed to load project file '{0}'\n    {1}", E.what());
			return false;
		}

		auto ProjectNode = Data["Project"];
		if (!ProjectNode)
		{
			return false;
		}

		Config.Name = ProjectNode["Name"].as<std::string>();
		Config.StartScene = ProjectNode["StartScene"].as<std::string>();
		Config.AssetDirectory = ProjectNode["AssetDirectory"].as<std::string>();
		Config.CppNameSpace = ProjectNode["CodeNamespace"].as<std::string>();
		Config.CopyrightNotice = ProjectNode["CopyrightNotice"].as<std::string>();
		Info.AudioEngine = ProjectNode["AudioEngine"].as<uint16_t>();
		Info.Renderer = ProjectNode["Renderer"].as<int>();
		Info.QuestFilepath = ProjectNode["QuestPath"].as<std::string>();
		Info.ConfigFilepath = ProjectNode["ConfigPath"].as <std::string>();
		if (ProjectNode["Scenes"])
		{
			size_t index = 0;
			for (auto S : ProjectNode["Scenes"])
			{
				Info.BuiltScenes.resize(ProjectNode["Scenes"].size());
				Info.BuiltScenes[index] = ProjectNode["Scenes"][index].as<std::string>();
				index++;
			}
		}

		return true;
	}
	/**
 * @brief Deserializes a binary file into the project.
 * 
 * This function attempts to deserialize a binary file located at the given path,
 * and if successful, it populates the current instance of ProjectSerializer with its data.
 * 
 * @param FilePath The path to the binary file to be deserialized.
 * @return True if the operation was successful, false otherwise.
 */
bool ProjectSerializer::DeserializeBinary(const std::filesystem::path& FilePath)
	{
		return false;
	}
	/**
 * @brief Constructor for the IniSerializer class.
 * 
 * This constructor initializes an instance of the IniSerializer class with two vectors, AxisBindings and ActionBindings. These are used to store axis bindings and action bindings respectively.
 * 
 * @param AxisBindings A vector of pairs where each pair consists of a string (representing the name of an axis) and a vector of uint8_t values (representing the binding for that axis).
 * @param ActionBindings A similar vector to AxisBindings but represents action bindings.
 */
IniSerializer::IniSerializer(std::vector<std::pair<std::string, std::vector<uint8_t>>>& AxisBindings, std::vector<std::pair<std::string, std::vector<uint8_t>>>& ActionBindings)
		:m_AxisBindings(AxisBindings), m_ActionBindings(ActionBindings)
	{
	}

	/**
 * @brief Serializes the IniSerializer object into a YAML file.
 *
 * This function serializes the current state of the IniSerializer object into a 
 * YAML file located at the provided path and filename. The serialized data includes 
 * axis bindings and action bindings.
 *
 * @param FilePath The path where the YAML file will be created.
 * @param FileName The name of the YAML file to create.
 *
 * @return True if the serialization was successful, false otherwise. 
 */
bool IniSerializer::Serialize(const std::filesystem::path& FilePath, const std::string& FileName)
	{
		//return false;
		std::string Path = FilePath.parent_path().string() + FileName;
		YAML::Emitter Out;

		Out << YAML::BeginMap;
		Out << YAML::Key << "Ini File" << YAML::Value << YAML::BeginMap;
		Out << YAML::Key << "AxisBindings";
		Out << YAML::Value;
		Out << m_AxisBindings;
		Out << YAML::Key << "ActionBindings";
		Out << YAML::Value;
		Out << m_ActionBindings;
		Out << YAML::EndMap;
		Out << YAML::EndMap;
		std::ofstream Fout(Path, std::ios::out);
		Fout << Out.c_str();
		return true;
	}
	/**
 * @brief Deserializes an INI file into the active project's information.
 * 
 * This function attempts to load and parse an INI file, then deserialize its content into the active Project's Info object.
 * If any of these steps fail, the function returns false.
 * 
 * @param FilePath The path to the directory containing the INI file.
 * @param FileName The name of the INI file itself.
 * @return True if the deserialization was successful; False otherwise.
 */
bool IniSerializer::Deserialize(const std::filesystem::path& FilePath, const std::string& FileName)
	{
		//return false;
		auto Proj = Project::GetActive();
		if (!Proj)
		{
			return false;
		}

		auto& Info = Project::GetActive()->GetInfo();

		YAML::Node Data;
		std::string Path = FilePath.string() + FileName;
		if (!std::filesystem::exists(Path))
		{
			return false;
		}
		try
		{
			Data = YAML::LoadFile(Path);
		}
		catch (YAML::ParserException E)
		{
			CoreLogger::Error("Failed to load ini file '{0}'\n    {1}", E.what());
			return false;
		}

		auto IniNode = Data["Ini File"];
		if (!IniNode)
		{
			return false;
		}

		auto AxisNode = IniNode["AxisBindings"];
		if (AxisNode)
		{
			Info.AxisBindings = AxisNode.as<std::vector<std::pair<std::string, std::vector<uint8_t>>>>();
		}

		auto ActionNode = IniNode["ActionBindings"];
		if (ActionNode)
		{
			Info.ActionBindings = ActionNode.as<std::vector<std::pair<std::string, std::vector<uint8_t>>>>();
		}
		return true;
	}
}