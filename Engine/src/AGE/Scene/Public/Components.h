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

		/**
 * @brief Default constructor for the IDComponent class.
 */
IDComponent() = default;
		/**
 * @brief Default copy constructor for the IDComponent class.
 *
 * This function is used to create a new instance of an IDComponent by copying another existing one. It uses the '= default' syntax, which instructs the compiler to generate a default implementation for this member function.
 * 
 * @param other The existing IDComponent to copy from.
 */
IDComponent(const IDComponent&) = default;
	};

	struct TagComponent
	{
		std::string Tag;

		/**
 * @brief Default constructor for the TagComponent class.
 * 
 * This function initializes a new instance of the TagComponent class with its members set to their default values.
 * The default value is determined by the type of each member variable. For example, if a member variable is an integer, it will be initialized to 0. If it's a pointer, it will be initialized to nullptr.
 * This function does not take any parameters and returns no value.
 */
TagComponent() = default;
		/**
 * @brief Default copy constructor for the TagComponent class.
 *
 * This function is used to create a new instance of the TagComponent class by copying an existing one. It uses the '= default' syntax, which tells the compiler to use the default implementation provided by the compiler.
 *
 * @param other The TagComponent instance to copy.
 * 
 * @return A new instance of the TagComponent class with the same values as the input parameter.
 */
TagComponent(const TagComponent&) = default;
		/**
 * @brief Constructor for the TagComponent class.
 *
 * This constructor initializes a new instance of the TagComponent class with a given string.
 * The input parameter is expected to be a non-empty string, and it will be stored as the tag value.
 * 
 * @param T A const reference to a std::string representing the tag value.
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
 * @param other The existing TransformComponent instance to copy.
 */
TransformComponent(const TransformComponent&) = default;
		/**
 * @brief Constructor for the TransformComponent class.
 *
 * This constructor initializes a new instance of the TransformComponent with a given translation vector.
 *
 * @param T The translation vector to initialize this component with.
 */
TransformComponent(const Vector3& T)
			:Translation(T) {}

		/**
 * @brief This function returns a transformation matrix based on the object's rotation, translation and scale.
 * 
 * The returned matrix is calculated as follows:
 * - First, it converts the object's rotation to a 4x4 matrix using glm::toMat4() function.
 * - Then, it applies a translation to this matrix using glm::translate().
 * - After that, it multiplies the resulting matrix by the rotation matrix.
 * - Finally, it scales the final matrix using glm::scale().
 * 
 * @return Matrix4D The transformation matrix based on the object's rotation, translation and scale.
 */
Matrix4D GetTransform() const
		{ 
			Matrix4D Rot = glm::toMat4(glm::quat(Convert::ToGLM(Rotation)));
			

			return glm::translate(Matrix4D(1.f).ToGLM(),Convert::ToGLM(Translation)) * Rot.ToGLM() * glm::scale(Matrix4D(1.f).ToGLM(), Convert::ToGLM(Scale));
		}

		/**
 * @brief This function serializes the given transform component data into a format that can be stored or transmitted.
 * 
 * @param[in] Serializer A pointer to an instance of DataWriter which is responsible for writing the serialized data.
 * @param[in] Data The TransformComponent whose data needs to be serialized.
 * 
 * @return void
 */
static void Serialize(DataWriter* Serializer, const TransformComponent& Data)
		{

		}

		/**
 * @brief This function deserializes data from a serialized format into the provided TransformComponent object.
 * 
 * @param[in] Serializer A pointer to an instance of DataReader that provides the serialized data.
 * @param[out] Data The TransformComponent object where the deserialized data will be stored.
 * 
 * @return void
 */
static void Deserialize(DataReader* Serializer, TransformComponent& Data)
		{

		}

		/**
 * @brief Converts the current object to a 4x4 matrix representation.
 *
 * This function converts the current object into a 4x4 matrix representation by calling the `GetTransform` method and returning its result. The returned matrix can be used for further transformations or computations.
 *
 * @return A 4x4 Matrix representing the current object's transformation.
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
 * This function initializes a new instance of the SpriteRendererComponent with default values.
 * The component is initialized to have no specific sprite or color, and its visibility is set to true.
 * 
 * @return A newly created instance of SpriteRendererComponent with default values.
 */
SpriteRendererComponent() = default;
		/**
 * @brief Default copy constructor for the SpriteRendererComponent class.
 *
 * This function is used to create a new instance of the SpriteRendererComponent class by copying an existing one. It uses the '= default' syntax, which tells the compiler to use the default implementation provided by the compiler. 
 *
 * @param other The existing SpriteRendererComponent instance to copy.
 */
SpriteRendererComponent(const SpriteRendererComponent&) = default;
		/**
 * @brief Constructor for the SpriteRendererComponent class.
 *
 * This constructor initializes a new instance of the SpriteRendererComponent with a given color.
 *
 * @param C A const reference to a Vector4 object representing the color to be set for this component.
 */
SpriteRendererComponent(const Vector4& C)
			:Color(C) {}

		/**
 * @brief This function serializes the sprite renderer component data into a DataWriter object.
 * 
 * @param[in] Serializer Pointer to the DataWriter object where the data will be written.
 * @param[in] Data Const reference to the SpriteRendererComponent that needs to be serialized.
 */
static void Serialize(DataWriter* Serializer, const SpriteRendererComponent& Data)
		{

		}

		/**
 * @brief This function deserializes a SpriteRendererComponent from the provided DataReader object.
 * 
 * The function reads data from the serialized format and populates the passed in SpriteRendererComponent reference with this data.
 * 
 * @param Serializer A pointer to an instance of DataReader that provides the serialized data.
 * @param Data Reference to a SpriteRendererComponent object where the deserialized data will be stored.
 * 
 * @return void
 */
static void Deserialize(DataReader* Serializer, SpriteRendererComponent& Data)
		{

		}

		/**
 * @brief Checks if any animation is ready to load.
 * 
 * This function iterates over the AnimTextures vector and checks each element's MovementStatus against the current status. If a texture with an equal or lesser movement status is found, it calls IsReadyToLoad() on that texture.
 * The function returns true if any such texture reports itself as ready to load, false otherwise.
 * 
 * @return True if any animation is ready to load, False otherwise.
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
		

		/**
 * @brief Default constructor for the TileMapRendererComponent class.
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
 * @brief Constructor for TileMapRendererComponent class.
 *
 * This constructor initializes the Name member variable with a given string.
 *
 * @param N The name to be assigned to the Name member variable.
 */
TileMapRendererComponent(const std::string& N)
			:Name(N) {}


		/**
 * @brief This function serializes the data of a TileMapRendererComponent into a DataWriter.
 * 
 * @param[in] Serializer Pointer to the DataWriter object where the data will be written.
 * @param[in] Data The TileMapRendererComponent whose data is being serialized.
 */
static void Serialize(DataWriter* Serializer, const TileMapRendererComponent& Data)
		{

		}

		/**
 * @brief This function deserializes data from a serialized format into the TileMapRendererComponent object.
 * 
 * @param[in] Serializer A pointer to an instance of DataReader that provides the serialized data.
 * @param[out] Data The TileMapRendererComponent object where the deserialized data will be stored.
 * 
 * @return void
 */
static void Deserialize(DataReader* Serializer, TileMapRendererComponent& Data)
		{

		}

		/**
 * @brief This function returns the tile map of the game.
 * 
 * @return tmx_map* A pointer to the tile map object. If no tile map exists, it will return NULL.
 */
tmx_map* GetTileMap()
		{
			return TileMap;
		}

		/**
 * @brief Sets the TileMap for the game.
 *
 * This function sets the TileMap that will be used by the game engine to render and update the game world.
 * The TileMap is a data structure containing information about the layout of the game world, including details like terrain types and object locations.
 * 
 * @param Map Pointer to the tmx_map structure which contains the map data.
 */
void SetTileMap(tmx_map* Map)
		{
			TileMap = Map;
		}

		/**
 * @brief This function sets the tile locations for a given TileMap. 
 * It calculates and stores the positions of each tile in a two dimensional vector, Vector2, named 'TileLocs'. 
 * The dimensions of each tile are also calculated and stored in another two dimensional vector, SubTexture2D, named 'TileTextures'.
 * @return void
 */
void SetTileLocations()
		{
			AGE_PROFILE_FUNCTION();
			unsigned long Width, Height;

			//Now sure if 1 will always be valid, but it should be
			Width = TileMap->tiles[1]->tileset->image->width;
			Height = TileMap->tiles[1]->tileset->image->height;

			for (unsigned long x = (Height / TileMap->tiles[1]->tileset->tile_height)-1; x >= 0 ; x--)
			{
				for (uint64_t y = 0; y < (Width / TileMap->tiles[1]->tileset->tile_width); y++)
				{
					TileLocs.push_back(Vector2((float)y, (float)x));
				}
			}

			for (size_t i = 0; i < TileLocs.size() - 1; i++)
			{
				TileTextures.push_back(SubTexture2D::CreateFromCoords(TileMapTexture, TileLocs[i], { (float)TileMap->tiles[1]->tileset->tile_width,(float)TileMap->tiles[1]->tileset->tile_height}));
			}
		}

		/**
 * @brief Processes a linked list of layers and pushes them into the Layers vector.
 *
 * This function takes in the head of a linked list of tmx_layer objects, traverses through the 
 * list by following the 'next' pointers until it reaches the end (when 'next' is NULL), and for each 
 * layer encountered, it pushes that layer into the Layers vector. The function returns an integer 
 * representing the total number of layers processed.
 *
 * @param Head A pointer to the head of a linked list of tmx_layer objects.
 * @return An integer representing the total number of layers processed.
 */
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
		/**
 * @brief Default constructor for the MovementComponent class.
 *
 * This function initializes a new instance of the MovementComponent class with default values. It does not take any parameters and returns nothing. The component is initialized to have no movement properties set.
 *
 * @return void
 */
MovementComponent() = default;
		/**
 * @brief Default copy constructor for the MovementComponent class.
 *
 * This function is used to create a new instance of the MovementComponent class by copying an existing one. It uses the '= default' syntax, which instructs the compiler to generate a default implementation for this member function.
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
 *
 * This function initializes a new instance of the BoxComponent class with default values.
 * It does not take any parameters and returns nothing.
 */
BoxComponent() = default;
		/**
 * @brief Default copy constructor for the BoxComponent class.
 *
 * This function is used to create a new instance of the BoxComponent class by copying an existing one. It uses the '= default' syntax, which instructs the compiler to generate a default implementation for this member function.
 *
 * @param[in] other The BoxComponent object to be copied.
 * 
 * @return A new BoxComponent instance that is a copy of the input parameter.
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
 *
 * This function initializes a new instance of the CircleRendererComponent class with default values.
 * It does not take any parameters and returns nothing.
 */
CircleRendererComponent() = default;
		/**
 * @brief Default copy constructor for the CircleRendererComponent class.
 * This function is used to create a new instance of the class by copying an existing one, which can be useful in scenarios where you need to clone objects or handle memory management.
 * 
 * @param other The existing instance of the CircleRendererComponent class to copy from.
 */
CircleRendererComponent(const CircleRendererComponent&) = default;

		/**
 * @brief This function serializes the data of a circle renderer component into a DataWriter object.
 * 
 * @param[in] Serializer A pointer to the DataWriter object where the data will be written.
 * @param[in] Data The CircleRendererComponent whose data is being serialized.
 */
static void Serialize(DataWriter* Serializer, const CircleRendererComponent& Data)
		{

		}

		/**
 * @brief This function deserializes a CircleRendererComponent from the provided DataReader.
 * 
 * @param[in] Serializer A pointer to the DataReader that contains the serialized data.
 * @param[out] Data The CircleRendererComponent to be populated with the deserialized data.
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
 * @brief Constructs an AudioComponent with a reference to the given AudioEngine.
 * @param[in] Engine A reference to the AudioEngine that this component will use.
 */
AudioComponent(const Ref<AudioEngine>& Engine)
		{
			Audio = Engine;
		}

		/**
 * @brief Default copy constructor for the AudioComponent class.
 *
 * This function is used to create a new instance of an AudioComponent by copying data from another existing instance.
 * The actual behavior depends on the specific implementation of the AudioComponent class, which may involve deep or shallow copying.
 * 
 * @param other The existing AudioComponent instance to copy data from.
 */
AudioComponent(const AudioComponent&) = default;


		/**
 * @brief This function serializes an instance of the AudioComponent class into a DataWriter object.
 * 
 * The function takes in two parameters - a pointer to a DataWriter object and a constant reference to an AudioComponent object. It does not return anything, hence void is used as the return type.
 * 
 * @param Serializer A pointer to a DataWriter object that will be serializing the data from the AudioComponent object.
 * @param Data The constant reference to an AudioComponent object whose data needs to be serialized.
 */
static void Serialize(DataWriter* Serializer, const AudioComponent& Data)
		{

		}

		/**
 * @brief This function deserializes data from a serialized format into an AudioComponent object.
 * 
 * @param[in] Serializer A pointer to the DataReader instance that provides the serialized data.
 * @param[out] Data The AudioComponent object where the deserialized data will be stored.
 * 
 * @return void
 */
static void Deserialize(DataReader* Serializer, AudioComponent& Data)
		{

		}

		/**
 * @brief This function adds a sound to the Sounds vector.
 *
 * @param Sound A reference to an AudioSource object that represents the sound to be added.
 * If the provided Sound is null, this function does nothing and returns immediately.
 */
void AddSound(Ref<AudioSource> Sound) 
		{
			if (Sound)
			{
				Sounds.push_back(Sound); 
			}
		}

		/**
 * @brief Gets the reference to the audio engine instance.
 *
 * This function returns a reference to the global instance of the AudioEngine class, which is used by other parts of the application for managing and playing sounds.
 *
 * @return Reference to the global AudioEngine instance.
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
 *
 * This function initializes a new instance of the CameraComponent class with default values.
 * It does not take any parameters and returns nothing.
 */
CameraComponent() = default;
		/**
 * @brief Default copy constructor for the CameraComponent class.
 *
 * This function is used to create a new instance of the CameraComponent class by copying an existing one. It uses the 'default' keyword, which means it will use the compiler-generated default implementation.
 * 
 * @param[in] other The CameraComponent object to be copied.
 * 
 * @return A new CameraComponent object that is a copy of the input parameter.
 */
CameraComponent(const CameraComponent& ) = default;


		/**
 * @brief This function serializes a camera component into a data writer.
 * 
 * The function takes in two parameters - a pointer to a DataWriter and a constant reference to a CameraComponent. It does not return anything as it is a void function.
 * 
 * @param Serializer A pointer to the DataWriter that will be used for serialization.
 * @param Data The camera component that needs to be serialized.
 */
static void Serialize(DataWriter* Serializer, const CameraComponent& Data)
		{

		}

		/**
 * @brief This function deserializes a CameraComponent object from the provided DataReader instance.
 * 
 * The function reads data from the serialized format and populates the CameraComponent reference with this data.
 * 
 * @param Serializer A pointer to an instance of DataReader that provides the serialized data.
 * @param Data Reference to a CameraComponent object which will be filled with deserialized data.
 * 
 * @return void
 */
static void Deserialize(DataReader* Serializer, CameraComponent& Data)
		{

		}

		/**
 * @brief This function is used to activate an object by setting the 'bPrimary' variable to true.
 * 
 * @return void
 */
void Activate()
		{
			bPrimary = true;
		}

		/**
 * @brief This function is used to deactivate the primary status of an object.
 *
 * It sets the boolean variable 'bPrimary' to false, indicating that this object is no longer the primary one.
 * 
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
 * @brief Returns the body type of the object.
 * @return BodyType The type of the body (e.g., human, robot).
 */
BodyType GetBodyType() { return Type; }
		/**
 * @brief Sets the body type of an object.
 *
 * This function sets the BodyType variable to a specified value, which can be either SEDAN, HATCHBACK or SUV.
 * The new value is then stored in the Type member variable for future use.
 *
 * @param type The desired BodyType to set. Can be one of: SEDAN, HATCHBACK, or SUV.
 * @return void No return value.
 */
void SetBodyType(BodyType type) { Type = type; }
		/**
 * @brief Default constructor for RigidBody2DComponent class.
 */
RigidBody2DComponent() = default;
		/**
 * @brief Default copy constructor for the RigidBody2DComponent class.
 * This function is used to create a new instance of the RigidBody2DComponent by copying an existing one.
 * The copied object will have the same properties as the original, including its position, velocity and mass.
 * 
 * @param other The RigidBody2DComponent to be copied.
 */
RigidBody2DComponent(const RigidBody2DComponent&) = default;

		/**
 * @brief This function serializes the data of a RigidBody2DComponent.
 * 
 * The function takes in two parameters - a pointer to a DataWriter object and a constant reference to a RigidBody2DComponent object. It does not return anything, hence it is declared as 'static void'.
 * 
 * @param Serializer A pointer to the DataWriter object that will be used for serialization.
 * @param Data The RigidBody2DComponent whose data needs to be serialized.
 */
static void Serialize(DataWriter* Serializer, const RigidBody2DComponent& Data)
		{

		}

		/**
 * @brief This function deserializes the data from a serialized format into an instance of `RigidBody2DComponent`.
 * 
 * The function takes in two parameters - a pointer to a `DataReader` object and a reference to a `RigidBody2DComponent` object. It does not return anything, but it modifies the `RigidBody2DComponent` object by deserializing data from the provided `DataReader` object.
 * 
 * @param Serializer A pointer to an instance of `DataReader` that contains serialized data.
 * @param Data A reference to an instance of `RigidBody2DComponent` where the deserialized data will be stored.
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
 * @brief Default constructor for BoxCollider2DComponent class.
 * 
 * This function initializes a new instance of the BoxCollider2DComponent class with default values.
 * It does not take any parameters and returns nothing.
 */
BoxCollider2DComponent() = default;
		/**
 * @brief Default copy constructor for the BoxCollider2DComponent class.
 *
 * This function is used to create a new instance of the BoxCollider2DComponent class by copying an existing one. It uses the '= default' syntax, which tells the compiler to use the default implementation provided by the compiler.
 *
 * @param[in] other The BoxCollider2DComponent instance to copy from.
 * 
 * @return A new BoxCollider2DComponent object that is a copy of the input parameter 'other'.
 */
BoxCollider2DComponent(const BoxCollider2DComponent&) = default;

		/**
 * @brief This function serializes the data of a 2D box collider component into a DataWriter.
 * @param[in] Serializer Pointer to the DataWriter object where the data will be written.
 * @param[in] Data The BoxCollider2DComponent whose data is being serialized.
 * @return void
 */
static void Serialize(DataWriter* Serializer, const BoxCollider2DComponent& Data)
		{

		}

		/**
 * @brief This function deserializes a BoxCollider2DComponent from the provided DataReader.
 * 
 * The function reads data from the serialized format and populates the BoxCollider2DComponent with it.
 * It uses the provided DataReader to read the necessary information for the component.
 * 
 * @param Serializer A pointer to a DataReader object that provides the serialized data.
 * @param Data The BoxCollider2DComponent to be populated with deserialized data.
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

		COMMENT:
/**
 * @brief Default constructor for the CapsuleCollider2DComponent class.
 *
 * This function initializes a new instance of the CapsuleCollider2DComponent class with default values.
 */
CONFIDENCE: 1.0;

CapsuleCollider2DComponent() = default;
		/**
 * @brief Default copy constructor for the CapsuleCollider2DComponent class.
 * This function is used to create a new instance of the class by copying an existing one, which can be useful in certain situations where you need to duplicate an object without manually defining each attribute.
 * 
 * @param other The existing instance of the class that will be copied.
 */
CapsuleCollider2DComponent(const CapsuleCollider2DComponent&) = default;

		/**
 * @brief This function serializes the data of a 2D capsule collider component.
 * 
 * @param[in] Serializer A pointer to an instance of DataWriter that is responsible for writing the serialized data.
 * @param[in] Data The CapsuleCollider2DComponent whose data needs to be serialized.
 * 
 * @return void
 */
static void Serialize(DataWriter* Serializer, const CapsuleCollider2DComponent& Data)
		{

		}

		/**
 * @brief This function deserializes a CapsuleCollider2DComponent from the provided DataReader.
 * 
 * The function reads data from the serializer and populates the given CapsuleCollider2DComponent with this data.
 * It does not return anything as it directly modifies the passed in component.
 *
 * @param Serializer A pointer to a DataReader that provides the serialized data.
 * @param Data The CapsuleCollider2DComponent to be deserialized and populated.
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
 *
 * This function is used to create a new instance of the class by copying an existing one. It uses the '= default' syntax, which tells the compiler to use the default implementation provided by the compiler.
 *
 * @param[in] other The SegmentCollider2DComponent instance to copy.
 * 
 * @return A new instance of the SegmentCollider2DComponent class with the same values as the input parameter 'other'.
 */
SegmentCollider2DComponent(const SegmentCollider2DComponent&) = default;

		/**
 * @brief This function serializes the data of a 2D segment collider component.
 * 
 * The function takes in two parameters - a pointer to a DataWriter object and a constant reference to a SegmentCollider2DComponent object. It does not return anything, hence it is declared as 'static void'.
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
 * @brief This function serializes a NativeScriptComponent object into a DataWriter.
 * 
 * @param[in] Serializer Pointer to the DataWriter where the data will be written.
 * @param[in] Data The NativeScriptComponent object that needs to be serialized.
 * 
 * @return void
 */
static void Serialize(DataWriter* Serializer, const NativeScriptComponent& Data)
		{

		}

		/**
 * @brief This function deserializes data from a given serialization source into the provided native script component.
 * 
 * @param[in] Serializer A pointer to the data reader object that provides the serialized data.
 * @param[out] Data The native script component where the deserialized data will be stored.
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
 * @brief This function binds a new scriptable entity to the NativeScriptComponent. It creates an instance of this entity using a lambda, InstantiateScript, and stores it in the NativeScriptComponent. 
 *        The DestroyScript lambda is used to delete the instance when necessary.
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