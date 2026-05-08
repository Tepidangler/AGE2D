//
// Created by gdmgp on 12/30/2025.
//

#include "../Public/UiImageComponent.h"

#include "Render/Public/Renderer2D.h"

RTTR_REGISTRATION{
	rttr::registration::class_<AGE::UIImageComponent>("ImageComponent")
	.constructor<const std::string&>()
	.method("OnUpdate", &AGE::UIImageComponent::OnUpdate)
	.property("Image", &AGE::UIImageComponent::m_Image)(rttr::metadata("Description", "Properties related to box surrounding the text"));
}
namespace AGE
{
	/**
 * @brief Constructs an instance of UIImageComponent with the given name and initializes it.
 * 
 * This constructor creates a new UIImageComponent with the provided name, sets its type to ImageComponent,
 * retrieves all textures from the AssetManager's asset registry, stores their names in m_TextureNames,
 * and finally creates an instance of Texture2D using default parameters.
 * 
 * @param Name The name for this UIImageComponent.
 */
UIImageComponent::UIImageComponent(const std::string &Name)
	{
		m_Name = Name;
		m_Type = UIComponentType::ImageComponent;
		std::unordered_map<UUID, Ref<Texture2D>> TextureMap = AssetManager::Get().GetAssetRegistry()->GetTextures();

		std::for_each(TextureMap.begin(), TextureMap.end(),[&](const std::pair<UUID, Ref<Texture2D>>& pair)
		{
			m_TextureNames.push_back(pair.second->GetName());
		});

		m_Image = Texture2D::Create(TextureSpecification());
	}

	/**
 * @brief This function updates the image component.
 * 
 * The function takes a TimeStep parameter representing the time elapsed since the last frame. It uses this value to update the image and its properties.
 * 
 * @param DeltaTime - A TimeStep object representing the time elapsed since the last frame.
 * 
 * @return void
 */
void UIImageComponent::OnUpdate(TimeStep DeltaTime)
	{
		Renderer2D::DrawQuad(m_Image, m_Properties);
	}

	/**
 * @brief Handles an event of type Event.
 *
 * This function is responsible for handling events dispatched by the system. It takes in a reference to an Event object and processes it accordingly. 
 * The exact behavior depends on the specifics of the Event subclass that is being handled.
 *
 * @param[in] Event - A reference to the event to be processed.
 */
void UIImageComponent::OnEvent(Event &Event)
	{
	}

	
void UIImageComponent::DrawContent()
	{
		//Combo Box

		//Button with drag and drop ability
		uint32_t TextureID = m_Image->GetTextureID();
		ImGui::ImageButton("##Image", (ImTextureID)&TextureID, ImVec2(32.f,32.f));
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