//
// Created by gdmgp on 12/3/2025.
//

#include "AGEpch.hpp"
#include "UI/Public/UiComponent.h"

#include "UI/Components/Public/ButtonComponent.h"
#include "UI/Components/Public/HorizontalBoxComponent.h"
#include "UI/Components/Public/TextComponent.h"
#include "UI/Components/Public/TextBoxComponent.h"
#include "UI/Components/Public/UiImageComponent.h"
#include "UI/Components/Public/VerticalBoxComponent.h"

namespace AGE
{
	Ref<UIComponent> UIComponent::Create(const std::string &Name, UIComponentType Type)
	{
		// For the record I don't like this, and I don't know what else to do. Also, I'm tired of being stuck on this
		switch (Type)
		{
			case UIComponentType::TextComponent:
			{
				return CreateRef<TextComponent>(Name);
				break;
			}
			case UIComponentType::TextBoxComponent:
			{
				return CreateRef<TextBoxComponent>(Name);
				break;
			}
			case UIComponentType::HorizontalBoxComponent: {
				return CreateRef<HorizontalBoxComponent>(Name);
				break;
			}
			case UIComponentType::VerticalBoxComponent: {
				return CreateRef<VerticalBoxComponent>(Name);
				break;
			}
			case UIComponentType::ButtonComponent: {
				return CreateRef<ButtonComponent>(Name);
				break;
			}
			case UIComponentType::ImageComponent: {
				return CreateRef<UIImageComponent>(Name);
				break;
			}
			default:
			{
				AGE_CORE_ASSERT(false, "Unsupported UIComponent Type");
				return nullptr;
			}
		}

		return nullptr;
	}

	void UIComponent::DrawVec3Control(const std::string& Label, Vector3 &Values, float ResetValue, float ColumnWidth)
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

	//Semi-Dummy Constructor that needs to be here so this class can become visible to RTTR
	UIComponent::UIComponent(const std::string& Name)
	{
		m_Name = Name;
	}

	void UIComponent::OnEvent(Event &Event)
	{
		AGE::EventDispatcher Dispatcher(Event);
	}
} // AGE

RTTR_REGISTRATION
{
	rttr::registration::class_<AGE::UIProperties>("UIProperties")
	.property("Position", &AGE::UIProperties::Position)(rttr::metadata("Description", "Widget Property Position"))
	.property("Rotation", &AGE::UIProperties::Rotation)(rttr::metadata("Description", "Widget Property Rotation"))
	.property("Scale", &AGE::UIProperties::Scale)(rttr::metadata("Description", "Widget Property Scale"))
	.property("Visible", &AGE::UIProperties::Visible)(rttr::metadata("Description", "Widget Property Visible"));

	rttr::registration::class_<AGE::UIComponent>("UIComponent")
	.method("OnUpdate", &AGE::UIComponent::OnUpdate)
	.property("Name", &AGE::UIComponent::m_Name)
	.property("Properties", &AGE::UIComponent::m_CompProperties);

	rttr::registration::enumeration<AGE::UIComponentType::Value>("UIComponentType")
	(
		rttr::value("TextComponent", AGE::UIComponentType::Value::TextComponent),
		rttr::value("TextBoxComponent", AGE::UIComponentType::Value::TextBoxComponent),
		rttr::value("HorizontalBoxComponent", AGE::UIComponentType::Value::HorizontalBoxComponent),
		rttr::value("VerticalBoxComponent", AGE::UIComponentType::Value::VerticalBoxComponent),
		rttr::value("ButtonComponent", AGE::UIComponentType::Value::ButtonComponent),
		rttr::value("ImageComponent", AGE::UIComponentType::Value::ImageComponent)
	);
}