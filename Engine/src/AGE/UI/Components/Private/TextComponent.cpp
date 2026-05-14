//
// Created by gdmgp on 12/5/2025.
//

#include "AGEpch.hpp"
#include "UI/Components/Public/TextComponent.h"
#include "Render/Public/Renderer2D.h"
#include "Core/Public/Log.h"
#include <rttr/registration>
#include <misc/cpp/imgui_stdlib.h>


namespace AGE
{
	/**
 * @brief Constructs a TextComponent with the given name and sets default properties.
 * @param Name The name of the TextComponent to be created.
 */
TextComponent::TextComponent(const std::string& Name)
	{
		m_Name = Name;
		m_Type = UIComponentType::TextComponent;
		m_StringProperties.TextFont = AGEFont::GetDefault();
	}
	/**
 * @brief This function updates the text component based on a time step.
 *
 * The function checks if the component is visible and if so, it calls Renderer2D::DrawString with the string properties of the component. 
 * It's assumed that Renderer2D::DrawString takes care of rendering the string in the correct position on screen.
 *
 * @param DeltaTime The time step since the last update. This is used to calculate how much time has passed and adjust the animation accordingly.
 */
void TextComponent::OnUpdate(TimeStep DeltaTime)
	{
		if (m_CompProperties.Visible)
		{
			Renderer2D::DrawString(m_StringProperties);
		}
	}

	/**
 * @brief Handles an event of type Event.
 *
 * This function takes in a reference to an object of type Event and processes it accordingly. The exact behavior depends on the specifics of the implementation.
 *
 * @param[in] Event - Reference to the Event object that needs processing.
 */
void TextComponent::OnEvent(Event &Event)
	{
	}

	
void TextComponent::DrawFontSelectionComboBox()
	{
		std::unordered_map<UUID,Ref<AGEFont>> Fonts = AssetManager::Get().GetAssetRegistry()->GetFonts();
		std::vector<std::string> FontNames = AssetManager::Get().GetAssetRegistry()->GetFontNames();

		if (m_StringProperties.FontName.empty())
		{
			m_StringProperties.FontName = AGEFont::GetDefault()->GetFontName();
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
 * @brief Draws a TextComponent with various properties.
 * 
 * The function displays an interface for editing the text, font size, color, position, and rotation of a TextComponent. It uses ImGui functions to create input fields for these properties.
 * 
 * @return void
 */
void TextComponent::DrawContent()
	{
		ImGui::Text("String Properties");
		ImGui::Text("Text");ImGui::SameLine();
		ImGui::InputText("##Text", &m_StringProperties.Text);
		DrawFontSelectionComboBox();
		if (m_StringProperties.TextFont->GetAtlasTexture()->GetName() != m_StringProperties.FontName)
		{
			m_StringProperties.TextFont = AssetManager::Get().GetFont(m_StringProperties.FontName);
		}
		ImGui::InputDouble("Font Size", &m_StringProperties.FontSize, 1.0, 4.0);
		ImGui::ColorEdit4("Text Color", &m_StringProperties.Color.x);
		DrawVec3Control("Position", m_StringProperties.Position);
		DrawVec3Control("Rotation", m_StringProperties.Rotation);
	}

	template<>
	/**
 * @brief This function is used to cast the current object to a TextComponent type.
 * 
 * @return A pointer of type TextComponent that points to this instance of UIComponent. If the casting fails, it will return nullptr.
 */
TextComponent* UIComponent::As()
	{
		return (TextComponent*)this;
	}
} // AGE

RTTR_REGISTRATION
{
	rttr::registration::class_<AGE::TextComponent>("TextComponent")
	.constructor<const std::string&>()
	.method("OnUpdate", &AGE::TextComponent::OnUpdate)
	.property("Name", &AGE::TextComponent::m_Name);
}