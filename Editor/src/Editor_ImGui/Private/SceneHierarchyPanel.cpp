#include "Editor_Core/Public/EditorLayer.h"
#include <Core/Public/AGEpch.hpp>
#include <Scene/Public/Components.h>
#include <Utils/Public/WindowsUtils.h>
#include <GameFramework.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

#include "Editor_ImGui/Public/SceneHierarchyPanel.h"

#ifdef _MSVC_LANG
#define _CRT_SECURE_NO_WARNINGS
#endif

namespace AGE
{
	template<typename T, typename UIFunction>
	static void DrawComponent(const std::string& Name, Entity E, UIFunction Function)
	{
		const ImGuiTreeNodeFlags TNF = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

		bool RemoveComponent = false;
		if (E.HasComponent<T>())
		{
			auto& Component = E.GetComponent<T>();
			ImVec2 CRA = ImGui::GetContentRegionAvail();
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4.f,4.f });
			ImGui::Separator();
			float LineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.f;
			ImVec2 ButtonSize = { LineHeight,LineHeight};
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), TNF, Name.c_str());

			ImGui::SameLine(CRA.x - LineHeight * .5f);
			if (ImGui::Button("+", ButtonSize))
			{
				ImGui::OpenPopup("Component Settings");
			}
			ImGui::PopStyleVar();
			if (ImGui::BeginPopup("Component Settings"))
			{
				if (ImGui::MenuItem("Remove Component"))
				{
					RemoveComponent = true;

				}
				ImGui::EndPopup();
			}
			if (open)
			{
				Function(Component);
				ImGui::TreePop();
			}
		}

		if (RemoveComponent)
		{
			E.RemoveComponent<T>();
		}
	}

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& Scene)
	{
		AppConfig Config = App::Get().GetAppConfig();
		SetContext(Scene);
		m_Importer = CreateRef<TileMapImporter>(Scene);
		m_AsepriteManager = CreateRef<Aseprite>();
		m_AssetPath = Config.GameContentPath;
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& Context)
	{
		m_Context = Context;
		m_SelectionContext = {};	
	}
	void SceneHierarchyPanel::OnImGuiRender()
	{
		if (ImGui::Begin("Scene Heirarchy"))
		{
			if (m_Context)
			{
				m_Context->m_Registry.view<entt::entity>().each([&](auto EntityID)
					{
						Entity entity{ EntityID, m_Context.get() };
						DrawEntityNode(entity);
					});

				//TODO: Fix this to work better. Hierarchy panel seems to always be in focus
				if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
				{
					GImGui->NavId = 0;
					m_SelectionContext = {};
				}

				if (!m_SelectionContext)
				{
					if (ImGui::BeginPopupContextWindow(0, 1))
					{
						if (ImGui::MenuItem("Create Empty Entity"))
						{
							m_Context->CreateEntity("Empty Entity");
						}

						ImGui::EndPopup();
					}
				}
			}


			ImGui::End();

			if (ImGui::Begin("Properties"))
			{
				if (m_SelectionContext)
				{
					DrawComponents(m_SelectionContext);

				}

			}
			ImGui::End();
		}
	}


	tmx_map* SceneHierarchyPanel::SelectTileMap()
	{
		std::string FilePath = FileDialogs::OpenFile("TMX (*.tmx)\0*.tmx\0");
		if (!FilePath.empty())
		{
			return m_Importer->ImportMap(FilePath);
		}

		return nullptr;
	}

	Ref<AudioSource> SceneHierarchyPanel::SelectSound()
	{
		std::string FilePath = FileDialogs::OpenFile("WAV (*.wav)\0*.wav\0MP3 (*.mp3)\0*.mp3\0");
		if (!FilePath.empty())
		{
			return CreateRef<AudioSource>(FilePath);
		}
		
		return nullptr;
	}

	void SceneHierarchyPanel::OpenNodeEditor(const std::string& Name, void* Target)
	{
		EditorLayer::Get().m_NodeEditorManager->CreateContextAndWindow(Name + ".json", Name, Target);
	}

	std::filesystem::path SceneHierarchyPanel::SelectStatsFile()
	{
		std::filesystem::path Filepath(FileDialogs::OpenFile("Comma Separated Value(*.csv)\0 * .csv\0(*.xls)\0 * .xls\0"));
		return Filepath;
	}

	std::filesystem::path SceneHierarchyPanel::SelectSoundBank()
	{
		std::filesystem::path Filepath(FileDialogs::OpenFile("SoundBank(*.bank)\0 * .bank\0"));
		return Filepath;
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity E)
	{
		auto& Tag = E.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == E) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
		bool Opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)E, flags, Tag.c_str());
		if (ImGui::IsItemClicked() || ImGui::IsItemFocused())
		{
			m_SelectionContext = E;
		}

		bool EntityDeleted = false;

		if (m_SelectionContext)
		{
			if (ImGui::BeginPopupContextItem())
			{
				if (ImGui::MenuItem("Delete Entity"))
				{
					EntityDeleted = true;
				}

				ImGui::EndPopup();
			}
		}

		if (Opened)
		{
			bool Opened = ImGui::TreeNodeEx((void*)9817239, flags, Tag.c_str());
			if (Opened)
			{
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}

		if (EntityDeleted)
		{
			m_Context->DestoryEntity(E);
			if (m_SelectionContext == E)
			{
				m_SelectionContext = {};
			}
		}
	}

	void SceneHierarchyPanel::DrawCharacterComponent(ScriptableEntity* E)
	{
		GameFramework::Character* Char = static_cast<GameFramework::Character*>(E);

		if (ImGui::Button("Open Visual Scripting Window"))
		{
			OpenNodeEditor(Char->GetEntity().GetName(), Char);
		}
	}

	void SceneHierarchyPanel::LoadAsepriteFile(const std::filesystem::path&  FilePath)
	{
		m_AsepriteManager->ReadData(FilePath);
	}

	std::string SceneHierarchyPanel::GetFileName(const std::filesystem::path& FilePath)
	{
		std::string base = FilePath.string().substr(FilePath.string().find_last_of("/\\") + 1);
		std::string::size_type const p(base.find_last_of('.'));
		std::string filename = base.substr(0, p);

		if (!filename.empty())
		{
			return filename;
		}

		return std::string();
	}

	static void DrawVec3Control(const std::string Label, Vector3& Values, float ResetValue = 0.f, float ColumnWidth = 100.f)
	{
		ImGuiIO& io = ImGui::GetIO();

		auto BoldFont = io.Fonts->Fonts[0];
		ImGui::PushID(Label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, ColumnWidth);
		ImGui::Text(Label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		float LineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.f;
		ImVec2 ButtonSize = { LineHeight + 3.f,LineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.8f, .1f, .15f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.9f, .2f, .2f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(.8f, .1f, .15f, 1.f));
		ImGui::PushFont(BoldFont);
		if (ImGui::Button("X", ButtonSize))
			Values.x = ResetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &Values.x, .1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.2f, .7f, .2f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.3f, .8f, .3f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(.2f, .7f, .2f, 1.f));
		ImGui::PushFont(BoldFont);
		if (ImGui::Button("Y", ButtonSize))
			Values.y = ResetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &Values.y, .1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.1f, .25f, .8f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.2f, .35f, .9f, 1.f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(.1f, .25f, .8f, 1.f));
		ImGui::PushFont(BoldFont);
		if (ImGui::Button("Z", ButtonSize))
			Values.z = ResetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &Values.z, .1f, 0.f, 0.f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();


	}

	void SceneHierarchyPanel::DrawComponents(Entity E)
	{

		DrawComponent<TagComponent>("Tag", m_SelectionContext, [&](auto& Component)
			{
				char Buffer[256];
				memset(Buffer, 0, sizeof(Buffer));
				strcpy_s(Buffer, sizeof(Buffer), Component.Tag.c_str());
				if (ImGui::InputText("##Tag", Buffer, sizeof(Buffer)))
				{
					Component.Tag = std::string(Buffer);
				}
			});

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		if (ImGui::Button("Add Component"))
		{
			ImGui::OpenPopup("Add Component");
		}

		if (ImGui::BeginPopup("Add Component"))
		{
			if (ImGui::MenuItem("Camera"))
			{
				if (!m_SelectionContext.HasComponent<CameraComponent>())
				{
					m_SelectionContext.AddComponent<CameraComponent>();
				}
				else
				{
					CoreLogger::Warn("This Entity Already Has a CameraComponent");
				}
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Sprite Renderer"))
			{
				if (!m_SelectionContext.HasComponent<SpriteRendererComponent>())
				{
					m_SelectionContext.AddComponent<SpriteRendererComponent>();
				}
				else
				{
					CoreLogger::Warn("This Entity Already Has a SpriteRendererComponent");
				}
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("TileMap Renderer"))
			{
				if (!m_SelectionContext.HasComponent<TileMapRendererComponent>())
				{
					m_SelectionContext.AddComponent<TileMapRendererComponent>();
				}
				else
				{
					CoreLogger::Warn("This Entity Already Has a LevelRendererComponent");
				}
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Circle Renderer"))
			{
				if (!m_SelectionContext.HasComponent<CircleRendererComponent>())
				{
					m_SelectionContext.AddComponent<CircleRendererComponent>();
				}
				else
				{
					CoreLogger::Warn("This Entity Already Has a CircleRendererComponent");
				}
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("RigidBody 2D"))
			{
				if (!m_SelectionContext.HasComponent<RigidBody2DComponent>())
				{
					m_SelectionContext.AddComponent<RigidBody2DComponent>();
				}
				else
				{
					CoreLogger::Warn("This Entity Already Has a RigidBody2DComponent");
				}
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Box Collider"))
			{
				if (!m_SelectionContext.HasComponent<BoxCollider2DComponent>())
				{
					m_SelectionContext.AddComponent<BoxCollider2DComponent>();
				}
				else
				{
					CoreLogger::Warn("This Entity Already Has a BoxCollider2DComponent");
				}
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Capsule Collider"))
			{
				if (!m_SelectionContext.HasComponent<CapsuleCollider2DComponent>())
				{
					m_SelectionContext.AddComponent<CapsuleCollider2DComponent>();
				}
				else
				{
					CoreLogger::Warn("This Entity Already Has a CapsuleCollider2DComponent");
				}
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Segment Collider"))
			{
				if (!m_SelectionContext.HasComponent<SegmentCollider2DComponent>())
				{
					m_SelectionContext.AddComponent<SegmentCollider2DComponent>();
				}
				else
				{
					CoreLogger::Warn("This Entity Already Has a SegmentCollider2DComponent");
				}
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Audio Component"))
			{
				if (!E.HasComponent<AudioComponent>())
				{
					m_SelectionContext.AddComponent<AudioComponent>(App::Get().GetDeviceManager().GetAudioManager().GetAudioEngine());
				}
				else
				{
					CoreLogger::Warn("This Entity Already Has a AudioComponent");
				}
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::BeginMenu("Scriptable Component"))
			{
				if (ImGui::MenuItem("CameraController"))
				{
					m_SelectionContext.AddComponent<NativeScriptComponent>().Bind<GameFramework::CameraController>();

				}
				if (ImGui::MenuItem("PlayerController"))
				{
					m_SelectionContext.AddComponent<NativeScriptComponent>().Bind<GameFramework::PlayerController>();
				}
				if (ImGui::MenuItem("AudioController"))
				{
					m_SelectionContext.AddComponent<NativeScriptComponent>().Bind<GameFramework::AudioController>();
				}
				if (ImGui::MenuItem("CharacterComponent"))
				{
					m_SelectionContext.AddComponent<NativeScriptComponent>().Bind<GameFramework::Character>();
				}

				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();

		DrawComponent<TransformComponent>("Transform", m_SelectionContext, [&](auto& Component)
			{
				DrawVec3Control("Translation", Component.Translation);
				AGE::Vector3 Rotation = Math::Degrees(Component.Rotation);
				DrawVec3Control("Rotation", Rotation);
				Component.Rotation = Math::Radians(Rotation);
				DrawVec3Control("Scale", Component.Scale, 1.f);
			});
		DrawComponent<SpriteRendererComponent>("Sprite Renderer", m_SelectionContext, [&](auto& Component)
			{
				auto& Color = Component.Color;
				ImGui::ColorEdit4("Color", &Color.x);

				if (Component.bTile)
				{
					ImGui::Text("Tile ID: %d", Component.TileID);
				}

				ImGui::Text("Movement Status "); ImGui::SameLine();
				const char* AnimationTypeString[7] = { "Idle", "Walking", "Running", "BattleIdle", "BattleAttack",  "BattleCast", "Undefined" };
				const char* CurrentAnimationTypeString = AnimationTypeString[(int)Component.MovementStatus];
				if (ImGui::BeginCombo("##MovementStatus", CurrentAnimationTypeString))
				{
					for (int i = 0; i < 7; i++)
					{
						bool IsSelected = CurrentAnimationTypeString == AnimationTypeString[i];

						if (ImGui::Selectable(AnimationTypeString[i], IsSelected))
						{
							CurrentAnimationTypeString = AnimationTypeString[i];
							Component.MovementStatus = ((CharMovementStatus)i);
						}

						if (IsSelected)
						{
							ImGui::SetItemDefaultFocus();
						}

					}
					ImGui::EndCombo();
				}
				ImGui::Text("Aseprite Name: %s", Component.AsepriteName.c_str());
				ImGui::Button("Texture", ImVec2(100.f, 0.f));
				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* Payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
					{
						const wchar_t* Path = (const wchar_t*)Payload->Data;
						std::filesystem::path TexturePath = std::filesystem::path(m_AssetPath) / Path;
						Component.Texture = AssetManager::Get().LoadTexture(TexturePath);
						
					}
					ImGui::EndDragDropTarget();
				}
				ImGui::Button("Aseprite File");
				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* Payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
					{
						const wchar_t* Path = (const wchar_t*)Payload->Data;
						std::filesystem::path AsepriteFilePath = std::filesystem::path(m_AssetPath) / Path;
						Component.AsepriteFile = AsepriteFilePath;
						LoadAsepriteFile(AsepriteFilePath);
						Component.AsepriteName = GetFileName(AsepriteFilePath);
						Component.Texture = m_AsepriteManager->CreateImage(Component.AsepriteName, true, true);
					}
					ImGui::EndDragDropTarget();
				}

				ImGui::Button("Add Animation");
				if(ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* Payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
					{
						const wchar_t* Path = (const wchar_t*)Payload->Data;
						std::filesystem::path AnimationTexture = std::filesystem::path(m_AssetPath) / Path;
						AnimationSpecification Spec;
						Spec.Texture = Texture2D::Create(AnimationTexture.string());
						Spec.Width = (float)Spec.Texture->GetWidth();
						Spec.Height = (float)Spec.Texture->GetHeight();
						Component.AnimTextures.emplace_back(Spec);
					}
					ImGui::EndDragDropTarget();
				}
				int Index = 0;
				for (auto& S : Component.AnimTextures)
				{
						std::string IndexString = std::to_string(Index);
						ImGui::Text("Animation Name"); ImGui::SameLine();
						std::string NameLbl = "##AnimationNameText" + IndexString;
						ImGui::InputText(NameLbl.c_str(), &S.Name);
						ImGui::Text("Number Of Frames"); ImGui::SameLine();
						std::string FramesLbl = "##Frames" + IndexString;
						ImGui::InputInt(FramesLbl.c_str(), &S.NumberOfFrames, 1, 5);
						ImGui::Text("Texture ID: "); ImGui::SameLine();
						ImGui::Text("%d", S.Texture->GetTextureID());
						ImGui::Text("Animation Type "); ImGui::SameLine();
						const char* AnimationTypeString[7] = { "Idle", "Walking", "Running", "BattleIdle", "BattleAttack",  "BattleCast", "Undefined"};
						const char* CurrentAnimationTypeString = AnimationTypeString[(int)S.Status];
						std::string ComboLbl = "##AnimationType" + IndexString;
						if (ImGui::BeginCombo(ComboLbl.c_str(), CurrentAnimationTypeString))
						{
							for (int i = 0; i < 7; i++)
							{
								bool IsSelected = CurrentAnimationTypeString == AnimationTypeString[i];

								if (ImGui::Selectable(AnimationTypeString[i], IsSelected))
								{
									CurrentAnimationTypeString = AnimationTypeString[i];
									S.Status = ((CharMovementStatus)i);
								}

								if (IsSelected)
								{
									ImGui::SetItemDefaultFocus();
								}

							}
							ImGui::EndCombo();
						}

						if (!S.IsReadyToLoad())
						{
							if (ImGui::Button("Load Animation"))
							{
								S.SetIsReadyToLoad(true);
							}
						}

						ImGui::Separator();


						if (S.IsReadyToLoad())
						{
							Component.AnimInstance.LoadAnimation(S);
						}
						Index++;
				}											  				 
															  		
				if (!Component.AsepriteFile.empty())		  
				{
					ImGui::Text(Component.AsepriteFile.string().c_str());
				}

			});

		DrawComponent<CircleRendererComponent>("Circle Renderer", m_SelectionContext, [&](auto& Component)
			{
				auto& Color = Component.Color;
				ImGui::ColorEdit4("Color", &Color.x);
				ImGui::DragFloat("Thickness", &Component.Thickness, .025f, 0.f, 1.f);
				ImGui::DragFloat("Fade", &Component.Fade, .00025f, 0.f, 1.f);


			});

		DrawComponent<CameraComponent>("Scene Camera", m_SelectionContext, [&](auto& Component)
			{
				const char* ProjectionTypeStrings[] = { "Perspective", "Orthographic" };
				const char* CurrentProjectionTypeString = ProjectionTypeStrings[(int)Component.Cam.GetProjectionType()];

				ImGui::Checkbox("Primary", &Component.bPrimary);

				if (ImGui::BeginCombo("Projection", CurrentProjectionTypeString))
				{
					for (int i = 0; i < 2; i++)
					{
						bool IsSelected = CurrentProjectionTypeString == ProjectionTypeStrings[i];

						if (ImGui::Selectable(ProjectionTypeStrings[i], IsSelected))
						{
							CurrentProjectionTypeString = ProjectionTypeStrings[i];
							Component.Cam.SetProjectionType((ProjectionType)i);
						}

						if (IsSelected)
						{
							ImGui::SetItemDefaultFocus();
						}
					}

					ImGui::EndCombo();
				}

				if (Component.Cam.GetProjectionType() == ProjectionType::Orthographic)
				{
					float Size = Component.Cam.GetOrthographicSize();
					if (ImGui::DragFloat("Size", &Size))
					{
						Component.Cam.SetOrthographicSize(Size);
					}
					float NearClip = Component.Cam.GetOrthographicNearClip();
					if (ImGui::DragFloat("Near Clip", &NearClip))
					{
						Component.Cam.SetOrthographicNearClip(NearClip);
					}
					float FarClip = Component.Cam.GetOrthographicFarClip();
					if (ImGui::DragFloat("Far Clip", &FarClip))
					{
						Component.Cam.SetOrthographicFarClip(FarClip);
					}
				}
				else
				{
					float FOV = Math::Degrees(Component.Cam.GetPerspectiveVerticalFOV());
					if (ImGui::DragFloat("Vertical FOV", &FOV))
					{

						Component.Cam.SetPerspectiveVerticalFOV(Math::Radians(FOV));
					}
					float NearClip = Component.Cam.GetPerspectiveNearClip();
					if (ImGui::DragFloat("Near Clip", &NearClip))
					{
						Component.Cam.SetPerspectiveNearClip(NearClip);
					}
					float FarClip = Component.Cam.GetPerspectiveFarClip();
					if (ImGui::DragFloat("Far Clip", &FarClip))
					{
						Component.Cam.SetPerspectiveFarClip(FarClip);
					}

				}

				
			});

		DrawComponent<TileMapRendererComponent>("Tile Map", m_SelectionContext, [&](auto& Component)
			{
				auto& TileMap = Component.TileMap;
				if (!Component.bLoaded)
				{

				}

				if (ImGui::BeginMenu("Import Tilemap"))
				{
					if (ImGui::MenuItem("Add Tilemap"))
					{
						TileMap = SelectTileMap();
						if (TileMap)
						{
							Component.ActiveScene = m_Context;
							Component.TileMapPath = m_Importer->GetTileSetPath();
							Component.TileMapTexture = m_Importer->GetTexture();
						}
					}
					ImGui::EndMenu();
				}
			});

		DrawComponent<AudioComponent>("Audio Component", m_SelectionContext, [&](auto& Component)
			{

				switch (App::Get().GetDeviceManager().GetAudioManager().GetAudioEngineType())
				{
				case 0:
				{
					if (ImGui::BeginCombo("Sound", std::to_string(Component.Sounds.size()).c_str()))
					{
						for (int i = 0; i < Component.Sounds.size(); i++)
						{
							bool IsSelected = false;

							if (ImGui::Selectable(std::to_string(i).c_str(), IsSelected))
							{
							}

							if (IsSelected)
							{
								ImGui::SetItemDefaultFocus();
							}
						}

						ImGui::EndCombo();
					}

					if (ImGui::BeginMenu("Import Sound"))
					{
						if (ImGui::MenuItem("Add Sound"))
						{
							Component.AddSound(SelectSound());
						}
						ImGui::EndMenu();
					}
					break;
				}
				case 1:
				{
					break;
				}
				case 2:
				{
					if (ImGui::Button("Load SoundBanks"))
					{
						Component.GetAudioEngine()->As<FmodEngine>()->LoadBankFromFile(SelectSoundBank().string());
					}
					ImGui::Text("LoadedBanks");
					ImGui::Separator();
					if (ImGui::BeginTable("Banks", 1))
					{
						for (const auto& [K, V]: Component.GetAudioEngine()->As<FmodEngine>()->GetBanks())
						{
							ImGui::TableNextColumn();
							ImGui::Text(K.c_str());
						}
						ImGui::EndTable();
					}
					break;
				}
				default:
				{
					break;
				}
				}

			});
			
		DrawComponent<RigidBody2DComponent>("RigidBody 2D Component", m_SelectionContext, [&](auto& Component)
			{
				ImGui::Checkbox("Simulate Physics", &Component.bSimulatePhysics);

				const char* BodyTypeStrings[] = { "Static", "Dynamic", "Kinematic"};
				const char* CurrentBodyTypeString = BodyTypeStrings[(int)Component.GetBodyType()];

				if (ImGui::BeginCombo("Body Type", CurrentBodyTypeString))
				{
					for (int i = 0; i < 3; i++)
					{
						bool IsSelected = CurrentBodyTypeString == BodyTypeStrings[i];

						if (ImGui::Selectable(BodyTypeStrings[i], IsSelected))
						{
							CurrentBodyTypeString = BodyTypeStrings[i];
							Component.SetBodyType((BodyType)i);
						}

						if (IsSelected)
						{
							ImGui::SetItemDefaultFocus();
						}
					}

					ImGui::EndCombo();
				}

				ImGui::Checkbox("Interactable", &Component.bInteractable);
			});
		DrawComponent<BoxCollider2DComponent>("Box Collider 2D Component", m_SelectionContext, [&](auto& Component)
			{

				ImGui::DragFloat2("Offset", &Component.Offset.x);
				ImGui::DragFloat2("Size", &Component.Size.x);

				ImGui::DragFloat("Density", &Component.Density, 0.01f, 0.f, 1.f);
				ImGui::DragFloat("Friction", &Component.Friction, 0.01f, 0.f, 1.f);
				ImGui::DragFloat("Restitution", &Component.Restitution, 0.01f, 0.f, 1.f);
			});

		DrawComponent<CapsuleCollider2DComponent>("Capsule Collider 2D Component", m_SelectionContext, [&](auto& Component)
			{

				ImGui::DragFloat2("Offset", &Component.Offset.x);
				ImGui::DragFloat("Radius", &Component.Radius);

				ImGui::DragFloat("Density", &Component.Density, 0.01f, 0.f, 1.f);
				ImGui::DragFloat("Friction", &Component.Friction, 0.01f, 0.f, 1.f);
				ImGui::DragFloat("Restitution", &Component.Restitution, 0.01f, 0.f, 1.f);
				ImGui::Checkbox("Generate Physics Events", &Component.bGeneratePhysicsEvents); // TODO: Grey this out while running since it probably won't be updated in the run time;
			});

		DrawComponent<SegmentCollider2DComponent>("Segment Collider 2D Component", m_SelectionContext, [&](auto& Component)
			{

				ImGui::DragFloat2("Offset", &Component.Offset.x);
				ImGui::DragFloat2("Size", &Component.Size.x);

				ImGui::DragFloat("Density", &Component.Density, 0.01f, 0.f, 1.f);
				ImGui::DragFloat("Friction", &Component.Friction, 0.01f, 0.f, 1.f);
				ImGui::DragFloat("Restitution", &Component.Restitution, 0.01f, 0.f, 1.f);
			});

		DrawComponent<MovementComponent>("Movement Component", m_SelectionContext, [&](auto& Component)
			{
				ImGui::DragFloat("Speed", &Component.Speed);
			});

		DrawComponent<NativeScriptComponent>("Scriptable Component", m_SelectionContext, [&](auto& Component)
			{

				if (Component.Instance)
				{
					if (Component.Instance->IsCharacter())
					{
						DrawCharacterComponent(Component.Instance);
					}
				}
				
			
			});	
		
	}

}

	