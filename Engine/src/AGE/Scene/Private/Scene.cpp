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
	static void CopyComponent(entt::registry& dst, entt::registry& src, const std::unordered_map<UUID, entt::entity>& enttMap)
	{
		auto View = src.view<Component>();


		for (auto E : View)
		{
			UUID uuid = src.get<IDComponent>(E).ID;

			AGE_CORE_ASSERT(enttMap.find(uuid) != enttMap.end(), "UUID not found!");
			entt::entity dstEnttID = enttMap.at(uuid);


			if (src.any_of<Component>(E))
			{
				auto& component = src.get<Component>(E);
				dst.emplace_or_replace<Component>(dstEnttID, component);
			}


		}
	}

	template<typename Component>
	static void CopyComponentIfExists(Entity dst, Entity src)
	{
		if (src.HasComponent<Component>())
		{
			dst.AddOrReplaceComponent<Component>(src.GetComponent<Component>());
		}
	}

	Scene::Scene()
	{
		m_Importer = TileMapImporter(*this);
		m_Physics = CreateRef<Physics2D>();
	}
	Scene::~Scene()
	{

	}
	Entity Scene::CreateEntity(const std::string Name)
	{
		return CreateEntityWithUUID(UUID(), Name);
	}

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
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& NSC)
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
						if (!Map.TileMap)
						{
							m_Importer.SetActiveScene(shared_from_this());
							Map.TileMap = m_Importer.ImportMap(Map.TileMapPath);
							Map.TileMapTexture = m_Importer.GetTexture();
						}

						if (Map.TileMap)
						{
							tmx_layer* CurrentLayer = Map.TileMap->ly_head;
							auto SpriteView = GetAllEntitiesWith<SpriteRendererComponent>();
							if (Map.LayerCount == -1)
							{
								Map.SetTileLocations();
								Map.LayerCount = Map.ProcessLayers(Map.TileMap->ly_head);

							}
							if (!Map.bLoaded)
							{

								for (auto E : SpriteView)
								{
									auto& Sprite = SpriteView.get<SpriteRendererComponent>(E);

									if (Sprite.bTile)
									{
										Sprite.SubTexture = Map.TileTextures[Sprite.TileID];
									}

								}
								Map.bLoaded = true;
							}
							else
							{
								Renderer2D::DrawTileMapLayers(Map, Map.TileMap, Map.Layers);
							}

							for (auto E : Reverse(SpriteView))
							{
								auto& Sprite = SpriteView.get<SpriteRendererComponent>(E);

								if (Sprite.bTile)
								{
									Sprite.QuadProps.TintColor = Sprite.Color;
									Sprite.QuadProps.EntityID = (int)E;
									Renderer2D::DrawTile(Sprite);
								}
							}

						}
					}

				}
				{
					m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& NSC)
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
						auto [Map, Audio] = View.get<TileMapRendererComponent, AudioComponent>(E);

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
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& NSC)
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
				if (!Map.TileMap)
				{
					m_Importer.SetActiveScene(shared_from_this());
					Map.TileMap = m_Importer.ImportMap(Map.TileMapPath);
					Map.TileMapTexture = m_Importer.GetTexture();
				}

				if (Map.TileMap)
				{
					tmx_layer* CurrentLayer = Map.TileMap->ly_head;
					auto SpriteView = GetAllEntitiesWith<SpriteRendererComponent>();
					if (Map.LayerCount == -1)
					{
						Map.SetTileLocations();
						Map.LayerCount = Map.ProcessLayers(Map.TileMap->ly_head);
						
					}
					if (!Map.bLoaded)
					{

						for (auto E : SpriteView)
						{
							auto& Sprite = SpriteView.get<SpriteRendererComponent>(E);
							
							if (Sprite.bTile)
							{
								Sprite.SubTexture = Map.TileTextures[Sprite.TileID];
							}

						}
						Map.bLoaded = true;
					}
					else
					{
						Renderer2D::DrawTileMapLayers(Map, Map.TileMap, Map.Layers);
					}

					for (auto E : Reverse(SpriteView))
					{
						auto& Sprite = SpriteView.get<SpriteRendererComponent>(E);

						if (Sprite.bTile)
						{
							Sprite.QuadProps.TintColor = Sprite.Color;
							Sprite.QuadProps.EntityID = (int)E;
							Renderer2D::DrawTile(Sprite);
						}
					}

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
	void Scene::DestoryEntity(Entity E)
	{
		m_Registry.destroy(E);
	}

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
	void Scene::OnComponentAdded(Entity E, T& Component)
	{
		//static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity E, TagComponent& Component)
	{

	}
	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity E, TransformComponent& Component)
	{

	}	
	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity E, CameraComponent& Component)
	{
		Component.Cam.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}	
	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity E, SpriteRendererComponent& Component)
	{

	}	
	template<>
	void Scene::OnComponentAdded<TileMapRendererComponent>(Entity E, TileMapRendererComponent& Component)
	{

	}
	template<>
	void Scene::OnComponentAdded<CircleRendererComponent>(Entity E, CircleRendererComponent& Component)
	{

	}
	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity E, NativeScriptComponent& Component)
	{

	}
	template<>
	void Scene::OnComponentAdded<BoxComponent>(Entity E, BoxComponent& Component)
	{

	}
	template<>
	void Scene::OnComponentAdded<AudioComponent>(Entity E, AudioComponent& Component)
	{

	}
	template<>
	void Scene::OnComponentAdded<RigidBody2DComponent>(Entity E, RigidBody2DComponent& Component)
	{

	}
	template<>
	void Scene::OnComponentAdded<BoxCollider2DComponent>(Entity E, BoxCollider2DComponent& Component)
	{

	}
	template<>
	void Scene::OnComponentAdded<CapsuleCollider2DComponent>(Entity E, CapsuleCollider2DComponent& Component)
	{

	}
	template<>
	void Scene::OnComponentAdded<SegmentCollider2DComponent>(Entity E, SegmentCollider2DComponent& Component)
	{

	}
	template<>
	void Scene::OnComponentAdded<IDComponent>(Entity E, IDComponent& Component)
	{

	}
	template<>
	void Scene::OnComponentAdded<MovementComponent>(Entity E, MovementComponent& Component)
	{

	}
}
