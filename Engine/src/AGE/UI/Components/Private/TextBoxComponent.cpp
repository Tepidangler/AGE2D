//
// Created by gdmgp on 12/5/2025.
//

#include "AGEpch.hpp"
#include "../Public/TextBoxComponent.h"
#include "Render/Public/Renderer2D.h"
#include <rttr/registration>
#include <misc/cpp/imgui_stdlib.h>

RTTR_REGISTRATION{
	rttr::registration::class_<AGE::TextBoxComponent>("TextBoxComponent")
	.constructor<const std::string&>()
	.method("OnUpdate", &AGE::TextBoxComponent::OnUpdate)
	.property("BoxProperties", &AGE::TextBoxComponent::m_BoxProperties)(rttr::metadata("Description", "Properties related to box surrounding the text"));
}

namespace AGE
{
	TextBoxComponent::TextBoxComponent(const std::string &Name)
	{
		m_Name = Name;
		m_Type = UIComponentType::TextBoxComponent;
		m_StringProperties.TextFont = Font::GetDefault();
	}

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

	void TextBoxComponent::OnEvent(Event &Event)
	{
	}

	void TextBoxComponent::DrawFontSelectionComboBox()
	{
		std::unordered_map<UUID,Ref<Font>> Fonts = AssetManager::Get().GetAssetRegistry()->GetFonts();
		std::vector<std::string> FontNames = AssetManager::Get().GetAssetRegistry()->GetFontNames();

		if (m_StringProperties.FontName.empty())
		{
			m_StringProperties.FontName = Font::GetDefault()->GetAtlasTexture()->GetName();
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
	TextBoxComponent* UIComponent::As()
	{
		return (TextBoxComponent*)this;
	}
} // AGE