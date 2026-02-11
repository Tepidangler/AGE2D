#pragma once
#include "Core/Public/Core.h"
#include "Core/Public/UUID.h"
#include "Scene/Public/SceneCamera.h"
#include "Scene/Public/Scene.h"
#include "Animation/Public/Animation.h"
#include "Math/Public/Math.h"
#include "Audio/AGESound/Public/Sound.h"
#include "Audio/AudioEngine/Public/AudioEngine.h"
#include "Texture/Public/Texture.h"
#include "Parser/Public/CsvParser.h"
#include "Serializers/Public/DataReader.h"
#include "Serializers/Public/DataWriter.h"
#include "Assets/Public/AssetManager.h"
#include "Core/Public/Keycodes.h"
#include "Core/Public/MouseButtonCodes.h"
#include "Core/Public/JoyStickCodes.h"
#include "Core/Public/GamepadCodes.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <box2d/id.h>
#include <box2d/types.h>
#include <tmx.h>

#include "Debug/Public/Instrumentor.h"

namespace GameFramework
{
	class Character;
}

namespace AGE
{
	enum class BodyType { Static = 0, Dynamic, Kinematic };


	struct IDComponent
	{
		UUID ID;

		IDComponent() = default;
		IDComponent(const IDComponent&) = default;
	};

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string T)
			: Tag(T) {}

	};
	struct TransformComponent
	{
		Vector3 Translation{ 0.f };
		Vector3 Rotation{ 0.f };
		Vector3 Scale{ 1.f };


		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const Vector3& T)
			:Translation(T) {}

		Matrix4D GetTransform() const
		{ 
			Matrix4D Rot = glm::toMat4(glm::quat(Convert::ToGLM(Rotation)));
			

			return glm::translate(Matrix4D(1.f).ToGLM(),Convert::ToGLM(Translation)) * Rot.ToGLM() * glm::scale(Matrix4D(1.f).ToGLM(), Convert::ToGLM(Scale));
		}

		static void Serialize(DataWriter* Serializer, const TransformComponent& Data)
		{

		}

		static void Deserialize(DataReader* Serializer, TransformComponent& Data)
		{

		}

		operator Matrix4D()
		{
			return GetTransform();
		}
	};

	struct SpriteRendererComponent
	{
		QuadProperties QuadProps;
		Vector4 Color{ 1.f };
		int TileID = -1;
		int CurrentAnimationID = -1;
		Ref<Texture2D> Texture;
		Ref<Texture2D> DiagTexture;
		Ref<SubTexture2D> SubTexture;
		Vector2 TileLocation;
		int TilesLayer = -1;
		float TileWidth;
		float TileHeight;
		bool bTile = false;
		std::vector<AnimationSpecification> AnimTextures;
		CharMovementStatus MovementStatus = CharMovementStatus::Idle;
		std::string RigidBodyType = "Dynamic";
		std::string AsepriteName = "None";
		std::filesystem::path AsepriteFile = "";

		Animation AnimInstance;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const Vector4& C)
			:Color(C) {}

		static void Serialize(DataWriter* Serializer, const SpriteRendererComponent& Data)
		{

		}

		static void Deserialize(DataReader* Serializer, SpriteRendererComponent& Data)
		{

		}

		bool AnimIsReady()
		{
			if (AnimTextures.empty())
			{
				return false;
			}

			for (auto& A : AnimTextures)
			{
				if (A.Status == MovementStatus)
				{
					if (A.IsReadyToLoad())
					{
						return true;
					}
				}
				else
				{
					continue;
				}

			}
			return false;
		}
	};

	struct TileMapRendererComponent
	{
		std::string Name;
		tmx_map* TileMap;
		Ref<Texture2D> TileMapTexture;
		std::vector<Vector2> TileLocs;
		std::vector <Ref<SubTexture2D>> TileTextures;
		std::vector<tmx_layer*> Layers;
		int LayerCount = -1;
		std::vector<uint64_t> IDs;
		std::string TileMapPath;
		Ref<Scene> ActiveScene;

		int TileCount = 0;
		bool bFirstPass = true;
		bool bLoaded = false;
		

		TileMapRendererComponent() = default;
		TileMapRendererComponent(const TileMapRendererComponent&) = default;
		TileMapRendererComponent(const std::string& N)
			:Name(N) {}


		static void Serialize(DataWriter* Serializer, const TileMapRendererComponent& Data)
		{

		}

		static void Deserialize(DataReader* Serializer, TileMapRendererComponent& Data)
		{

		}

		tmx_map* GetTileMap()
		{
			return TileMap;
		}

		void SetTileMap(tmx_map* Map)
		{
			TileMap = Map;
		}

		void SetTileLocations()
		{
			AGE_PROFILE_FUNCTION();
			uint32_t Width, Height;

			//Now sure if 1 will always be valid, but it should be
			Width = TileMap->tiles[1]->tileset->image->width;
			Height = TileMap->tiles[1]->tileset->image->height;

			for (uint32_t x = (Height / TileMap->tiles[1]->tileset->tile_height)-1; x >= 0 ; x--)
			{
				for (uint32_t y = 0; y < (Width / TileMap->tiles[1]->tileset->tile_width); y++)
				{
					TileLocs.push_back(Vector2((float)y, (float)x));
				}
			}

			for (size_t i = 0; i < TileLocs.size() - 1; i++)
			{
				TileTextures.push_back(SubTexture2D::CreateFromCoords(TileMapTexture, TileLocs[i], { (float)TileMap->tiles[1]->tileset->tile_width,(float)TileMap->tiles[1]->tileset->tile_height}));
			}
		}

		int ProcessLayers(tmx_layer* Head)
		{
			int Tmp = 0;
			tmx_layer* Current = Head;
			while (Current)
			{
				Layers.push_back(Current);
				Current = Current->next;
				Tmp++;
			}

			return Tmp;
		}
	};

	struct MovementComponent
	{
		MovementComponent() = default;
		MovementComponent(const MovementComponent&) = default;

		float Speed = .5f;
	};

	struct BoxComponent
	{
		BoxComponent() = default;
		BoxComponent(const BoxComponent&) = default;

		Vector4 Color{ 1.f };
		Ref<Texture2D> Texture;

	};

	struct CircleRendererComponent
	{
		Vector4 Color{ 1.f,1.f,1.f,1.f };
		float Thickness = 1.f;
		float Fade = .005f;

		CircleRendererComponent() = default;
		CircleRendererComponent(const CircleRendererComponent&) = default;

		static void Serialize(DataWriter* Serializer, const CircleRendererComponent& Data)
		{

		}

		static void Deserialize(DataReader* Serializer, CircleRendererComponent& Data)
		{

		}
	};


	struct AudioComponent
	{
	public:

		std::vector<Ref<AudioSource>> Sounds;
		Ref<AudioEngine> Audio;
		uint32_t SoundBankID;
		uint64_t GameObjID;
		//ALint State = AL_INITIAL;
		//std::size_t Cursor = 65536 * 4;

		AudioComponent(const Ref<AudioEngine>& Engine)
		{
			Audio = Engine;
		}

		AudioComponent(const AudioComponent&) = default;


		static void Serialize(DataWriter* Serializer, const AudioComponent& Data)
		{

		}

		static void Deserialize(DataReader* Serializer, AudioComponent& Data)
		{

		}

		void AddSound(Ref<AudioSource> Sound) 
		{
			if (Sound)
			{
				Sounds.push_back(Sound); 
			}
		}

		Ref<AudioEngine>& GetAudioEngine() { return Audio; }
	};
	struct CameraComponent
	{
		
		SceneCamera Cam;
		bool bPrimary = true;
		bool bFixedAspectRatio = false;
		bool bRecording = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent& ) = default;


		static void Serialize(DataWriter* Serializer, const CameraComponent& Data)
		{

		}

		static void Deserialize(DataReader* Serializer, CameraComponent& Data)
		{

		}

		void Activate()
		{
			bPrimary = true;
		}

		void Deactivate()
		{
			bPrimary = false;
		}
		

	};

	struct RigidBody2DComponent
	{
		BodyType Type = BodyType::Static;

		bool FixedRotation = false;

		bool bSimulatePhysics = true;

		bool bInteractable = false;

		void* RuntimeBody = nullptr;

		b2BodyId BodyID = b2_nullBodyId;

		BodyType GetBodyType() { return Type; }
		void SetBodyType(BodyType type) { Type = type; }
		RigidBody2DComponent() = default;
		RigidBody2DComponent(const RigidBody2DComponent&) = default;

		static void Serialize(DataWriter* Serializer, const RigidBody2DComponent& Data)
		{

		}

		static void Deserialize(DataReader* Serializer, RigidBody2DComponent& Data)
		{

		}
	};

	struct BoxCollider2DComponent
	{
		Vector2 Offset = { 0.f, 0.f };
		Vector2 Size = { .5f,.5f };


		float Density = 1.f;
		float Friction = 1.f;
		float Restitution = 0.f;
		float RestitutionThreshold = .5f;

		b2ShapeId ShapeID = b2_nullShapeId;

		bool bGeneratePhysicsEvents = false;

		BoxCollider2DComponent() = default;
		BoxCollider2DComponent(const BoxCollider2DComponent&) = default;

		static void Serialize(DataWriter* Serializer, const BoxCollider2DComponent& Data)
		{

		}

		static void Deserialize(DataReader* Serializer, BoxCollider2DComponent& Data)
		{

		}

	};

	struct CapsuleCollider2DComponent
	{
		Vector2 Offset = { 0.f, 0.f };
		float Radius = .5f;


		float Density = 1.f;
		float Friction = 1.f;
		float Restitution = 0.f;
		float RestitutionThreshold = .5f;

		b2ShapeId ShapeID = b2_nullShapeId;
		
		bool bGeneratePhysicsEvents = false;

		CapsuleCollider2DComponent() = default;
		CapsuleCollider2DComponent(const CapsuleCollider2DComponent&) = default;

		static void Serialize(DataWriter* Serializer, const CapsuleCollider2DComponent& Data)
		{

		}

		static void Deserialize(DataReader* Serializer, CapsuleCollider2DComponent& Data)
		{

		}
	};

	struct SegmentCollider2DComponent
	{
		Vector2 Offset = { 0.f, 0.f };
		Vector2 Size = { .5f,.5f };

		float Density = 1.f;
		float Friction = 1.f;
		float Restitution = 0.f;
		float RestitutionThreshold = .5f;

		b2ShapeId ShapeID = b2_nullShapeId;
		bool bGeneratePhysicsEvents = false;

		SegmentCollider2DComponent() = default;
		SegmentCollider2DComponent(const SegmentCollider2DComponent&) = default;

		static void Serialize(DataWriter* Serializer, const SegmentCollider2DComponent& Data)
		{

		}

		static void Deserialize(DataReader* Serializer, SegmentCollider2DComponent& Data)
		{

		}
	};
	
	class ScriptableEntity;

	struct NativeScriptComponent
	{

		static void Serialize(DataWriter* Serializer, const NativeScriptComponent& Data)
		{

		}

		static void Deserialize(DataReader* Serializer, NativeScriptComponent& Data)
		{

		}

		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() {return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* NSC) {delete NSC->Instance; NSC->Instance = nullptr; };
		}
	};


	
}