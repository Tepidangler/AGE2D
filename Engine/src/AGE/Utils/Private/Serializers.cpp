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
 * This function takes in a const reference to an AGE::Vector2 and encodes it into a Node object by pushing the x and y coordinates of the Vector2 onto the Node. The encoded Node is then returned.
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
 * @brief Decodes a Node object into an AGE::Vector2.
 *
 * This function attempts to decode the given Node object into an AGE::Vector2. It checks if the node is a sequence and has exactly two elements, then assigns the first element of the node as x value of the vector and the second one as y value. If the conditions are not met, it returns false.
 * 
 * @param[in] node The Node object to be decoded.
 * @param[out] rhs The AGE::Vector2 that will store the decoded values.
 * @return True if the decoding was successful, False otherwise.
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
 * This function takes in a const reference to an AGE::Vector3 object and encodes it into a Node object by pushing the x, y, and z values of the vector onto the node.
 * The encoded Node is then returned.
 * @param rhs The Vector3 object to be encoded.
 * @return The encoded Node object containing the x, y, and z values from the input Vector3.
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
 * It checks if the Node is a sequence (i.e., it contains elements) and has exactly three elements. If these conditions are met, it assigns the first element of the Node to rhs.x, the second to rhs.y, and the third to rhs.z. The function returns true if all operations were successful, false otherwise.
 *
 * @param node A const reference to a Node object that should be decoded into an AGE::Vector3 object.
 * @param rhs A reference to an AGE::Vector3 object where the result of the decoding will be stored.
 * 
 * @return Returns true if successful, false otherwise.
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
 * This function takes in a const reference to an AGE::Vector4 and encodes it into a Node object by pushing the x, y, z, and w values of the vector onto the node.
 * 
 * @param rhs The input Vector4 to be encoded.
 * @return Returns a Node object containing the encoded data from the input Vector4.
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
 * It checks if the node is a sequence and has exactly four elements. If it does, it assigns the first three elements of the node (interpreted as floats) to x, y, and z properties of the Vector4 respectively, and the fourth element to w property. 
 * The function returns true if the decoding was successful, false otherwise.
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
 * This function takes a reference to an AGE::Texture2D object and encodes it into a Node object. The encoded data is then pushed back onto the node.
 * 
 * @param rhs Reference to the Texture2D object to be encoded.
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
 * @return True if the decoding was successful, false otherwise.
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
 * @param rhs A reference to an AudioSource that needs to be encoded.
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
 * This function takes in a const reference to a Node object and attempts to decode it into 
 * an instance of AGE::Ref<AGE::AudioSource>. If the node is not a sequence or if it's empty, 
 * the function returns false indicating failure. Otherwise, it sets rhs to the first element in 
 * the Node object and returns true.
 *
 * @param[in] node The input Node object to be decoded.
 * @param[out] rhs The output AGE::Ref<AGE::AudioSource> instance where the decoded data will be stored.
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
 * This function takes in a vector of pairs, where each pair contains a string and a vector of uint8_t values. 
 * It iterates over the input vector, assigning each pair's first element to the node as its key, and the second element to the node as its value. 
 * After processing all pairs, it returns the resulting Node object.
 *
 * @param rhs The vector of pairs to encode into a Node object.
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
 * Otherwise, it iterates over the node fields, extracting the "first" and "second" values into the output vector.
 *
 * @param[in] node The Node object to be decoded.
 * @param[out] rhs The std::vector of pairs where the decoded data will be stored.
 * 
 * @return True if successful, false otherwise.
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
 * This function takes an input vector of uint8_t and encodes it into a Node object by assigning each element of the vector to a corresponding index in the Node object. 
 * The encoding is done using a for loop, where each element from the input vector is assigned to a position in the Node object.
 *
 * @param rhs A const reference to an std::vector<uint8_t> that needs to be encoded into a Node object.
 * @return Returns a Node object which contains the encoded data from the input vector.
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
 * its size is greater than zero, returning false otherwise. If the check passes, it 
 * resizes the vector to match the size of the node and populates it with uint8_t values 
 * obtained by converting each string element in the Node object to an unsigned char. It then 
 * returns true indicating successful decoding.
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
 * This function takes an instance of the AnimationSpecification class and encodes it into a Node object, which is then returned by the function. The encoding process involves pushing back several properties of the AnimationSpecification object onto the Node object in specific order: Name, NumberOfFrames, MovementStatus (cast to int), Width, Height, TextureFilePath, and bIsReadyToLoad.
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
 * @param node The const reference to the Node object to be decoded.
 * @param rhs The reference to the AGE::AnimationSpecification object that will hold the decoded data.
 * 
 * @return Returns true if the Node was successfully decoded, false otherwise.
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
 * @param v The vector to be serialized and appended to the emitter.
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
 * @param Out The YAML emitter to which we are appending the vector data.
 * @param v The Vector3 object whose data is being appended to the emitter.
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
 * This function allows to output an AGE::Vector4 instance in a format that can be easily parsed by YAML parsers.
 * 
 * @param Out The YAML emitter object to which we are appending the vector data.
 * @param v The Vector4 instance from which we want to extract data for output.
 * @return A reference to the modified YAML::Emitter object.
 */
YAML::Emitter& operator <<(YAML::Emitter& Out, const AGE::Vector4& v)
	{
		Out << YAML::Flow;
		Out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return Out;
	}
	/**
 * @brief Overload of the << operator for YAML::Emitter and std::unordered_map<std::string, Ref<Texture2D>>. 
 * This function serializes an unordered map where each key-value pair represents a texture name and its corresponding Texture2D object.
 * @param Out The YAML emitter to which the data is appended.
 * @param um The unordered map of textures to be serialized.
 * @return A reference to the modified YAML emitter.
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
 * This function serializes a vector of Ref<AudioSource> into a YAML emitter in a flow sequence format.
 * 
 * @param Out The YAML emitter to which the data is appended.
 * @param sound The vector of Ref<AudioSource> to be serialized.
 * @return YAML::Emitter& Returns the modified emitter for further use.
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
 * @brief Serializes an animation specification into a YAML emitter.
 *
 * This function takes an instance of AnimationSpecification and serializes its data into a YAML emitter in a specific format. 
 * The output includes the name, number of frames, movement status, width, height, texture file path, and readiness to load of the animation.
 *
 * @param Out A reference to an existing YAML::Emitter object.
 * @param Anim An instance of AnimationSpecification that needs to be serialized.
 * 
 * @return The modified YAML emitter with the serialized data appended at its end.
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
 * @brief Converts a given body type to its string representation.
 *
 * This function takes in an enumeration of type BodyType and returns the corresponding string representation.
 * The possible values for BodyType are Static, Dynamic, and Kinematic. If the input is not one of these three, 
 * it asserts false with a message "Unknown Body Type".
 *
 * @param BodyType The body type to convert to a string.
 * @return A string representation of the given body type. Possible values are: "Static", "Dynamic", and "Kinematic".
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
 * This function takes in a string and converts it into the equivalent RigidBody2D type. It supports three types: "Static", "Dynamic" and "Kinematic". If an unknown string is passed, it asserts false and returns Static as default.
 * 
 * @param BodyTypeString The string to be converted.
 * @return The corresponding RigidBody2D type.
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
 *  This constructor initializes the m_Scene member variable with the provided scene reference.
 *  
 *  @param S A const reference to a Ref<Scene> object representing the scene to be serialized.
 */
SceneSerializer::SceneSerializer(const Ref<Scene>& S)
		:m_Scene(S)
	{
	}

	/**
 * @brief Serializes an entity to a YAML emitter object.
 * 
 * This function serializes the given entity into a YAML emitter object, which can be written to a file or string. 
 * The serialization includes components such as IDComponent, TagComponent, CameraComponent, TransformComponent, etc., if they exist on the entity.
 * 
 * @param Out A reference to the YAML emitter object where the serialized data will be stored.
 * @param E The entity to be serialized. It must have at least an IDComponent.
 */
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
			[[maybe_unused]] auto& SubTexture = E.GetComponent<SpriteRendererComponent>().SubTexture;
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

			Out << YAML::Key << "Name" << YAML::Value << Name;
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
 * The function extracts the filename from the provided filepath, sets this as the name of the scene, and then writes out the scene data to the file in YAML format. Each entity in the scene is represented by an entry in the "Entities" sequence.
 * 
 * @param FilePath A string representing the path where the serialized scene should be saved.
 * 
 * @return void
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
 * @brief Constructs a new instance of the ProjectSerializer class with the given project reference.
 * 
 * @param Project The project to be serialized and stored in this object.
 */
ProjectSerializer::ProjectSerializer(Ref<Project> Project)
		:m_Project(Project)
	{

	}
	/**
 * @brief Serializes the project configuration and information into a YAML file.
 *
 * This function serializes the project's configuration and information into a YAML file at the specified path. 
 * The configuration includes details about the project such as its name, starting scene, asset directory, C++ namespace, copyright notice, audio engine used, renderer used, quest filepath, config filepath, and built scenes.
 *
 * @param FilePath The path to the YAML file where the serialized data will be written.
 * 
 * @return Returns true if the serialization was successful, false otherwise. In this case, it always returns true as there are no exceptions that could cause a failure.
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
 * This function reads the contents of a YAML file and populates the internal configuration and info structures with data from the file.
 * If the file cannot be loaded, an error message is logged and false is returned.
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
 * This function attempts to deserialize a binary file located at the given path into the current project state. It returns true if the operation was successful, and false otherwise.
 * 
 * @param FilePath The path of the binary file to be deserialized.
 * @return True if the binary file was successfully deserialized, false otherwise.
 */
bool ProjectSerializer::DeserializeBinary(const std::filesystem::path& FilePath)
	{
		return false;
	}

}