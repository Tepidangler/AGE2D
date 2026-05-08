//
// Created by gdmgp on 12/5/2025.
//

#include "AGEpch.hpp"
#include "../Public/TextBoxComponent.h"
#include "Render/Public/Renderer2D.h"
#include "rttr/registration"
#include <misc/cpp/imgui_stdlib.h>

RTTR_REGISTRATION{
	rttr::registration::class_<AGE::TextBoxComponent>("TextBoxComponent")
	.constructor<const std::string&>()
	.method("OnUpdate", &AGE::TextBoxComponent::OnUpdate)
	.property("BoxProperties", &AGE::TextBoxComponent::m_BoxProperties)(rttr::metadata("Description", "Properties related to box surrounding the text"));
}

namespace AGE
{
	/**
 * @brief Constructs a TextBoxComponent with the given name and sets default properties.
 * @param Name The name of the TextBoxComponent.
 * @return None
 */
TextBoxComponent::TextBoxComponent(const std::string &Name)
	{
		m_Name = Name;
		m_Type = UIComponentType::TextBoxComponent;
		m_StringProperties.TextFont = AGEFont::GetDefault();
	}

	/**
 * @brief Updates the TextBoxComponent based on a time step.
 * 
 * This function updates the TextBoxComponent by checking if it is visible. If it is, it sets up properties for a quad and string to be drawn. The quad's transform, color, and other properties are set according to the component's box properties. Then, it calls Renderer2D::DrawQuad with these properties and Renderer2D::DrawString with the string properties of the TextBoxComponent.
 * 
 * @param DeltaTime The time step for updating the component.
 */
void TextBoxComponent::OnUpdate(TimeStep DeltaTime)
	{
		if (m_CompProperties.Visible)
		{
			QuadProperties QuadProps;
			QuadProps.Transform = Math::MakeTransform(m_BoxProperties.Position,m_BoxProperties.Rotation,m_BoxProperties.Scale);
			QuadProps.Color = m_BoxProperties.TintColor;
			Renderer2D::DrawQuad(QuadProps);
			Renderer2D::DrawString(m_StringProperties);
		}
	}

	/**
 * @brief Handles an event of type Event.
 *
 * This function takes in a reference to an Event object and processes it according to its type. The exact behavior depends on the specific implementation of this class.
 *
 * @param[in] Event - A reference to the Event that needs to be processed.
 */
void TextBoxComponent::OnEvent(Event &Event)
	{
	}

	
void TextBoxComponent::DrawFontSelectionComboBox()
	{
		std::unordered_map<UUID,Ref<AGEFont>> Fonts = AssetManager::Get().GetAssetRegistry()->GetFonts();
		std::vector<std::string> FontNames = AssetManager::Get().GetAssetRegistry()->GetFontNames();

		if (m_StringProperties.FontName.empty())
		{
			m_StringProperties.FontName = AGEFont::GetDefault()->GetAtlasTexture()->GetName();
		}
		ImGui::Text("Fonts"); ImGui::SameLine();
		if (ImGui::BeginCombo("##Fonts",m_StringProperties.FontName.c_str()))
		{
			for (auto& F : FontNames)
			{
				bool IsSelected = F == m_StringProperties.FontName;
				if (ImGui::Selectable(F.c_str(), IsSelected))
				{
					m_StringProperties.FontName = F;
				}

				if (IsSelected)
				{
					ImGui::SetItemDefaultFocus();
				}

			}
			ImGui::EndCombo();
		}
	}

	/**
 * @brief Draws the content of the TextBoxComponent, including text properties, font selection, color editing, and positioning controls.
 * 
 * This function uses ImGui to draw a series of UI elements for configuring the text properties of the TextBoxComponent. It includes inputs for text string, font selection, color editing, and positioning controls. The function updates the m_StringProperties member variable accordingly based on user input.
 * 
 * @return void
 */
void TextBoxComponent::DrawContent()
	{
		ImGui::Text("String Properties");
		ImGui::Text("Text");ImGui::SameLine();
		ImGui::InputText("##Text", &m_StringProperties.Text);
		DrawFontSelectionComboBox();
		if (m_StringProperties.TextFont->GetAtlasTexture()->GetName() != m_StringProperties.FontName)
		{
			m_StringProperties .TextFont = AssetManager::Get().GetFont(m_StringProperties.FontName);
		}
		ImGui::ColorEdit4("Text Color", &m_StringProperties.Color.x);
		ImGui::InputDouble("Font Size", &m_StringProperties.FontSize, 1.0, 4.0);
		DrawVec3Control("Position", m_StringProperties.Position);
		DrawVec3Control("Rotation", m_StringProperties.Rotation);
		ImGui::Text("Box Properties");
		DrawVec3Control("Screen Position", m_BoxProperties.Position);
		DrawVec3Control("Screen Rotation", m_BoxProperties.Rotation);
		DrawVec3Control("Screen Scale", m_BoxProperties.Scale);
		ImGui::ColorEdit4("Box Color", &m_BoxProperties.TintColor.x);
	}

	template<>
	/**
 * @brief This function is used to cast the current object to TextBoxComponent type.
 * 
 * @return TextBoxComponent* Returns a pointer to this object, but with its type as TextBoxComponent.
 */
TextBoxComponent* UIComponent::As()
	{
		return (TextBoxComponent*)this;
	}
} // AGE