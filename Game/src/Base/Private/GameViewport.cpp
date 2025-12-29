#include "Base/Public/GameViewport.h"
#include "Base/Public/GameLayer.h"
#include <imgui.h>

namespace Proj
{
	GameViewport::GameViewport(const char* Name)
		:m_Name(Name), Layer(Name)
	{

	}

	void GameViewport::Init()
	{
		m_Framebuffer = GameLayer::Get().GetFramebuffer();
	}

	void GameViewport::OnUpdate(AGE::TimeStep DeltaTime)
	{

	}
	void GameViewport::OnImGuiRender(AGE::TimeStep DeltaTime)
	{
		ImGuiViewport* Viewport = ImGui::GetMainViewport();
		ImGuiIO& io = ImGui::GetIO();
		ImGui::SetNextWindowSize({ io.DisplaySize.x,io.DisplaySize.y });
		ImGui::SetNextWindowViewport(Viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 });
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);

		if (ImGui::Begin("Viewport"), true, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize)
		{
			auto ViewportMinRegion = ImGui::GetWindowContentRegionMin();
			auto ViewportMaxRegion = ImGui::GetWindowContentRegionMax();
			auto ViewportOffset = ImGui::GetWindowPos();

			m_ViewportBounds[0] = { ViewportMinRegion.x + ViewportOffset.x, ViewportMinRegion.y + ViewportOffset.y };
			m_ViewportBounds[1] = { ViewportMaxRegion.x + ViewportOffset.x, ViewportMaxRegion.y + ViewportOffset.y };

			GameLayer::Get().m_ViewportFocused = ImGui::IsWindowFocused();
			GameLayer::Get().m_ViewportHovered = ImGui::IsWindowHovered();

			AGE::App::Get().GetImGuiLayer()->BlockEvents(!GameLayer::Get().m_ViewportFocused && !GameLayer::Get().m_ViewportHovered);

			AGE::Vector2 View(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);
			AGE::Vector2 SpecView((float)m_Framebuffer->GetSpecification().Width, (float)m_Framebuffer->GetSpecification().Height);
			if (SpecView != View && View.x > 0 && View.y > 0)
			{

				GameLayer::Get().SetViewportSize(AGE::Vector2(View[0], View[1]));
				SpecView = View;
			}
			ImGui::Image((ImTextureID)m_Framebuffer->GetColorAttachmentRendererID(0), ImVec2(SpecView[0], SpecView[1]), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::End();
			ImGui::PopStyleVar(3);
		}
	}
	void GameViewport::OnEvent(AGE::Event& E)
	{

	}
}