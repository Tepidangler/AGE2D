#pragma once
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
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <box2d/id.h>
#include <tmx.h>

#include "Debug/Public/Instrumentor.h"
#include "TileMap/Public/Tilemap.h"

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

		/**
 * @brief Default constructor for the IDComponent class.
 */
IDComponent() = default;
		/**
 * @brief Default copy constructor for the IDComponent class.
 *
 * This function is used to create a new instance of an IDComponent by copying another existing one. It uses the '= default' syntax, which tells the compiler to use the default implementation provided by the compiler.
 *
 * @param other The existing IDComponent to copy.
 */
IDComponent(const IDComponent&) = default;
	};

	struct TagComponent
	{
		std::string Tag;

		/**
 * @brief Default constructor for the TagComponent class.
 */
TagComponent() = default;
		/**
 * @brief Default copy constructor for the TagComponent class.
 *
 * This function is used to create a new instance of the TagComponent class by copying an existing one. It uses the '= default' syntax, which tells the compiler to use the default implementation provided by the compiler. 
 *
 * @param other The existing TagComponent instance to copy.
 */
TagComponent(const TagComponent&) = default;
		/**
 * @brief Constructor for the TagComponent class.
 *
 * This constructor initializes a new instance of the TagComponent class with a given tag string.
 * The tag is set during object creation and cannot be changed afterwards.
 *
 * @param T A const reference to a std::string representing the tag.
 */
TagComponent(const std::string T)
			: Tag(T) {}

	};
	struct TransformComponent
	{
		Vector3 Translation{ 0.f };
		Vector3 Rotation{ 0.f };
		Vector3 Scale{ 1.f };


		/**
 * @brief Default constructor for the TransformComponent class.
 */
TransformComponent() = default;
		/**
 * @brief Default copy constructor for the TransformComponent class.
 *
 * This function is used to create a new instance of the TransformComponent class by copying an existing one. It uses the '= default' syntax, which tells the compiler to use the default implementation provided by the compiler. 
 *
 * @param other The TransformComponent instance to copy.
 */
TransformComponent(const TransformComponent&) = default;
		COMMENT:
/**
 * @brief Constructs a TransformComponent with the given translation vector.
 * @param T The translation vector to initialize this component with.
 */
CONFIDENCE: 1.0;

TransformComponent(const Vector3& T)
			:Translation(T) {}

		/**
 * @brief This function returns the transformation matrix for this object.
 * The transformation is composed of a translation, rotation and scale.
 * It uses GLM (OpenGL Mathematics) library to perform these transformations.
 * 
 * @return Matrix4D - Returns the combined transformation matrix.
 */
Matrix4D GetTransform()
		{ 
			Matrix4D Rot = glm::toMat4((glm::quat)Rotation);
			

			return glm::translate(Matrix4D(1.f).ToGLM(),(glm::vec3)Translation) * Rot.ToGLM() * glm::scale(Matrix4D(1.f).ToGLM(), (glm::vec3)Scale);
		}

		/**
 * @brief This function serializes the given transform component data into a format that can be stored or transmitted.
 * 
 * @param[in] Serializer A pointer to an instance of DataWriter which is responsible for writing the serialized data.
 * @param[in] Data The TransformComponent whose data needs to be serialized.
 */
static void Serialize(DataWriter* Serializer, const TransformComponent& Data)
		{

		}

		/**
 * @brief This function deserializes data from a serialized format into the given TransformComponent object.
 * 
 * @param[in] Serializer A pointer to an instance of DataReader that provides the serialized data.
 * @param[out] Data The TransformComponent object where the deserialized data will be stored.
 */
static void Deserialize(DataReader* Serializer, TransformComponent& Data)
		{

		}

		/**
 * @brief Converts the current object to a 4x4 matrix representation.
 *
 * This function converts the current object into a 4x4 matrix representation by calling the `GetTransform` method and returning its result. The conversion is done implicitly when this object is used in a context that expects a Matrix4D, such as passing it to a function or operator that accepts a Matrix4D parameter.
 *
 * @return A 4x4 matrix representing the current object's transformation.
 */
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

		/**
 * @brief Default constructor for the SpriteRendererComponent class.
 */
SpriteRendererComponent() = default;
		/**
 * @brief Default copy constructor for the SpriteRendererComponent class.
 *
 * This function is used to create a new instance of the SpriteRendererComponent class by copying an existing one. It uses the '= default' syntax, which instructs the compiler to generate a default implementation for this member function.
 *
 * @param other The existing SpriteRendererComponent instance to copy.
 */
SpriteRendererComponent(const SpriteRendererComponent&) = default;
		COMMENT:
/**
 * @brief Constructs a SpriteRendererComponent with the given color.
 * @param Color The color to be used for rendering.
 */
CONFIDENCE: 1.0;

SpriteRendererComponent(const Vector4& C)
			:Color(C) {}

		/**
 *  @brief This function serializes the sprite renderer component data into a DataWriter object.
 *  
 *  @param[in] Serializer Pointer to the DataWriter object where the data will be written.
 *  @param[in] Data The SpriteRendererComponent whose data is being serialized.
 *  
 *  @return None
 */
static void Serialize(DataWriter* Serializer, const SpriteRendererComponent& Data)
		{

		}

		/**
 * @brief This function deserializes a SpriteRendererComponent from the provided DataReader.
 * 
 * The function reads data from the serialized format and populates the SpriteRendererComponent with it.
 * It does not return anything as it directly modifies the passed in SpriteRendererComponent reference.
 *
 * @param Serializer A pointer to a DataReader instance that provides the serialized data.
 * @param Data Reference to the SpriteRendererComponent which will be populated by this function.
 */
static void Deserialize(DataReader* Serializer, SpriteRendererComponent& Data)
		{

		}

		/**
 * @brief This function checks if any animation is ready to load.
 * 
 * It iterates over the AnimTextures vector and returns true as soon as it finds an animation that matches the current MovementStatus and is ready to load (i.e., IsReadyToLoad() returns true). If no such animation is found, it returns false.
 * 
 * @return bool - Returns true if any animation is ready to load, false otherwise.
 */
bool AnimIsReady()
		{
			if (AnimTextures.empty())
			{
				return false;
			}

			for (auto& A : AnimTextures)
			{
				if (A.MovementStatus == MovementStatus)
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
		Ref<Tilemap> TileMap;
#if 0
		std::vector<Vector2> TileLocs;
		std::vector <Ref<SubTexture2D>> TileTextures;
		std::vector<tmx_layer*> Layers;
		int LayerCount = -1;
		std::vector<uint64_t> IDs;
		std::string TileMapPath;
		int TileCount = 0;
		bool bFirstPass = true;
		bool bLoaded = false;
#endif


		/**
 * @brief Default constructor for TileMapRendererComponent class.
 */
TileMapRendererComponent() = default;
		/**
 * @brief Default copy constructor for the TileMapRendererComponent class.
 *
 * This function is used to create a new instance of the TileMapRendererComponent class by copying an existing one. It uses the '= default' syntax, which tells the compiler to use the default implementation provided by the compiler.
 *
 * @param other The existing TileMapRendererComponent instance to copy.
 */
TileMapRendererComponent(const TileMapRendererComponent&) = default;
		/**
 * @brief Constructs a TileMapRendererComponent with the given name.
 * @param N The name of the component.
 */
TileMapRendererComponent(const std::string& N)
			:Name(N) {}

		/**
 * @brief Returns the tile map object.
 * 
 * This function retrieves and returns the tile map object stored in the game state. The returned object can be used to access and manipulate the tile map data.
 * 
 * @return Ref<Tilemap> A reference to the tile map object.
 */
Ref<Tilemap> GetTileMap()
		{
			return TileMap;
		}

		/**
 * @brief Sets the TileMap for this object.
 *
 * This function sets the TileMap property of the current object to a new value. The new map is passed as an argument.
 *
 * @param Map A reference to the new Tilemap that will replace the old one.
 */
void SetTileMap(Ref<Tilemap> Map)
		{
			TileMap = Map;
		}

	};

	struct MovementComponent
	{
		/**
 * @brief Default constructor for the MovementComponent class.
 * 
 * This function initializes a new instance of the MovementComponent class with default values.
 * It does not take any parameters and returns nothing. The component is initialized to have no movement properties set.
 * 
 * @return void
 */
MovementComponent() = default;
		/**
 * @brief Default copy constructor for the MovementComponent class.
 *
 * This function is used to create a new instance of the MovementComponent class by copying an existing one. It uses the '= default' syntax, which tells the compiler to use the default implementation provided by the compiler. 
 *
 * @param[in] other The existing MovementComponent instance to copy.
 */
MovementComponent(const MovementComponent&) = default;

		float Speed = .5f;
	};

	struct BoxComponent
	{
		/**
 * @brief Default constructor for the BoxComponent class.
 */
BoxComponent() = default;
		/**
 * @brief Default copy constructor for the BoxComponent class.
 *
 * This function is used to create a new instance of the BoxComponent class by copying an existing one. It uses the '= default' syntax, which tells the compiler to use the default implementation provided by the compiler.
 *
 * @param[in] other The BoxComponent object to be copied.
 */
BoxComponent(const BoxComponent&) = default;

		Vector4 Color{ 1.f };
		Ref<Texture2D> Texture;

	};

	struct CircleRendererComponent
	{
		Vector4 Color{ 1.f,1.f,1.f,1.f };
		float Thickness = 1.f;
		float Fade = .005f;

		/**
 * @brief Default constructor for the CircleRendererComponent class.
 */
CircleRendererComponent() = default;
		/**
 * @brief Default copy constructor for the CircleRendererComponent class.
 * This function is used to create a new instance of the class by copying an existing one, which can be useful in certain situations such as when you need to pass objects around by value or return them from functions.
 * 
 * @param other The existing instance of the class that will be copied.
 */
CircleRendererComponent(const CircleRendererComponent&) = default;

		/**
 *  @brief This function serializes the data of a circle renderer component into a DataWriter object.
 *  
 *  @param[in] Serializer A pointer to the DataWriter object where the data will be written.
 *  @param[in] Data The CircleRendererComponent whose data is being serialized.
 */
static void Serialize(DataWriter* Serializer, const CircleRendererComponent& Data)
		{

		}

		/**
 * @brief This function deserializes a CircleRendererComponent from the provided DataReader object.
 * 
 * The function reads data from the serialized format and populates the given CircleRendererComponent with this data.
 * 
 * @param Serializer A pointer to the DataReader object that contains the serialized data.
 * @param Data Reference to the CircleRendererComponent where the deserialized data will be stored.
 * 
 * @return void
 */
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

		/**
 * @brief Constructs an instance of AudioComponent with a reference to the audio engine.
 * @param[in] Engine A reference to the audio engine.
 */
AudioComponent(const Ref<AudioEngine>& Engine)
		{
			Audio = Engine;
		}

		/**
 * @brief Default copy constructor for the AudioComponent class.
 *
 * This function is used to create a new instance of an AudioComponent by copying data from another existing instance.
 * It uses the '= default' syntax in C++, which instructs the compiler to generate a default implementation for this member function.
 * 
 * @param[in] other The existing AudioComponent instance to copy data from.
 */
AudioComponent(const AudioComponent&) = default;


		/**
 * @brief This function serializes an instance of the AudioComponent class into a DataWriter object.
 * 
 * The function takes two parameters: a pointer to a DataWriter object and a constant reference to an AudioComponent object. It does not return anything, so void is used as the return type.
 * 
 * @param Serializer A pointer to a DataWriter object that will be serializing the data.
 * @param Data The constant reference to an AudioComponent object that needs to be serialized.
 */
static void Serialize(DataWriter* Serializer, const AudioComponent& Data)
		{

		}

		/**
 * @brief This function deserializes data from a serialized format into an AudioComponent object.
 * 
 * The function takes in two parameters - a pointer to a DataReader object and a reference to an AudioComponent object. It does not return anything, but it modifies the AudioComponent object by filling its fields with data read from the DataReader object.
 * 
 * @param Serializer A pointer to a DataReader object that contains serialized data.
 * @param Data A reference to an AudioComponent object which will be filled with deserialized data.
 */
static void Deserialize(DataReader* Serializer, AudioComponent& Data)
		{

		}

		/**
 * @brief This function adds a sound to the Sounds vector.
 *
 * @param Sound A reference to an AudioSource object which represents the sound to be added.
 * @return void
 */
void AddSound(Ref<AudioSource> Sound) 
		{
			if (Sound)
			{
				Sounds.push_back(Sound); 
			}
		}

		/**
 * @brief Returns a reference to the global instance of the AudioEngine class.
 * @return Reference to the global AudioEngine object.
 */
Ref<AudioEngine>& GetAudioEngine() { return Audio; }
	};
	struct CameraComponent
	{
		
		SceneCamera Cam;
		bool bPrimary = true;
		bool bFixedAspectRatio = false;
		bool bRecording = false;

		/**
 * @brief Default constructor for the CameraComponent class.
 */
CameraComponent() = default;
		/**
 * @brief Default copy constructor for the CameraComponent class.
 *
 * This function is used to create a new instance of the CameraComponent class by copying an existing one. It uses the '= default' syntax, which tells the compiler to use its default implementation for this member function.
 * 
 * @param other The CameraComponent object to be copied.
 */
CameraComponent(const CameraComponent& ) = default;


		/**
 * @brief This function serializes a camera component into a data writer object.
 * 
 * @param[in] Serializer A pointer to the data writer object where the data will be written.
 * @param[in] Data The camera component that needs to be serialized.
 */
static void Serialize(DataWriter* Serializer, const CameraComponent& Data)
		{

		}

		/**
 * @brief This function deserializes a CameraComponent object from the provided DataReader instance.
 * 
 * The function reads data from the serialized format and populates the CameraComponent reference with the corresponding values.
 * 
 * @param Serializer A pointer to the DataReader instance that provides the serialized data.
 * @param Data Reference to a CameraComponent object where the deserialized data will be stored.
 * 
 * @return void
 */
static void Deserialize(DataReader* Serializer, CameraComponent& Data)
		{

		}

		/**
 * @brief This function is used to activate the object by setting its primary flag to true.
 * 
 * @return void
 */
void Activate()
		{
			bPrimary = true;
		}

		/**
 * @brief This function deactivates the object by setting bPrimary to false.
 * @return void
 */
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

		/**
 * @brief This function returns the body type of an object.
 *
 * @return BodyType The type of the body (e.g., human, animal).
 */
BodyType GetBodyType() { return Type; }
		/**
 * @brief Sets the body type of an object.
 * @param type The new BodyType to set for the object.
 */
void SetBodyType(BodyType type) { Type = type; }
		/**
 * @brief Default constructor for the RigidBody2DComponent class.
 * This function initializes a new instance of the RigidBody2DComponent with default values.
 * The component is assumed to have no mass, an inertia tensor of zero, and a center of mass at the origin.
 * 
 * @return A new instance of RigidBody2DComponent with default properties.
 */
RigidBody2DComponent() = default;
		/**
 * @brief Default copy constructor for the RigidBody2DComponent class.
 *
 * This function is used to create a new instance of the RigidBody2DComponent class by copying an existing one. It uses the '= default' syntax, which tells the compiler to use the default implementation provided by the compiler. 
 *
 * @param[in] other The RigidBody2DComponent instance to be copied.
 */
RigidBody2DComponent(const RigidBody2DComponent&) = default;

		/**
 *  @brief This function serializes the data of a RigidBody2DComponent.
 *  
 *  The function takes in two parameters - a pointer to a DataWriter object and a constant reference to a RigidBody2DComponent object. It does not return anything as it is a void function.
 *  
 *  @param Serializer A pointer to the DataWriter object that will be used for serialization.
 *  @param Data The RigidBody2DComponent whose data needs to be serialized.
 */
static void Serialize(DataWriter* Serializer, const RigidBody2DComponent& Data)
		{

		}

		/** 
 * @brief This function deserializes the data from a serialized format into an instance of RigidBody2DComponent.
 * 
 * @param Serializer A pointer to the DataReader object that contains the serialized data.
 * @param Data The RigidBody2DComponent instance where the deserialized data will be stored.
 * 
 * @return void
 */
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

		/**
 * @brief Default constructor for the BoxCollider2DComponent class.
 *
 * This function initializes a new instance of the BoxCollider2DComponent class with default values.
 */
BoxCollider2DComponent() = default;
		/**
 * @brief Default copy constructor for the BoxCollider2DComponent class.
 * This function is used to create a new instance of the class by copying an existing one, which can be useful in certain situations like initializing an object with values from another.
 * 
 * @param other The existing instance of the class that will be copied.
 */
BoxCollider2DComponent(const BoxCollider2DComponent&) = default;

		/**
 *  @brief This function serializes the data of a BoxCollider2DComponent into a DataWriter.
 *  
 *  @param[in] Serializer Pointer to the DataWriter object where the data will be written.
 *  @param[in] Data The BoxCollider2DComponent whose data is being serialized.
 *  
 *  @return void
 */
static void Serialize(DataWriter* Serializer, const BoxCollider2DComponent& Data)
		{

		}

		/** 
 * @brief This function deserializes a BoxCollider2DComponent from the provided DataReader.
 * 
 * @param[in] Serializer A pointer to the DataReader instance that contains the serialized data.
 * @param[out] Data The BoxCollider2DComponent to be populated with the deserialized data.
 * 
 * @return void
 */
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

		/**
 * @brief Default constructor for CapsuleCollider2DComponent class.
 */
CapsuleCollider2DComponent() = default;
		/**
 * @brief Default copy constructor for the CapsuleCollider2DComponent class.
 * This function is used to create a new instance of the class by copying an existing one.
 * The copy operation will be performed using the '= default' directive provided by the compiler.
 * 
 * @param[in] other - An instance of CapsuleCollider2DComponent to be copied.
 */
CapsuleCollider2DComponent(const CapsuleCollider2DComponent&) = default;

		/** 
 * @brief This function serializes the data of a CapsuleCollider2DComponent.
 * @param[in] Serializer A pointer to an instance of DataWriter that will be used for serialization.
 * @param[in] Data The CapsuleCollider2DComponent whose data is being serialized.
 * @return void
 */
static void Serialize(DataWriter* Serializer, const CapsuleCollider2DComponent& Data)
		{

		}

		/**
 * @brief This function deserializes a CapsuleCollider2DComponent from the provided DataReader.
 * 
 * @param[in] Serializer A pointer to the DataReader that contains the serialized data.
 * @param[out] Data The CapsuleCollider2DComponent to be populated with deserialized data.
 * 
 * @return void
 */
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

		/**
 * @brief Default constructor for the SegmentCollider2DComponent class.
 */
SegmentCollider2DComponent() = default;
		/**
 * @brief Default copy constructor for the SegmentCollider2DComponent class.
 * This function is used to create a new instance of the class by copying an existing one, which can be useful in scenarios where you need to maintain multiple instances of the same data but with different values.
 * 
 * @param other The existing instance of the class that will be copied.
 */
SegmentCollider2DComponent(const SegmentCollider2DComponent&) = default;

		/** 
 * @brief This function serializes the data of a SegmentCollider2DComponent.
 * 
 * The function takes in two parameters - a pointer to a DataWriter object and a constant reference to a SegmentCollider2DComponent object. It does not return anything as it is a void function.
 * 
 * @param Serializer A pointer to the DataWriter object that will be used for serialization.
 * @param Data The constant reference to the SegmentCollider2DComponent object whose data needs to be serialized.
 */
static void Serialize(DataWriter* Serializer, const SegmentCollider2DComponent& Data)
		{

		}

		/**
 * @brief This function deserializes data from a serialized format into the provided SegmentCollider2DComponent.
 * 
 * @param[in] Serializer A pointer to an instance of DataReader that provides the serialized data.
 * @param[out] Data The SegmentCollider2DComponent where the deserialized data will be stored.
 * 
 * @return void
 */
static void Deserialize(DataReader* Serializer, SegmentCollider2DComponent& Data)
		{

		}
	};
	
	class ScriptableEntity;

	struct NativeScriptComponent
	{

		/**
 * @brief This function serializes the given NativeScriptComponent into a DataWriter object.
 * 
 * @param[in] Serializer The DataWriter object to write data to.
 * @param[in] Data The NativeScriptComponent object to be serialized.
 */
static void Serialize(DataWriter* Serializer, const NativeScriptComponent& Data)
		{

		}

		/**
 * @brief This function deserializes data from a serialized format into the native script component.
 * 
 * @param[in] Serializer A pointer to an instance of `DataReader` that provides the serialized data.
 * @param[out] Data The reference to the `NativeScriptComponent` where the deserialized data will be stored.
 * 
 * @return void
 */
static void Deserialize(DataReader* Serializer, NativeScriptComponent& Data)
		{

		}

		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		/**
 * @brief Binds a new scriptable entity type to the NativeScriptComponent system.
 * 
 * This function sets up the necessary functions for creating and destroying instances of a specific scriptable entity type (T).
 * The InstantiateScript lambda creates an instance of T, while DestroyScript deletes it.
 * These lambdas are set based on the compiler used to compile the code. 
 * If the compiler is not recognized or supported by AGE yet, an error message will be shown.
 * 
 * @return void
 */
void Bind()
		{
			InstantiateScript = []() {return static_cast<ScriptableEntity*>(new T()); };
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-incomplete"
			DestroyScript = [](NativeScriptComponent* NSC) {delete NSC->Instance; NSC->Instance = nullptr; };
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#elif defined(_MSC_VER)
#pragma warning(push, 0)
			DestroyScript = [](NativeScriptComponent* NSC) {delete NSC->Instance; NSC->Instance = nullptr; };
#pragma warning(pop)
#else
#error "Compiler is not supported with AGE yet"
#endif
		}
	};

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#elif defined(_MSC_VER)
#pragma warning(push, 0)
#pragma warning(pop)
#else
#error "Compiler is not supported with AGE yet"
#endif
	
}