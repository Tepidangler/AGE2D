//
// Created by gdmgp on 12/3/2025.
//

#include "AGEpch.hpp"
#include "Core/Public/Log.h"
#include "UI/Public/UiComponent.h"

#include "UI/Components/Public/ButtonComponent.h"
#include "UI/Components/Public/HorizontalBoxComponent.h"
#include "UI/Components/Public/TextComponent.h"
#include "UI/Components/Public/TextBoxComponent.h"
#include "UI/Components/Public/UiImageComponent.h"
#include "UI/Components/Public/VerticalBoxComponent.h"

namespace AGE
{
	/**
 * @brief Creates a new instance of a UI component based on the provided type.
 * 
 * This function creates and returns a reference to a newly created UIComponent, which can be one of several types such as TextComponent, TextBoxComponent, HorizontalBoxComponent, VerticalBoxComponent, ButtonComponent or ImageComponent. The specific type is determined by the 'Type' parameter. If an unsupported type is provided, it asserts false and returns nullptr.
 * 
 * @param Name The name of the UI component to be created.
 * @param Type The type of the UI component to be created. This can be one of the following: TextComponent, TextBoxComponent, HorizontalBoxComponent, VerticalBoxComponent, ButtonComponent or ImageComponent.
 * 
 * @return A reference to a newly created UIComponent instance. If an unsupported 'Type' is provided, it returns nullptr.
 */
/**
 * @brief Creates a new instance of a UI component based on the provided type.
 * 
 * This function creates and returns a reference to a newly created UIComponent, which can be one of several types such as TextComponent, TextBoxComponent, HorizontalBoxComponent, VerticalBoxComponent, ButtonComponent or ImageComponent. The specific type is determined by the 'Type' parameter. If an unsupported type is provided, it asserts false and returns nullptr.
 * 
 * @param Name The name of the UI component to be created.
 * @param Type The type of the UI component to be created. This can be one of the following: TextComponent, TextBoxComponent, HorizontalBoxComponent, VerticalBoxComponent, ButtonComponent or ImageComponent.
 * 
 * @return A reference to a newly created UIComponent instance. If an unsupported 'Type' is provided, it returns nullptr.
 */
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
				CoreLogger::Assert(false, "Unsupported UIComponent Type");
				return nullptr;
			}
		}

		return nullptr;
	}

	/**
 * @brief Draws a Vector3 control with draggable sliders.
 * 
 * This function creates an ImGui UI component that allows the user to modify three float values (x, y, z) through draggable sliders. The labels and initial values are provided as parameters.
 * 
 * @param Label A string label for this control.
 * @param Values A reference to a Vector3 object representing the current x, y, and z values. This function will modify these values when the user interacts with the sliders.
 * @param ResetValue The value to reset each individual component of the vector to when the corresponding button is clicked.
 * @param ColumnWidth The width of the column in which this control should be displayed.
 */
/**
 * @brief Draws a 3D vector control with draggable sliders for X, Y and Z values.
 * 
 * This function is used to create an ImGui UI component that allows the user to manipulate three-dimensional vectors (X, Y, Z). The labels, initial vector values, reset value, and column width are all parameters of this function.
 * 
 * @param Label A string representing the label for the control.
 * @param Values A reference to a Vector3 object that holds the current X, Y, and Z values.
 * @param ResetValue The value to which each component (X, Y, Z) of the vector will be reset when its corresponding button is clicked.
 * @param ColumnWidth The width of the column in which the control will be displayed.
 * 
 * @return void
 */
void UIComponent::DrawVec3Control(const std::string& Label, Vector3 &Values, float ResetValue, float ColumnWidth)
	{
		ImGuiIO& io = ImGui::GetIO();

		auto BoldFont = io.Fonts->Fonts[0];
		ImGui::PushID(Label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, ColumnWidth);
		ImGui::Text("%s", Label.c_str());
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
	/**
 * @brief Constructs a UIComponent with the given name.
 * @param Name The name of the component.
 */
/**
 * @brief Constructs a UIComponent with the given name.
 * @param Name The name of the component.
 */
UIComponent::UIComponent(const std::string& Name)
	{
		m_Name = Name;
	}

	/**
 * @brief Handles an event by dispatching it to the appropriate handler.
 *
 * This function takes in an Event object and dispatches it to the appropriate 
 * handler based on its type. The EventDispatcher class is used for this purpose.
 *
 * @param[in] Event - Reference to the Event object that needs to be handled.
 */
/**
 * @brief This function is used to handle events in the UIComponent class.
 * 
 * @param Event The event object that needs to be handled by the UIComponent.
 */
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