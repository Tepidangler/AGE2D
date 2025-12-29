
#if !AG_DIST
#include <Core/Public/AGEpch.hpp>
#include <Age.h>
#include <Render/Public/Renderer2D.h>
#include <Texture/Public/Texture.h>
#include <Math/Public/Math.h>
#include <ImGuizmo.h>
#include <Scene/Public/Entity.h>
#include <Scene/Public/Scene.h>


#include "Viewports/Public/Viewport.h"
#include "Editor_Core/Public/EditorLayer.h"

namespace AGE
{
	Viewport::Viewport(const char* Name)
		:m_Name(Name)
	{
		AppConfig Config = App::Get().GetAppConfig();
		m_AssetPath = Config.GameContentPath;
	}

	void Viewport::OnUpdate(TimeStep DeltaTime)
	{
		auto [mx, my] = ImGui::GetMousePos();
		mx -= m_ViewportBounds[0].x;
		my -= m_ViewportBounds[0].y;

		Vector2 ViewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];

		my = ViewportSize.y - my;

		
		int MouseX = (int)mx;
		int MouseY = (int)my;

		if (MouseX >= 0 && MouseY >= 0 && MouseX < (int)ViewportSize.x && MouseY < (int)ViewportSize.y)
		{
			int PixelData = EditorLayer::Get().m_FrameBuffer->ReadPixel(1, MouseX, MouseY);
			EditorLayer::Get().m_HoveredEntity = PixelData == -1 ? Entity() : Entity((entt::entity)PixelData, EditorLayer::Get().m_ActiveScene.get());
		}

		OnOverlayRender();
	
		
	}

	void Viewport::OnImGuiRender(TimeStep DeltaTime, Ref<FrameBuffer> FrameBuffer, EditorCamera& Camera, int Index)
	{

		switch ((int)Renderer::GetAPI())
		{
		case 0:
			AGE_CORE_ASSERT(false, "None Renderer is not supported!")
				break;
		case 1:
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			if (ImGui::Begin(m_Name))
			{
				auto ViewportMinRegion = ImGui::GetWindowContentRegionMin();
				auto ViewportMaxRegion = ImGui::GetWindowContentRegionMax();
				auto ViewportOffset = ImGui::GetWindowPos();

				m_ViewportBounds[0] = { ViewportMinRegion.x + ViewportOffset.x, ViewportMinRegion.y + ViewportOffset.y };
				m_ViewportBounds[1] = { ViewportMaxRegion.x + ViewportOffset.x, ViewportMaxRegion.y + ViewportOffset.y};

				EditorLayer::Get().m_ViewportFocused = ImGui::IsWindowFocused();
				EditorLayer::Get().m_ViewportHovered = ImGui::IsWindowHovered();

				App::Get().GetImGuiLayer()->BlockEvents(!EditorLayer::Get().m_ViewportFocused && !EditorLayer::Get().m_ViewportHovered);

				Vector2 View(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);
				Vector2 SpecView((float)FrameBuffer->GetSpecification().Width, (float)FrameBuffer->GetSpecification().Height);
				if (SpecView != View && View.x > 0 && View.y > 0)
				{

					EditorLayer::Get().SetViewportSize(Vector2(View[0], View[1]));
					SpecView = View;
				}
				ImGui::Image((ImTextureID)FrameBuffer->GetColorAttachmentRendererID(Index), ImVec2(SpecView[0], SpecView[1]), ImVec2(0, 1), ImVec2(1, 0));

				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* Payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
					{
						const wchar_t* Path = (const wchar_t*)Payload->Data;
						EditorLayer::Get().m_MainMenuBar->OpenScene(std::filesystem::path(m_AssetPath) / Path);
					}
					if (const ImGuiPayload* Payload = ImGui::AcceptDragDropPayload("TILE_MAP_ITEM"))
					{
						Ref<SubTexture2D> SubTexture = CreateRef<SubTexture2D>(Payload->Data); 
						Entity E = EditorLayer::Get().m_SceneHierarchyPanel->GetContext()->CreateEntity("NewTile");
						E.AddComponent<SpriteRendererComponent>();
						E.GetComponent<SpriteRendererComponent>().SubTexture = SubTexture;
						E.AddComponent<CameraComponent>();
					}
					ImGui::EndDragDropTarget();
				}

				//Gizmos

				Entity SelectedEntity = EditorLayer::Get().m_SceneHierarchyPanel->GetSelectedEntity();

				if (SelectedEntity && m_GizmoType != -1)
				{
					ImGuizmo::SetOrthographic(false);
					ImGuizmo::SetDrawlist();

					ImGuizmo::SetRect(m_ViewportBounds[0] .x, m_ViewportBounds[0].y, m_ViewportBounds[1].x - m_ViewportBounds[0].x, m_ViewportBounds[1].y - m_ViewportBounds[0].y);


					auto CameraEntity = EditorLayer::Get().m_SceneHierarchyPanel->GetContext()->GetPrimaryCameraEntity();

					const auto& Camera = CameraEntity.GetComponent<CameraComponent>().Cam;
					const Matrix4D& CameraProjection = Camera.GetProjection();
					Matrix4D CameraView = glm::inverse(CameraEntity.GetComponent<TransformComponent>().GetTransform().ToGLM());

					auto& TC = SelectedEntity.GetComponent<TransformComponent>();
					Matrix4D Transform = TC.GetTransform();

					bool Snap = Input::IsKeyPressed(Key::LEFT_CONTROL);

					float SnapValue = .5f;

					if (m_GizmoType == ImGuizmo::OPERATION::ROTATE)
					{
						SnapValue = 45.f;
					}

					float SnapValues[3] = { SnapValue, SnapValue, SnapValue };

					ImGuizmo::Manipulate(&CameraView[0].x, &CameraProjection[0].x, (ImGuizmo::OPERATION)m_GizmoType,
						ImGuizmo::LOCAL, &Transform[0].x, nullptr,
						Snap ? SnapValues : nullptr);

					if (ImGuizmo::IsUsing())
					{
						Vector3 Translation, Rotation, Scale;

						Math::DecomposeTransform(Transform, Translation, Rotation, Scale);

						Vector3 DeltaRotation = Rotation - TC.Rotation;
						TC.Translation = Translation;
						TC.Rotation += DeltaRotation;
						TC.Scale = Scale;
					}

				} 
				ImGui::End();
				ImGui::PopStyleVar();

			}
			break;
		}
		default:
		{
			break;
		}
		}
	}

	void Viewport::OnOverlayRender()
	{
		switch (RendererAPI::GetAPI())
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			auto Scene = EditorLayer::Get().m_ActiveScene;
			if (EditorLayer::Get().m_Toolbar->GetSceneState() == SceneState::Play)
			{
				Entity Camera = Scene->GetPrimaryCameraEntity();
				Renderer2D::BeginScene(Camera.GetComponent<CameraComponent>().Cam, Camera.GetComponent<TransformComponent>().GetTransform());
			}
			else
			{
				Renderer2D::BeginScene(EditorLayer::Get().m_EditorCamera);

			}

			if (EditorLayer::Get().m_MainMenuBar->IsShowingPhysicsColliders())
			{
				//Box
				{
					auto View = Scene->GetAllEntitiesWith<TransformComponent, BoxCollider2DComponent>();

					for (auto E : View)
					{
						auto [TC, BC2D] = View.get<TransformComponent, BoxCollider2DComponent>(E);

						Vector3 Translation = TC.Translation + Vector3(BC2D.Offset, .001f);
						Vector3 Scale = TC.Scale * Vector3(BC2D.Size * 2.f, 1.f);

						Matrix4D Transform = glm::translate(glm::mat4(1.f), Convert::ToGLM(Translation)) *
							glm::rotate(glm::mat4(1.f), TC.Rotation.z, glm::vec3(0.f, 0.f, 1.f)) *
							glm::scale(glm::mat4(1.f), Convert::ToGLM(Scale));

						Renderer2D::DrawRect(Transform, Vector4(1.f, 0.f, 0.f, 1.f));
					}
				}

				//Capsule
				{
					auto View = Scene->GetAllEntitiesWith<TransformComponent, CapsuleCollider2DComponent>();

					for (auto E : View)
					{
						auto [TC, CC2D] = View.get<TransformComponent, CapsuleCollider2DComponent>(E);

						Vector3 Translation = TC.Translation + Vector3(CC2D.Offset, .001f);
						Vector3 Scale = TC.Scale * Vector3(CC2D.Radius * 2.f, 1.f);

						Matrix4D Transform = glm::translate(glm::mat4(1.f), Convert::ToGLM(Translation)) *
							glm::rotate(glm::mat4(1.f), TC.Rotation.z, glm::vec3(0.f, 0.f, 1.f)) *
							glm::scale(glm::mat4(1.f), Convert::ToGLM(Scale));

						Renderer2D::DrawCircle(Transform, Vector4(1.f, 0.f, 0.f, 1.f), .1f);
					}
				}
			}
			Renderer2D::EndScene();
			break;
		}
		}
		
	}

	void Viewport::OnEvent(Event& E)
	{
		EventDispatcher Dispatcher(E);
		Dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(Viewport::OnKeyPressed));
		Dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(Viewport::OnMouseButtonPressed));
	}


	bool Viewport::OnKeyPressed(KeyPressedEvent& E)
	{
		if (E.GetRepeatCount() > 0)
		{
			return false;
		}

		switch (E.GetKeyCode())
		{
		case Key::Q:
		{
			m_GizmoType = -1;
			break;
		}

		case Key::W:
		{
			m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
			break;
		}
		case Key::E:
		{
			m_GizmoType = ImGuizmo::OPERATION::ROTATE;
			break;
		}
		case Key::R:
		{
			m_GizmoType = ImGuizmo::OPERATION::SCALE;
			break;
		}

		}

		return false;

	}

	bool Viewport::OnMouseButtonPressed(MouseButtonPressedEvent& E)
	{
		if (E.GetMouseButton() == Mouse::Left)
		{
			if (EditorLayer::Get().m_ViewportHovered && !ImGuizmo::IsOver() && !Input::IsKeyPressed(Key::LEFT_ALT))
			{
				EditorLayer::Get().m_SceneHierarchyPanel->SetSelectedEntity(EditorLayer::Get().m_HoveredEntity);
			}
		}
		return false;
	}
}

#endif //AG_DIST