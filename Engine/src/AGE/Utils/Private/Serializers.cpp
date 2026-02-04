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
		static Node encode(const AGE::Vector2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);

			return node;
		}

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
		static Node encode(const AGE::Vector3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);

			return node;
		}

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
		static Node encode(const AGE::Vector4& rhs)
		{
			Node node;

			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);

			return node;
		}

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
		static Node encode(const AGE::Ref<AGE::Texture2D>& rhs)
		{
			Node node;

			node.push_back(rhs);

			return node;
		}

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
		static Node encode(const AGE::Ref<AGE::AudioSource>& rhs)
		{
			Node node;

			node.push_back(rhs);

			return node;
		}

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
		static Node encode(const std::vector<std::pair<std::string, std::vector<uint8_t>>>& rhs)
		{
			Node node;
			for (int i = 0; i < rhs.size(); i++)
			{
				node = rhs[i].first;
				node = rhs[i].second;
				node.push_back(node);
			}
			return node;
		}

		static bool decode(const Node& node, std::vector<std::pair<std::string, std::vector<uint8_t>>>& rhs)
		{		
			rhs.resize(node.size()*.5f);
  			std::cout << Dump(node) << std::endl;
			if (!node["second"].IsSequence() || node["second"].size() <= 0)
			{
				return false;
			}
			int i = 0;
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
		static Node encode(const std::vector<uint8_t>& rhs)
		{
			Node node;
			for (int i = 0; i < rhs.size(); i++)
			{
				node[i] = rhs[i];
			}
			return node;
		}

		static bool decode(const Node& node, std::vector<uint8_t>& rhs)
		{
			if (!node.IsSequence() || node.size() <= 0)
			{
				return false;
			}

			rhs.resize(node.size());
			for (int i = 0; i < node.size(); i++)
			{
				//part of this potential workaround
				std::string s = node[i].as<std::string>();
				rhs[i] = *s.data();
			}

			return true;
		}
	};
	template<>
	struct convert <AGE::AnimationSpecification>
	{
		static Node encode(const AGE::AnimationSpecification& rhs)
		{
			Node node;
			node.push_back(rhs.Name);
			node.push_back(rhs.NumberOfFrames);
			node.push_back((int)rhs.Status);
			node.push_back(rhs.Width);
			node.push_back(rhs.Height);
			node.push_back(rhs.Texture->GetTextureFilePath());
			node.push_back(rhs.bIsReadyToLoad);

			return node;
		}

		static bool decode(const Node& node, AGE::AnimationSpecification& rhs)
		{
			if (!node.IsSequence() || node.size() <= 0)
			{
				return false;
			}

			rhs.Name = node[0].as<std::string>();
			rhs.NumberOfFrames = node[1].as<int>();
			rhs.Status = (AGE::CharMovementStatus)node[2].as<int>();
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
	YAML::Emitter& operator <<(YAML::Emitter& Out, const AGE::Vector2& v)
	{
		Out << YAML::Flow;
		Out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
		return Out;
	}

	YAML::Emitter& operator <<(YAML::Emitter& Out, const AGE::Vector3& v)
	{
		Out << YAML::Flow;
		Out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return Out;
	}
	YAML::Emitter& operator <<(YAML::Emitter& Out, const AGE::Vector4& v)
	{
		Out << YAML::Flow;
		Out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return Out;
	}
	YAML::Emitter& operator <<(YAML::Emitter& Out, const std::unordered_map<std::string, Ref<Texture2D>>& um)
	{
		Out << YAML::Flow;
		for (auto KV : um)
		{
			Out << YAML::BeginMap << YAML::Key << KV.first << YAML::Value << KV.second->GetTextureFilePath() << YAML::EndMap;
		}
		return Out;
	}
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
				char c = i;
				std::string s;
				s += c;
				Out << s;
			}
			Out << YAML::EndSeq;
		}
		Out << YAML::EndMap;
		return Out;
	}

	YAML::Emitter& operator <<(YAML::Emitter& Out, AGE::AnimationSpecification Anim)
	{
		Out << YAML::Flow;
		Out << YAML::BeginSeq;
		Out << Anim.Name;
		Out << Anim.NumberOfFrames;
		Out << (int)Anim.Status;
		Out << Anim.Width;
		Out << Anim.Height;
		Out << Anim.Texture->GetTextureFilePath();
		Out << Anim.bIsReadyToLoad;
		Out << YAML::EndSeq;
	
		return Out;
	}

	

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

		AGE_CORE_ASSERT(false, "Unknown Body Type");
		return {};
	}

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

		AGE_CORE_ASSERT(false, "Unknown Body Type");
		
		return BodyType::Static;

	}

	SceneSerializer::SceneSerializer(const Ref<Scene>& S)
		:m_Scene(S)
	{
	}

	static void SerializeEntity(YAML::Emitter& Out, Entity E)
	{
		AGE_CORE_ASSERT(E.HasComponent<IDComponent>(), "No ID Component present!");
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

	ProjectSerializer::ProjectSerializer(Ref<Project> Project)
		:m_Project(Project)
	{

	}
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
		std::tm tm =*std::localtime(&t);
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
			std::ifstream In(Scene.path().string(), std::ios::in, std::ios::binary);
			if (In)
			{
				std::string base = Scene.path().string().substr(Scene.path().string().find_last_of("/\\") + 1);
				std::string::size_type const p(base.find_last_of('.'));
				std::string filename = base.substr(0, p);
				In.seekg(0, std::ios::end);
				Result.resize(In.tellg());
				CurrentOffset += filename.size();
				CurrentOffset += Result.size();
				Stream.WriteRaw<size_t>(CurrentOffset);
				Stream.WriteString(filename);
			}

		}

		for (const auto& Scene : std::filesystem::directory_iterator(Config.CurrentProjectPath.string()+"/"+m_Project->GetConfig().Name + "/BuiltScenes/"))
		{
			std::string Result;
			std::ifstream In(Scene.path().string(), std::ios::in, std::ios::binary);
			if (In)
			{
				In.seekg(0, std::ios::end);
				Result.resize(In.tellg());
				In.seekg(0, std::ios::beg);
				In.read(&Result[0], Result.size());
				Stream.WriteRaw<const char*>(Result.c_str());
			}

		}
	}
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
			int index = 0;
			for (auto S : ProjectNode["Scenes"])
			{
				Info.BuiltScenes.resize(ProjectNode["Scenes"].size());
				Info.BuiltScenes[index] = ProjectNode["Scenes"][index].as<std::string>();
				index++;
			}
		}

		return true;
	}
	bool ProjectSerializer::DeserializeBinary(const std::filesystem::path& FilePath)
	{
		return false;
	}
	IniSerializer::IniSerializer(std::vector<std::pair<std::string, std::vector<uint8_t>>>& AxisBindings, std::vector<std::pair<std::string, std::vector<uint8_t>>>& ActionBindings)
		:m_AxisBindings(AxisBindings), m_ActionBindings(ActionBindings)
	{
	}

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