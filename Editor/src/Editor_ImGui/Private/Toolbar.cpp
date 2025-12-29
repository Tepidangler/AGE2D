#include <Core/Public/AGEpch.hpp>
#include "Editor_ImGui/Public/Toolbar.h"
#include "Editor_Core/Public/EditorLayer.h"

namespace AGE
{
	Toolbar::Toolbar()
	{
		AppConfig Config = App::Get().GetAppConfig();
		m_PlayIcon = AssetManager::Get().LoadTexture(Config.EditorAssetPath.string() + "/Resources/Icons/ContentBrowser/Play_Icon.png");
		m_StopIcon = AssetManager::Get().LoadTexture(Config.EditorAssetPath.string() + "/Resources/Icons/ContentBrowser/Stop_Icon.png");
	}
	void Toolbar::OnImGuiRender()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5, 5));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		
		auto& Colors = ImGui::GetStyle().Colors;
		const auto& ButtonHovered = Colors[ImGuiCol_ButtonHovered];
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ButtonHovered.x, ButtonHovered.y, ButtonHovered.z, .5f));
		
		const auto& ButtonActive = Colors[ImGuiCol_ButtonActive];
		
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ButtonActive.x, ButtonActive.y, ButtonActive.z, .5f));


		if (ImGui::Begin("##toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
		{
			switch (RendererAPI::GetAPI())
			{
			case 0:
			{
				break;
			}

			case 1:
			{
				float Size = ImGui::GetWindowHeight() + 4.f;
				Ref<Texture2D> Icon = m_SceneState == SceneState::Edit ? m_PlayIcon : m_StopIcon;
				//ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 5.f) - (Size * .5f));
				if (ImGui::ImageButton((ImTextureID)Icon->GetTextureID(), { 100.f, 100.f }))
				{
					if (m_SceneState == SceneState::Edit)
					{
						OnScenePlay();
					}
					else if (m_SceneState == SceneState::Play)
					{
						OnSceneStop();
					}
				}

				const char* DrawModeTypeStrings[] = { "Brush", "Rectangle" };
				const char* CurrentDrawModeTypeString = DrawModeTypeStrings[(int)m_Mode];
				if (ImGui::BeginCombo("DrawMode", CurrentDrawModeTypeString))
				{
					for (int i = 0; i < 2; i++)
					{
						bool IsSelected = CurrentDrawModeTypeString == DrawModeTypeStrings[i];

						if (ImGui::Selectable(DrawModeTypeStrings[i], IsSelected))
						{
							CurrentDrawModeTypeString = DrawModeTypeStrings[i];
							m_Mode = (TileDrawMode)i;
						}

						if (IsSelected)
						{
							ImGui::SetItemDefaultFocus();
						}
					}

					ImGui::EndCombo();
				}


				ImGui::PopStyleVar(2);
				ImGui::PopStyleColor(3);
				ImGui::End();
				break;
			}
			}
			
		}
		
		
	}
	void Toolbar::OnScenePlay()
	{
		m_SceneState = SceneState::Play;
		EditorLayer::Get().m_NodeEditorManager->RegisterFunctions();
		EditorLayer::Get().m_ActiveScene->OnRuntimeStart();
	}
	void Toolbar::OnSceneStop()
	{
		m_SceneState = SceneState::Edit;
		EditorLayer::Get().m_ActiveScene->OnRuntimeStop();
		EditorLayer::Get().m_NodeEditorManager->DeregisterFunctions();
	}

	void Toolbar::OnEvent(Event& E)
	{
		EventDispatcher Dispatcher(E);

		Dispatcher.Dispatch<RendererChangeEvent>(BIND_EVENT_FN(Toolbar::OnRendererChanged));
	}
	bool Toolbar::OnRendererChanged(RendererChangeEvent& E)
	{
		AppConfig Config = App::Get().GetAppConfig();
		m_PlayIcon.reset();
		m_StopIcon.reset();

		m_PlayIcon = Texture2D::Create(Config.EditorAssetPath.string() + "/Resources/Icons/ContentBrowser/Play_Icon.png");
		m_StopIcon = Texture2D::Create(Config.EditorAssetPath.string() + "/Resources/Icons/ContentBrowser/Stop_Icon.png");

		return false;
	}
}