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
COMMENT:
/**
 * @brief Constructs a TextComponent with the given name and sets default properties.
 * @param Name The name of the TextComponent to be created.
 */
CONFIDENCE: 1.0;

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
/**
 * @brief This function updates the text component based on a time step.
 * 
 * The function checks if the component is visible and then calls Renderer2D's DrawString method with m_StringProperties as an argument.
 * If the component is not visible, no action will be taken.
 * 
 * @param DeltaTime The time step for updating the component.
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
/**
 * @brief Handles an event of type Event.
 *
 * This function takes in a reference to an Event object and processes it accordingly. The exact behavior depends on the specifics of the Event subclass that is being processed.
 *
 * @param[in] Event - Reference to the Event object to be handled.
 */
void TextComponent::OnEvent(Event &Event)
	{
	}

	
/**
 * @brief Draws a combo box for selecting the font.
 * 
 * This function populates a ComboBox with all available fonts from the AssetManager. The currently selected font is stored in m_StringProperties.FontName, which is updated whenever a new font is selected. If no font is currently selected (i.e., m_StringProperties.FontName is empty), the default font is used as the initial selection.
 * 
 * @return void
 */
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
/**
 * @brief Draws the content of a TextComponent, including text input fields for properties like Font Name, Font Size and Color, as well as position and rotation controls.
 * 
 * The function first displays "String Properties" using ImGui::Text(). Then it creates an input field for "Text", uses ImGui::InputText() to handle user input. It also includes a combo box for font selection with DrawFontSelectionComboBox(). If the selected font's atlas texture name does not match m_StringProperties.FontName, it updates m_StringProperties.TextFont accordingly using AssetManager::Get().GetFont(m_StringProperties.FontName). It then creates an input field for "Font Size" and a color picker for "Text Color", both handled by ImGui functions respectively. Finally, it draws position and rotation controls with DrawVec3Control() function.
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
/**
 * @brief This function is used to cast the current object to a TextComponent type.
 * 
 * @return A pointer of type TextComponent that points to this object. If the casting fails, it will return nullptr.
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