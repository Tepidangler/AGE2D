#if !AG_DIST

#include <Age.h>
#include <Render/Public/Renderer.h>
#include <Render/Public/Renderer2D.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "Editor_ImGui/Public/Panel.h"
#include "Editor_Core/Public/EditorLayer.h"

namespace AGE
{
	Panel::Panel(const char* Name)
		: m_Name(Name)
	{

	}

	void Panel::OnImGuiRender(AGE::TimeStep DeltaTime)
	{
		ImVec2 View = ImGui::GetContentRegionAvail();

		static int Clicked = 0;

		auto Stats2D = AGE::Renderer2D::GetStats();

		std::string Name = "None";
		if (ImGui::Begin("Rendering"))
		{
			if (ImGui::CollapsingHeader("Renderer Stats"))
			{
				if (ImGui::TreeNode("Renderer 2D"))
				{
					ImGui::Text("DrawCalls: %d", Stats2D.DrawCalls);
					ImGui::Text("QuadCount: %d", Stats2D.QuadCount);
					ImGui::Text("IndexCount: %d", Stats2D.GetTotalQuadIndexCount());
					ImGui::Text("VertexCount: %d", Stats2D.GetTotalQuadVertexCount());
					ImGui::Text("TileCount: %d", Stats2D.TileCount);
					ImGui::Text("Tile VertexCount: %d", Stats2D.GetTotalTileVertexCount());
					ImGui::Text("Tile IndexCount: %d", Stats2D.GetTotalTileIndexCount());
					ImGui::Text("FPS: %f", EditorLayer::Get().DT);
					if (EditorLayer::Get().m_HoveredEntity)
					{
						Name = EditorLayer::Get().m_HoveredEntity.GetComponent<TagComponent>().Tag;
						ImGui::Text("Hovered Entity: %s", Name.c_str());
					}
					ImGui::TreePop();
				}
			}
		}
		ImGui::End();
	}
}


#endif //AG_DIST