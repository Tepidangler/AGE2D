//
// Created by gdmgp on 12/8/2025.
//

#include "../Public/UiEditorWindow.h"
#include "Core/Public/Colors.h"
#include "Editor_ImGui/Public/Dockspace.h"
#include <rttr/type>

namespace AGE
{
	void UIEditorWindow::DrawProperties(Ref<UIComponent> Comp)
	{
		UIProperties& Props = Comp->GetProperties();

		ImGui::Separator();
		UIComponent::DrawVec3Control("Position", Props.Position);
		UIComponent::DrawVec3Control("Rotation", Props.Rotation);
		UIComponent::DrawVec3Control("Scale", Props.Scale);
		ImGui::Checkbox("Is Visible", &Props.Visible);
	}

	void UIEditorWindow::DrawContent(Ref<UIComponent> Comp)
	{
		Comp->DrawContent();
	}

	void UIEditorWindow::DrawMenuBar()
	{
		if (!ImGui::BeginMenuBar())
		{
			ImGui::EndMenuBar();
			return;
		}

		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open Widget"))
			{

			}
			if (ImGui::MenuItem("Save Widget"))
			{

			}
			ImGui::EndMenu();
		}


		ImGui::EndMenuBar();
	}


	UIEditorWindow::UIEditorWindow()
	{
		FrameBufferSpecification FbSpec{};
		FbSpec.Attachments = {FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::DEPTH24STENCIL8};
		FbSpec.Width = 1280;
		FbSpec.Height = 720;

		m_UIFrameBuffer = FrameBuffer::Create(FbSpec);
		m_ClearColor ={Colors::Color::Aquamarine[0],Colors::Color::Aquamarine[1],Colors::Color::Aquamarine[2],Colors::Color::Aquamarine[3]};
		m_EditorCamera = EditorCamera(30.f,1.778f,.1f,1000.f);
		m_EditorCamera.SetProjectionType(ProjectionType::Perspective);
		m_EditorCamera.SetViewportSize(1280.f,720.f);
		//UIComponent* Comp = new UIComponent("Name");

		//Comp->m_Name = "Name";

	}

	UIEditorWindow::~UIEditorWindow()
	{
	}

	void UIEditorWindow::OnUpdate(TimeStep DeltaTime, EditorCamera& Camera)
	{
		m_UIFrameBuffer->Bind();

		RenderCommand::SetClearColor(m_ClearColor);
		RenderCommand::SetViewport(0, 0, m_UIFrameBuffer->GetSpecification().Width, m_UIFrameBuffer->GetSpecification().Height);
		RenderCommand::Clear();
		m_UIFrameBuffer->ClearAttachment(1,-1);
		m_EditorCamera.OnUpdate(DeltaTime);
		Renderer2D::BeginScene(m_EditorCamera);
		for (auto U : m_UIComponents)
		{
			U->OnUpdate(DeltaTime);
		}
		Renderer2D::EndScene();
		m_UIFrameBuffer->Unbind();
	}

	void UIEditorWindow::OnImGuiRender()
	{

		if (!ImGui::Begin("Widget Editor", &m_Opened, ImGuiWindowFlags_MenuBar))
		{
			ImGui::End();
			return;
		}
		DrawMenuBar();
		static float WidgetPaneWidth = 256.f;
		static float ViewportPaneWidth = 400.f;
		Splitter(true, 2.f, &WidgetPaneWidth, &ViewportPaneWidth, 50.f, 50.f);
		RenderWidgetsPane(WidgetPaneWidth - 4.f);
		ImGui::SameLine(0.f, 12.f);
		if (m_ImGuiWindowID != ImGui::GetID("Widget Editor"))
		{
			m_ImGuiWindowID = ImGui::GetID("Widget Editor");
		}
		auto& io = ImGui::GetIO();

		auto ViewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto ViewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto ViewportOffset = ImGui::GetWindowPos();

		m_ViewportBounds[0] = { ViewportMinRegion.x + ViewportOffset.x, ViewportMinRegion.y + ViewportOffset.y };
		m_ViewportBounds[1] = { ViewportMaxRegion.x + ViewportOffset.x, ViewportMaxRegion.y + ViewportOffset.y};

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();

		//App::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);

		Vector2 View(ImGui::GetContentRegionAvail().x - 400.f, ImGui::GetContentRegionAvail().y);
		Vector2 SpecView((float)m_UIFrameBuffer->GetSpecification().Width, (float)m_UIFrameBuffer->GetSpecification().Height);
		if (SpecView != View && View.x > 0 && View.y > 0)
		{
			SpecView = View;
			SetViewportSize(SpecView);

		}
		ImGui::Image((ImTextureID)m_UIFrameBuffer->GetColorAttachmentRendererID(0), ImVec2(SpecView[0], SpecView[1]), ImVec2(0, 1), ImVec2(1, 0));
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* Payload = ImGui::AcceptDragDropPayload("WIDGET_PANEL_ITEM"))
			{
				const UIComponentType::Value* Val = (UIComponentType::Value*)Payload->Data;
				UIComponentType WidgetType = UIComponentType(*Val);
				std::string ID = std::to_string(m_UIComponents.size() + 1);
				std::string Name = std::vformat("{}_{}", std::make_format_args((const std::string)WidgetType.ToString(), ID));
				m_UIComponents.emplace_back(UIComponent::Create(Name, WidgetType.ToValue()));
			}
		}
		ImGui::SameLine(0.f,12.f);
		RenderDetailsPane();
		ImGui::End();

	}

	void UIEditorWindow::RenderWidgetsPane(float PaneWidth)
	{
		ImGui::BeginChild("Widgets", ImVec2(PaneWidth,0.f));

		rttr::type CompTypes = rttr::type::get_by_name("UIComponentType");
		rttr::enumeration Types = CompTypes.get_enumeration();
		for (auto& Type : Types.get_names())
		{
			ImGui::Text(Type.data());
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
			{
				const UIComponentType::Value WidgetType = Types.name_to_value(Type).get_value<UIComponentType::Value>();
				ImGui::SetDragDropPayload("WIDGET_PANEL_ITEM", &WidgetType, sizeof(UIComponentType::Value));
				ImGui::EndDragDropSource();
			}
		}
		ImGui::Separator();
		RenderHierarchyPane();
		ImGui::EndChild();
	}

	void UIEditorWindow::RenderDetailsPane()
	{
		auto& io = ImGui::GetIO();
		if (!ImGui::BeginChild("DetailsPanel",ImVec2(400.f,0.f)))
		{
			ImGui::EndChild();
			return;
		}
		if (m_SelectionContext)
		{
			ImGui::Text("Properties");
			DrawProperties(m_SelectionContext);
			ImGui::Dummy({0.f,8.f});
			ImGui::Separator();
			ImGui::Text("Content");
			DrawContent(m_SelectionContext);

		}
		ImGui::EndChild();
	}

	void UIEditorWindow::RenderHierarchyPane()
	{
		ImGui::BeginChild("HierarchyPanel",ImVec2(400.f,0.f));
		if (ImGui::CollapsingHeader("Hierarchy"))
		{
			if (ImGui::TreeNode("Root"))
			{

				for (auto U : m_UIComponents)
				{
					bool IsSelected = m_CurrentSelectedComponent == U->GetName();
					if (ImGui::Selectable(std::vformat("{}", std::make_format_args(U->GetName())).c_str(), IsSelected))
					{
						m_SelectionContext = U;
					}
					if (IsSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::TreePop();
			}
		}

		ImGui::EndChild();
	}

	void UIEditorWindow::SetViewportSize(Vector2 Size)
	{
		m_EditorCamera.SetViewportSize(Size.x,Size.y);
		m_UIFrameBuffer->Resize((uint32_t)Size.x, (uint32_t)Size.y);
	}

	static uint32_t SplitterIndex = 0;
	bool UIEditorWindow::Splitter(bool SplitVertically, float Thickness, float* Size1, float* Size2, float Min_Size1, float Min_Size2, float SplitterLongAxisSize)
	{
		ImGuiContext& G = *GImGui;
		ImGuiWindow* Window = G.CurrentWindow;
		ImGuiID ID = Window->GetID("##Splitter");
		SplitterIndex++;
		ImRect BB;
		BB.Min = Window->DC.CursorPos + (SplitVertically ? ImVec2(*Size1, 0.f) : ImVec2(0.f, *Size1));
		BB.Max = BB.Min + ImGui::CalcItemSize(SplitVertically ? ImVec2(Thickness, SplitterLongAxisSize) : ImVec2(SplitterLongAxisSize, Thickness), 0.f, 0.f);

		return ImGui::SplitterBehavior(BB, ID, SplitVertically ? ImGuiAxis_X : ImGuiAxis_Y, Size1, Size2, Min_Size1, Min_Size2, 0.f);
	}
} // AGE