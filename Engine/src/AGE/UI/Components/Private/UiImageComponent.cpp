//
// Created by gdmgp on 12/30/2025.
//

#include "../Public/UiImageComponent.h"

#include "Render/Public/Renderer2D.h"

namespace AGE
{
	UIImageComponent::UIImageComponent(const std::string &Name)
	{
		m_Name = Name;
		std::unordered_map<UUID, Ref<Texture2D>> TextureMap = AssetManager::Get().GetAssetRegistry()->GetTextures();

		std::for_each(TextureMap.begin(), TextureMap.end(),[&](const std::pair<UUID, Ref<Texture2D>>& pair)
		{
			m_TextureNames.push_back(pair.second->GetName());
		});

		m_Image = Texture2D::Create(TextureSpecification());
	}

	void UIImageComponent::OnUpdate(TimeStep DeltaTime)
	{
		Renderer2D::DrawQuad(m_Image, m_Properties);
	}

	void UIImageComponent::OnEvent(Event &Event)
	{
	}

	void UIImageComponent::DrawContent()
	{
		//Combo Box

		//Button with drag and drop ability
		ImGui::ImageButton("##Image", (ImTextureID)m_Image->GetTextureID(), ImVec2(32.f,32.f));
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* Payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
			{
				const wchar_t* Path = (const wchar_t*)Payload->Data;
				std::filesystem::path TexturePath = Path;
				std::string FileName = TexturePath.filename().replace_extension("").string();
				if (AssetManager::Get().IsTextureLoaded(TexturePath))
				{
					m_Image = AssetManager::Get().GetTexture(FileName);
				}
				else
				{
					m_Image = AssetManager::Get().LoadTexture(TexturePath);
				}

			}
			ImGui::EndDragDropTarget();
		}

	}
} // AGE