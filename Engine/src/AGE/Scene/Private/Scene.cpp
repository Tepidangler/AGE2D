#include "AGEpch.hpp"

#include "Core/Public/Core.h"
#include "Core/Public/App.h"
#include "Physics/Public/Physics2D.h"
#include "Physics/Public/World.h"
#include "Scene/Public/Scene.h"
#include "Scene/Public/Components.h"
#include "Scene/Public/SceneCamera.h"
#include "Scene/Public/ScriptableEntity.h"
#include "Scene/Public/Entity.h"
#include "Utils/Public/Serializers.h"
#include "Project/Public/Project.h"
#include "Structs/Public/DataStructures.h"
#include "Texture/Public/SubTexture.h"
#include "Render/Public/Renderer.h"
#include "Render/Public/Renderer2D.h"
#include "Assets/Public/AssetManager.h"


#include <box2d/types.h>

namespace AGE
{
	template<typename Component>
	"Copies a Component from one entt::registry to another based on UUID mapping."
static void CopyComponent(entt::registry& dst, entt::registry& src, const std::unordered_map<UUID, entt::entity>& enttMap)
	{
		auto View = src.view<Component>();


		for (auto E : View)
		{
			UUID uuid = src.get<IDComponent>(E).ID;

			CoreLogger::Assert(enttMap.find(uuid) != enttMap.end(), "UUID not found!");
			entt::entity dstEnttID = enttMap.at(uuid);


			if (src.any_of<Component>(E))
			{
				auto& component = src.get<Component>(E);
				dst.emplace_or_replace<Component>(dstEnttID, component);
			}


		}
	}

	template<typename Component>
	/**
 * @brief Copies a component from one entity to another if the source entity has that component.
 * 
 * This function checks if the source entity (`src`) has a specific component, and if it does, adds or replaces that component on the destination entity (`dst`).
 * 
 * @param dst The destination entity to which the component will be added or replaced.
 * @param src The source entity from where the component will be copied.
 * 
 * @return void
 */
static void CopyComponentIfExists(Entity dst, Entity src)
	{
		if (src.HasComponent<Component>())
		{
			dst.AddOrReplaceComponent<Component>(src.GetComponent<Component>());
		}
	}

	/**
 * @brief Constructs a Scene object.
 * 
 * This function initializes the scene by creating an instance of TileMapImporter and Physics2D, both of which are members of the Scene class. The TileMapImporter is initialized with this as its argument to allow it access to private data within the Scene class. The Physics2D object is created using CreateRef, a function that returns a shared_ptr to an instance of Physics2D.
 * 
 * @return A new Scene object.
 */
Scene::Scene()
	{
		m_Physics = CreateRef<Physics2D>();
	}
	/**
 * @brief Destructor for the Scene class.
 *
 * This function is responsible for cleaning up any resources that were allocated during the lifetime of a Scene object. 
 * It currently does not perform any specific cleanup actions as there are no dynamically allocated resources in the Scene class.
 *
 * @return void
 */
Scene::~Scene()
	{

	}
	/**
 * @brief Creates an entity with a given name and assigns it a UUID.
 * 
 * This function creates an Entity object with the provided name, generates a unique UUID for it using the `UUID()` function, and then adds this new entity to the scene's list of entities. The newly created entity is returned by the function.
 * 
 * @param Name A string representing the name of the entity to be created.
 * @return An Entity object with a UUID that has been assigned.
 */
Entity Scene::CreateEntity(const std::string Name)
	{
		return CreateEntityWithUUID(UUID(), Name);
	}

	/**
 * @brief Creates an entity with a specific UUID and name.
 * 
 * This function creates an entity, assigns it a unique ID (UUID), adds TransformComponent to the entity,
 * and sets its tag to either the provided name or "UnnamedEntity" if no name is provided. The created entity
 * is then returned.
 * @param uuid The UUID for the new entity.
 * @param Name The optional name of the new entity. If not provided, it will default to "UnnamedEntity".
 * @return Entity The newly created entity.
 */
Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& Name)
	{
		Entity ent = { m_Registry.create(), this };
		ent.AddComponent<IDComponent>();
		ent.GetComponent<IDComponent>().ID = uuid;
		ent.AddComponent<TransformComponent>();
		auto& tag = ent.AddComponent<TagComponent>(Name);
		tag.Tag = Name.empty() ? "UnnamedEntity" : Name;
		return ent;
	}

	/**
 * @brief Retrieves an entity from the scene using its UUID.
 *
 * This function iterates over all entities in the registry and checks if their IDComponent has a matching UUID. If found, it returns the corresponding Entity object. 
 *
 * @param uuid The UUID of the entity to retrieve.
 * @return An Entity object representing the entity with the given UUID, or an empty Entity if no such entity exists in the scene.
 */
Entity Scene::GetEntityFromUUID(const uint64_t uuid)
	{
		AGE_PROFILE_FUNCTION();
		
		auto View = m_Registry.view<IDComponent, SpriteRendererComponent>();

		for (auto E : View)
		{
			auto [ID,SRC] = View.get<IDComponent, SpriteRendererComponent>(E);

			if (ID.ID == uuid)
			{
				return Entity{ E,this };
			}
		}
		return {};
	}

	/**
 * @brief Copies a scene from another one.
 * 
 * This function creates a new instance of the Scene class, copies over all components (except for ID and Tag) from the source scene to the newly created one, and maps entities in the source registry to their corresponding entities in the destination registry.
 * 
 * @param Other A reference to the source scene that is being copied.
 * @return A new instance of Scene with all components except IDComponent and TagComponent copied from the source scene.
 */
Ref<Scene> Scene::Copy(Ref<Scene> Other)
	{
		Ref<Scene> NewScene = CreateRef<Scene>();

		NewScene->m_ViewportWidth = Other->m_ViewportWidth;
		NewScene->m_ViewportHeight = Other->m_ViewportHeight;

		auto& SrcSceneRegistry = Other->m_Registry;
		auto& DstSceneRegistry = NewScene->m_Registry;

		std::unordered_map<UUID, entt::entity> enttMap;

		auto IDView = SrcSceneRegistry.view<IDComponent>();

		for (auto E : IDView)
		{
			UUID uuid = SrcSceneRegistry.get<IDComponent>(E).ID;
			const auto& Name = SrcSceneRegistry.get<TagComponent>(E).Tag;
			Entity NewEntity = NewScene->CreateEntityWithUUID(uuid, Name);
			enttMap[uuid] = (entt::entity)NewEntity;
		}

		//Copy Except ID and Tag

		CopyComponent<TransformComponent>(DstSceneRegistry, SrcSceneRegistry, enttMap);
		CopyComponent<SpriteRendererComponent>(DstSceneRegistry, SrcSceneRegistry, enttMap);
		CopyComponent<TileMapRendererComponent>(DstSceneRegistry, SrcSceneRegistry, enttMap);
		CopyComponent<CircleRendererComponent>(DstSceneRegistry, SrcSceneRegistry, enttMap);
		CopyComponent<AudioComponent>(DstSceneRegistry, SrcSceneRegistry, enttMap);
		CopyComponent<CameraComponent>(DstSceneRegistry, SrcSceneRegistry, enttMap);
		CopyComponent<NativeScriptComponent>(DstSceneRegistry, SrcSceneRegistry, enttMap);
		CopyComponent<RigidBody2DComponent>(DstSceneRegistry, SrcSceneRegistry, enttMap);
		CopyComponent<BoxCollider2DComponent>(DstSceneRegistry, SrcSceneRegistry, enttMap);
		CopyComponent<SegmentCollider2DComponent>(DstSceneRegistry, SrcSceneRegistry, enttMap);
		CopyComponent<CapsuleCollider2DComponent>(DstSceneRegistry, SrcSceneRegistry, enttMap);

		return NewScene;

	}

	/**
 * @brief Duplicates an Entity in the Scene.
 * 
 * This function duplicates a given Entity by creating a new one with the same name and copying all its components from the original Entity to the new one.
 * The components copied are TransformComponent, SpriteRendererComponent, TileMapRendererComponent, CircleRendererComponent, AudioComponent, CameraComponent, NativeScriptComponent, RigidBody2DComponent, BoxCollider2DComponent, SegmentCollider2DComponent and CapsuleCollider2DComponent.
 * 
 * @param entity The Entity to be duplicated.
 */
void Scene::DuplicateEntity(Entity entity)
	{
		std::string Name = entity.GetName();
		Entity NewEntity = CreateEntity(Name);

		CopyComponentIfExists<TransformComponent>(NewEntity, entity);
		CopyComponentIfExists<SpriteRendererComponent>(NewEntity, entity);
		CopyComponentIfExists<TileMapRendererComponent>(NewEntity, entity);
		CopyComponentIfExists<CircleRendererComponent>(NewEntity, entity);
		CopyComponentIfExists<AudioComponent>(NewEntity, entity);
		CopyComponentIfExists<CameraComponent>(NewEntity, entity);
		CopyComponentIfExists<NativeScriptComponent>(NewEntity, entity);
		CopyComponentIfExists<RigidBody2DComponent>(NewEntity, entity);
		CopyComponentIfExists<BoxCollider2DComponent>(NewEntity, entity);
		CopyComponentIfExists<SegmentCollider2DComponent>(NewEntity, entity);
		CopyComponentIfExists<CapsuleCollider2DComponent>(NewEntity, entity);
	}
	
	/**
 * @brief This function returns the primary camera entity in the scene.
 * 
 * The function iterates over all entities with a CameraComponent and checks if any of them is marked as primary. If it finds one, it returns that entity. Otherwise, it returns an empty entity.
 * 
 * @return Entity - The primary camera entity in the scene. Returns an empty entity if no primary camera exists.
 */
Entity Scene::GetPrimaryCameraEntity()
	{
		auto View = m_Registry.view<CameraComponent>();
		for (auto E : View)
		{
			const auto& Camera = View.get<CameraComponent>(E);
			if (Camera.bPrimary)
			{
				return Entity{ E,this };
			}
		}
		return {};
	}

	
void Scene::OnRuntimeStart()
	{

		m_Physics->CreateNewPhysicsWorld(shared_from_this());
		{
			m_Registry.view<NativeScriptComponent>().each([&](auto entity, auto& NSC)
				{
					if (!NSC.Instance)
					{
						NSC.Instance = NSC.InstantiateScript();
						NSC.Instance->m_Entity = Entity{ entity,this };

						NSC.Instance->OnCreate();
						NSC.Instance->PushComp();

					}
					NSC.Instance->OnBeginPlay();

				});

			auto View = m_Registry.view<RigidBody2DComponent>();

			for (auto E : View)
			{
				Entity entity = { E, this };
				auto Transform = entity.GetComponent<TransformComponent>();
				auto RB2D = entity.GetComponent<RigidBody2DComponent>();

				b2BodyDef BodyDef = m_Physics->MakeBodyDefinition(RB2D.Type, Transform.Translation, Transform.Rotation, RB2D.FixedRotation, &entity);
				RB2D.BodyID = m_Physics->CreateBody(BodyDef);


				if (entity.HasComponent<BoxCollider2DComponent>())
				{
					auto& BC2D = entity.GetComponent<BoxCollider2DComponent>();

					b2Polygon Box = m_Physics->CreateBox(BC2D.Size.x, BC2D.Size.y, Transform.Scale);
					b2ShapeDef Fixture = m_Physics->MakeShapeDefinition(BC2D.Density, BC2D.Friction, BC2D.Restitution, BC2D.bGeneratePhysicsEvents, (void*)(intptr_t)E);
					BC2D.ShapeID = m_Physics->CreatePolygonShape(RB2D.BodyID, Fixture, Box);
				}

				if (entity.HasComponent<CapsuleCollider2DComponent>())
				{
					auto& CC2D = entity.GetComponent<CapsuleCollider2DComponent>();

					b2Capsule Capsule = m_Physics->CreateCapsule(CC2D.Offset, Transform.Scale, CC2D.Radius);
					b2ShapeDef Fixture = m_Physics->MakeShapeDefinition(CC2D.Density, CC2D.Friction, CC2D.Restitution, CC2D.bGeneratePhysicsEvents, (void*)(intptr_t)E);
					CC2D.ShapeID = m_Physics->CreateCapsuleShape(RB2D.BodyID, Fixture, Capsule);
				}

				if (entity.HasComponent<SegmentCollider2DComponent>())
				{
					auto& SC2D = entity.GetComponent<SegmentCollider2DComponent>();

					b2Segment Segment = m_Physics->CreateSegment();
					b2ShapeDef Fixture = m_Physics->MakeShapeDefinition(SC2D.Density, SC2D.Friction, SC2D.Restitution, SC2D.bGeneratePhysicsEvents, (void*)(intptr_t)E);
					SC2D.ShapeID = m_Physics->CreateSegmentShape(RB2D.BodyID, Fixture, Segment);
				}
			}
		}


	}

	/**
 * @brief This function is called when the runtime of the application stops. It unloads sounds, destroys the physics world and resets all native script instances.
 * 
 * @param None
 * 
 * @return void
 */
void Scene::OnRuntimeStop()
	{
		//TODO: UnloadSounds
		//b2DestroyWorld(Physics2D::GetWorldID());
		m_Physics->DestroyWorld();
		auto View = m_Registry.view<AudioComponent>();

		for (auto E : View)
		{
			auto Audio = View.get<AudioComponent>(E);
			//Audio.GetAudioEngine()Stop(Audio.Sounds);
		}

		m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& NSC)
			{
				NSC.Instance->Reset();

			});

	}

	
void Scene::OnRuntimeUpdate(TimeStep DeltaTime)
	{
		m_Physics->Step(DeltaTime);
		{

			auto View = m_Registry.view<TransformComponent, RigidBody2DComponent, BoxCollider2DComponent>();

			for (auto E : View)
			{
				Entity entity = { E, this };
				auto [Transform, RB2D, BC2D] = View.get<TransformComponent, RigidBody2DComponent, BoxCollider2DComponent>(E);
				
				b2BodyId BodyId = m_Physics->GetBody(BC2D.ShapeID);
				const auto& Position = m_Physics->GetBodyPosition(BodyId);
				
				Vector2 Point{Position.x,Position.y};
				QueryParams Params;
				Params.Box2D = m_Physics->GetPolygon(BC2D.ShapeID);
				Params.Point2D = Point;
				Params.Location = Transform.Translation;
				Params.Rotation = Transform.Rotation;
				Params.OverlapFunc2D = [](b2ShapeId shapeId, void* context) -> bool
					{
						Scene* scene = (Scene*)context;
						int EnttID = (int)(intptr_t)scene->m_Physics->GetUserData(shapeId);
						Entity userData = Entity((entt::entity)EnttID, scene);
						userData.GetComponent<NativeScriptComponent>().Instance->OnOverlapStart();
						return true;
					};
				Params.CastFunc2D = [](b2ShapeId shapeId, b2Vec2 point, b2Vec2 normal, float fraction, void* context) -> float
					{
						Scene* scene = (Scene*)context;
						int EnttID = (int)(intptr_t)scene->m_Physics->GetUserData(shapeId);
						Entity userData = Entity((entt::entity)EnttID, scene);

						userData.GetComponent<NativeScriptComponent>().Instance->OnHit();

						return fraction;
					};
				Params.Context = this;
				m_Physics->QueryBoxOverlap(Params);
				
				//Physics2D::QueryHit(m_PhysicsWorld, Point);
				Transform.Translation.x = Position.x;
				Transform.Translation.y = Position.y;
				Transform.Rotation.z = m_Physics->GetRotationAngle(BodyId);
			}
		}

		{
			auto View = m_Registry.view<TransformComponent, RigidBody2DComponent, CapsuleCollider2DComponent>();

			for (auto E : View)
			{
				Entity entity = { E, this };

				auto [Transform, RB2D, CC2D] = View.get<TransformComponent, RigidBody2DComponent, CapsuleCollider2DComponent>(E);

				b2BodyId BodyId = m_Physics->GetBody(CC2D.ShapeID);

				const auto& Position = m_Physics->GetBodyPosition(BodyId);

				Vector2 Point{ Position.x,Position.y };

				QueryParams Params;
				Params.Capsule2D = m_Physics->GetCapsule(CC2D.ShapeID);
				Params.Point2D = Point;
				Params.Location = Transform.Translation;
				Params.Rotation = Transform.Rotation;
				Params.OverlapFunc2D = [](b2ShapeId shapeId, void* context) -> bool
					{
						Scene* scene = (Scene*)context;
						int EnttID = (int)(intptr_t)scene->m_Physics->GetUserData(shapeId);
						Entity userData = Entity((entt::entity)EnttID, scene);
						userData.GetComponent<NativeScriptComponent>().Instance->OnOverlapStart();
						return true;
					};
				Params.CastFunc2D = [](b2ShapeId shapeId, b2Vec2 point, b2Vec2 normal, float fraction, void* context) -> float
					{
						Scene* scene = (Scene*)context;
						int EnttID = (int)(intptr_t)scene->m_Physics->GetUserData(shapeId);
						Entity userData = Entity((entt::entity)EnttID, scene);

						userData.GetComponent<NativeScriptComponent>().Instance->OnHit();

						return fraction;
					};
				Params.Context = this;

				m_Physics->QueryCapsuleOverlap(Params);
				Transform.Translation.x = Position.x;
				Transform.Translation.y = Position.y;
				Transform.Rotation.z = m_Physics->GetRotationAngle(BodyId);
			}
		}
		{
			auto View = m_Registry.view<TransformComponent, RigidBody2DComponent, SegmentCollider2DComponent>();

			for (auto E : View)
			{
				auto [Transform, RB2D, SC2D] = View.get<TransformComponent, RigidBody2DComponent, SegmentCollider2DComponent>(E);

				b2BodyId BodyId = m_Physics->GetBody(SC2D.ShapeID);

				const auto& Position = m_Physics->GetBodyPosition(BodyId);

				Transform.Translation.x = Position.x;
				Transform.Translation.y = Position.y;
				Transform.Rotation.z = m_Physics->GetRotationAngle(BodyId);
			}
		}

		SceneCamera* MainCamera = nullptr;
		Matrix4D CameraTransform;
		{
			auto View = m_Registry.view<TransformComponent,CameraComponent>();
			for (auto E : View)
			{
				auto [Transform, Cam] = View.get<TransformComponent, CameraComponent>(E);
					if (Cam.bPrimary)
					{
						MainCamera = &Cam.Cam;
						MainCamera->SetProjectionType(ProjectionType::Perspective);
						CameraTransform = Transform.GetTransform();
					}
					if (!Cam.bPrimary && !Cam.bRecording)
					{
						Cam.Deactivate();
					}

			}
		}

		if (MainCamera)
		{
			Renderer::BeginScene(MainCamera->GetProjection(), CameraTransform);
			{

				{
					auto View = m_Registry.view<TileMapRendererComponent, TransformComponent>();
					for (auto E : View)
					{
						auto [Map, Transform] = View.get<TileMapRendererComponent, TransformComponent>(E);

						if (Map.TileMap)
						{
						}
					}

				}
				{
					m_Registry.view<NativeScriptComponent>().each([&](auto entity, auto& NSC)
						{
							if (!NSC.Instance)
							{
								NSC.Instance = NSC.InstantiateScript();
								NSC.Instance->m_Entity = Entity{ entity,this };

								NSC.Instance->OnCreate();
								NSC.Instance->PushComp();

							}
							NSC.Instance->OnUpdate(DeltaTime);

						});
				}

				{
					auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
					for (auto E : group)
					{
						auto [Transform, Sprite] = group.get<TransformComponent, SpriteRendererComponent>(E);

						Sprite.QuadProps.Transform = Transform.GetTransform();
						if (Sprite.Texture.get())
						{
							Sprite.QuadProps.TintColor = Sprite.Color;
							Sprite.QuadProps.EntityID = (int)E;
							Renderer2D::DrawSprite(Sprite);
						}

						if (Sprite.AnimTextures.size() > 0)
						{
							Sprite.QuadProps.TintColor = Sprite.Color;
							Sprite.QuadProps.EntityID = (int)E;
							Renderer2D::DrawSprite(Sprite);
							Sprite.AnimInstance.OnAnimate(DeltaTime);

						}

						if (Sprite.SubTexture.get() != nullptr && !Sprite.bTile)
						{
							Sprite.QuadProps.TintColor = Sprite.Color;
							Sprite.QuadProps.EntityID = (int)E;
							Renderer2D::DrawSprite(Sprite);
						}
					}

				}

				{
					auto View = m_Registry.view<TransformComponent, CircleRendererComponent>();

					for (auto E : View)
					{
						auto [Transform, Circle] = View.get<TransformComponent, CircleRendererComponent>(E);

						Renderer2D::DrawCircle(Transform.GetTransform(), Circle.Color, Circle.Thickness, Circle.Fade, (int)E);
					}

				}

				{
					auto View = m_Registry.view<TileMapRendererComponent, AudioComponent>();

					for (auto E : View)
					{
						[[maybe_unused]] auto [Map, Audio] = View.get<TileMapRendererComponent, AudioComponent>(E);

						//if (Audio.Sounds[0] && !Audio.Sounds[0]->IsPlaying())
						//{
						//	//AGESound::Play(Audio.Sounds[0]);
						//	//Audio.Sounds[0]->SetPlaying(true);
						//}

					}
				}



			}

			RenderUIEvent Data(DeltaTime);
			App::Get().OnEvent(Data);

			Renderer::EndScene();
		}
	}

	
void Scene::OnEditorUpdate(TimeStep DeltaTime, EditorCamera& Camera)
	{
		AGE_PROFILE_FUNCTION();
		Renderer2D::BeginScene(Camera);

		{
			m_Registry.view<NativeScriptComponent>().each([&](auto entity, auto& NSC)
				{
					if (!NSC.Instance)
					{
						NSC.Instance = NSC.InstantiateScript();
						NSC.Instance->m_Entity = Entity{ entity,this };

						NSC.Instance->OnCreate();
						NSC.Instance->PushComp(); //TODO: TEMP

					}
					NSC.Instance->OnUpdate(DeltaTime);
				});
		}



		{

			auto View = m_Registry.view<TileMapRendererComponent, TransformComponent>();
			for (auto E : View)
			{
				auto [Map, Transform] = View.get<TileMapRendererComponent, TransformComponent>(E);
				if (Map.TileMap)
				{

				}
			}

		}

		{
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto E : group)
			{
				auto [Transform, Sprite] = group.get<TransformComponent, SpriteRendererComponent>(E);

				Sprite.QuadProps.Transform = Transform.GetTransform();
				if (Sprite.AnimIsReady())
				{
					Sprite.QuadProps.TintColor = Sprite.Color;
					Sprite.QuadProps.EntityID = (int)E;
					Renderer2D::DrawSprite(Sprite);
					Sprite.AnimInstance.OnAnimate(DeltaTime);

				}

				if (Sprite.Texture.get() != nullptr)
				{
					Sprite.QuadProps.TintColor = Sprite.Color;
					Sprite.QuadProps.EntityID = (int)E;
					Renderer2D::DrawSprite(Sprite);
				}

				if (Sprite.SubTexture.get() != nullptr && !Sprite.bTile)
				{
					Sprite.QuadProps.TintColor = Sprite.Color;
					Sprite.QuadProps.EntityID = (int)E;
					Renderer2D::DrawSprite(Sprite);
				}
			}
		}

		{
			auto View = m_Registry.view<TransformComponent, CircleRendererComponent>();

			for (auto E : View)
			{
				auto [Transform, Circle] = View.get<TransformComponent, CircleRendererComponent>(E);

				Renderer2D::DrawCircle(Transform.GetTransform(), Circle.Color, Circle.Thickness, Circle.Fade, (int)E);
			}

		}
		RenderUIEvent Data(DeltaTime);
		App::Get().OnEvent(Data);

		Renderer2D::EndScene();
		//RenderCommand::Flush();
	}

	/**
 * @brief This function is called when the viewport size changes. It updates all camera components to reflect the new viewport dimensions.
 * 
 * @param Width The new width of the viewport.
 * @param Height The new height of the viewport.
 * 
 * @return None
 */
void Scene::OnViewportResize(uint32_t Width, uint32_t Height)
	{
		m_ViewportWidth = Width;
		m_ViewportHeight = Height;


		auto View = m_Registry.view<CameraComponent>();
		for (auto E : View)
		{
			auto& CameraComp = View.get<CameraComponent>(E);

			if (!CameraComp.bFixedAspectRatio)
			{
				CameraComp.Cam.SetViewportSize(Width,Height);
			}
		}
		
	}
	/**
 * @brief Destroys an entity from the scene's registry.
 * 
 * This function removes an Entity from the Registry of the Scene object. It takes as input a reference to an Entity, and destroys it by removing it from the Registry.
 * 
 * @param E A reference to the Entity that is to be destroyed.
 * @return void
 */
void Scene::DestoryEntity(Entity E)
	{
		m_Registry.destroy(E);
	}

	/**
 * @brief Builds a scene and saves it in a file within the "BuiltScenes" directory.
 * 
 * Checks if the "BuiltScenes" directory exists at the parent path of the project path. If not, creates this directory. Then writes the current scene object to a file with name equal to the scene's name and extension ".abs". Finally logs an info message indicating that the scene has been successfully built.
 * 
 * @param ProjectPath The path of the project used to determine where to save the built scene files.
 */
void Scene::BuildScene(const std::filesystem::path& ProjectPath)
	{
		if (std::filesystem::is_directory(ProjectPath.parent_path().string() + "/BuiltScenes/"))
		{
			CoreLogger::Info("Building {0}...", m_Name); // m_Name is EMPTY
			std::string FilePath;
			FilePath = ProjectPath.parent_path().string() + "/BuiltScenes/" + m_Name + ".abs";
			FileStreamWriter Stream(FilePath);
			Stream.WriteObject(*this);
			CoreLogger::Info("\t{0} Sucessfully Built!", m_Name);
		}
		else
		{
			std::filesystem::create_directories(ProjectPath.parent_path().string() + "/BuiltScenes/");
			CoreLogger::Info("Building {0}...", m_Name); // m_Name is EMPTY
			std::string FilePath;
			FilePath = ProjectPath.parent_path().string() + "/BuiltScenes/" + m_Name + ".abs";
			FileStreamWriter Stream(FilePath);
			Stream.WriteObject(*this);
			CoreLogger::Info("\t{0} Sucessfully Built!", m_Name);
		}

	}

	/**
 * @brief Loads a scene from the specified file path.
 * 
 * This function deserializes a scene from a JSON file and returns it as a `Ref<Scene>` object. The scene is loaded into an empty `Ref<Scene>` object, which can be accessed through the returned reference.
 * 
 * @param Path The filesystem path to the JSON file containing the serialized scene data.
 * @return A reference to the loaded scene.
 */
Ref<Scene> Scene::LoadScene(const std::filesystem::path& Path)
	{
		Ref<Scene> File = CreateRef<Scene>();
		SceneSerializer Serializer(File);

		Serializer.Deserialize(Path.string());

		return File;
	}

	
void Scene::BuildAllScenes()
	{
		AppConfig Config = App::Get().GetAppConfig();
		std::string ProjectName = Project::GetActive()->GetConfig().Name;
		if (!std::filesystem::is_directory(Config.CurrentProjectPath.string() + "/BuiltScenes/"))
		{
			std::filesystem::create_directory(Config.CurrentProjectPath.string() + "/BuiltScenes/");
		}

		for (const auto& S : std::filesystem::directory_iterator(Config.GameContentPath.string() + "../../Scenes"))
		{

			CoreLogger::Info("Building {0}...", S.path().filename().replace_extension().string());
			std::string FilePath;
			FilePath = Config.CurrentProjectPath.string() + "/BuiltScenes/" + S.path().filename().replace_extension().string() + ".abs";
			Ref<Scene> File = LoadScene(S.path());
			FileStreamWriter Stream(FilePath);
			Stream.WriteObject(*File.get());
			CoreLogger::Info("\t{0} Sucessfully Built!", S.path().filename().replace_extension().string());
		}
		CoreLogger::Error("Build All Scenes Not Implemented!");
	}

	template<typename T>
	/** 
 * @brief This function is called when a component is added to an entity in the scene.
 * 
 * @param E The entity that the component was added to.
 * @param Component A reference to the newly-added component.
 * 
 * @return void
 */
void Scene::OnComponentAdded(Entity E, T& Component)
	{
		//static_assert(false);
	}

	template<>
	/**
 * @brief This function is called when a new component of type `TagComponent` is added to an entity.
 * 
 * @param E The Entity that the new component was added to.
 * @param Component A reference to the newly added TagComponent.
 */
void Scene::OnComponentAdded<TagComponent>(Entity E, TagComponent& Component)
	{

	}
	template<>
	/**
 * @brief This function is called when a new component of type TransformComponent is added to an entity.
 * 
 * @param E The Entity that the new component has been added to.
 * @param Component A reference to the newly added TransformComponent.
 */
void Scene::OnComponentAdded<TransformComponent>(Entity E, TransformComponent& Component)
	{

	}	
	template<>
	/**
 * @brief This function is called when a new CameraComponent has been added to an Entity in the Scene. 
 * It sets the viewport size of the camera component's camera to match the current scene's viewport size.
 * 
 * @param E The Entity that the CameraComponent belongs to.
 * @param Component A reference to the newly added CameraComponent.
 */
void Scene::OnComponentAdded<CameraComponent>(Entity E, CameraComponent& Component)
	{
		Component.Cam.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}	
	template<>
	/**
 * @brief This function is called when a SpriteRendererComponent is added to an entity.
 * 
 * @param E The Entity that the component was added to.
 * @param Component A reference to the newly-added SpriteRendererComponent.
 */
void Scene::OnComponentAdded<SpriteRendererComponent>(Entity E, SpriteRendererComponent& Component)
	{

	}	
	template<>
	/** 
 * @brief This function is called when a new component of type `TileMapRendererComponent` is added to an entity.
 * 
 * @param[in] E The Entity that the new component has been added to.
 * @param[out] Component A reference to the newly created TileMapRendererComponent.
 * 
 * @return void
 */
void Scene::OnComponentAdded<TileMapRendererComponent>(Entity E, TileMapRendererComponent& Component)
	{

	}
	template<>
	/**
 * @brief This function is called when a new component of type `CircleRendererComponent` is added to an entity.
 * 
 * @param E The Entity that the new component was added to.
 * @param Component A reference to the newly added CircleRendererComponent.
 */
void Scene::OnComponentAdded<CircleRendererComponent>(Entity E, CircleRendererComponent& Component)
	{

	}
	template<>
	/**
 * @brief This function is called when a NativeScriptComponent is added to an Entity in the scene.
 * 
 * @param E The Entity that the NativeScriptComponent has been added to.
 * @param Component A reference to the NativeScriptComponent that was just added.
 * 
 * @return void
 */
void Scene::OnComponentAdded<NativeScriptComponent>(Entity E, NativeScriptComponent& Component)
	{

	}
	template<>
	/**
 * @brief This function is called when a new BoxComponent is added to an Entity in the scene.
 * 
 * @param E The Entity that has been given the new BoxComponent.
 * @param Component A reference to the newly created BoxComponent.
 */
void Scene::OnComponentAdded<BoxComponent>(Entity E, BoxComponent& Component)
	{

	}
	template<>
	/**
 * @brief This function is called when an AudioComponent is added to a specific Entity in the scene.
 * 
 * @param E The entity that the AudioComponent has been added to.
 * @param Component A reference to the AudioComponent that was just added.
 */
void Scene::OnComponentAdded<AudioComponent>(Entity E, AudioComponent& Component)
	{

	}
	template<>
	/** 
 * @brief This function is called when a new component of type RigidBody2DComponent has been added to the entity.
 * 
 * @param E The Entity that the new component was added to.
 * @param Component A reference to the newly added RigidBody2DComponent.
 * 
 * @return void
 */
void Scene::OnComponentAdded<RigidBody2DComponent>(Entity E, RigidBody2DComponent& Component)
	{

	}
	template<>
	/** 
 * @brief This function is called when a new BoxCollider2DComponent is added to an Entity.
 * 
 * @param E The Entity that the component was added to.
 * @param Component A reference to the newly added BoxCollider2DComponent.
 */
void Scene::OnComponentAdded<BoxCollider2DComponent>(Entity E, BoxCollider2DComponent& Component)
	{

	}
	template<>
	/**
 * @brief This function is called when a new CapsuleCollider2DComponent has been added to an Entity.
 * 
 * @param E The Entity that the component was added to.
 * @param Component A reference to the newly added CapsuleCollider2DComponent.
 */
void Scene::OnComponentAdded<CapsuleCollider2DComponent>(Entity E, CapsuleCollider2DComponent& Component)
	{

	}
	template<>
	/** 
 * @brief This function is called when a new component of type SegmentCollider2DComponent has been added to an entity.
 * 
 * @param E The Entity that the new component was added to.
 * @param Component A reference to the newly added SegmentCollider2DComponent.
 */
void Scene::OnComponentAdded<SegmentCollider2DComponent>(Entity E, SegmentCollider2DComponent& Component)
	{

	}
	template<>
	/**
 * @brief This function is called when a new component of type IDComponent is added to an entity.
 * 
 * @param E The Entity that the new component was added to.
 * @param Component A reference to the newly added IDComponent.
 */
void Scene::OnComponentAdded<IDComponent>(Entity E, IDComponent& Component)
	{

	}
	template<>
	/**
 * @brief This function is called when a new component of type `MovementComponent` is added to an entity.
 * 
 * @param E The Entity that the new component has been added to.
 * @param Component A reference to the newly added MovementComponent.
 */
void Scene::OnComponentAdded<MovementComponent>(Entity E, MovementComponent& Component)
	{

	}

	/**
 * @brief This function serializes a Scene object into a DataWriter.
 * 
 * The function writes the size of the scene name, the scene name itself, the viewport width and height, and the scene info to the provided DataWriter.
 * 
 * @param Serializer Pointer to the DataWriter where the serialized data will be written.
 * @param Data Const reference to the Scene object that is being serialized.
 */
void Scene::Serialize(DataWriter* Serializer, const Scene& Data)
	{
		Serializer->WriteRaw<size_t>(Data.m_Name.size());
		Serializer->WriteString(Data.m_Name);
		Serializer->WriteRaw<uint32_t>(Data.m_ViewportWidth);
		Serializer->WriteRaw<uint32_t>(Data.m_ViewportHeight);
		Serializer->WriteObject<SceneInfo>(Data.m_SceneInfo);
	}

	/**
 * @brief Deserialize a Scene object from a DataReader.
 * 
 * This function reads the necessary data to reconstruct a Scene object from a DataReader. The Scene object's name, viewport width and height as well as its SceneInfo are read.
 * 
 * @param Deserializer A pointer to the DataReader that provides the serialized data.
 * @param Data The Scene object to be deserialized.
 * 
 * @return void
 */
void Scene::Deserialize(DataReader* Deserializer, Scene& Data)
	{
		Deserializer->ReadString(Data.m_Name);
		Deserializer->ReadRaw<uint32_t>(Data.m_ViewportWidth);
		Deserializer->ReadRaw<uint32_t>(Data.m_ViewportHeight);
		Deserializer->ReadObject<SceneInfo>(Data.m_SceneInfo);
	}

	/**
 * @brief Serializes the SceneInfo data into a DataWriter object.
 * 
 * This function serializes various parts of the SceneInfo data structure, including the size of AssetMap and the Flags string. It also writes the raw pointer to AssetMap.
 * 
 * @param[in] Serializer The DataWriter object where the serialized data will be written into.
 * @param[in] Data The SceneInfo instance that contains the data to be serialized.
 */
void SceneInfo::Serialize(DataWriter* Serializer, const SceneInfo& Data)
	{
		Serializer->WriteRaw<size_t>(sizeof(*Data.AssetMap));
		Serializer->WriteString(Data.Flags);
		Serializer->WriteRaw<const char*>(Data.AssetMap);
	}

	/**
 * @brief Deserialize function for SceneInfo class.
 * 
 * This function reads raw data from a DataReader object and populates the provided SceneInfo object with it.
 * 
 * @param Deserializer Pointer to the DataReader object that provides the serialized data.
 * @param Data Reference to the SceneInfo object where the deserialized data will be stored.
 */
void SceneInfo::Deserialize(DataReader* Deserializer, SceneInfo& Data)
	{
		Deserializer->ReadRaw<size_t>(Data.Size);
		Deserializer->ReadString(Data.Flags);
		Deserializer->ReadRaw<const char*>(Data.AssetMap);
	}
}
