#include <Core/Public/AGEpch.hpp>
#include "Editor_ImGui/Public/ContentBrowserPanel.h"
#include <Age.h>
#include <imgui.h>

namespace AGE
{

	ContentBrowserPanel::ContentBrowserPanel()
	{
		AppConfig Config = App::Get().GetAppConfig();
		m_DirectoryIcon = Texture2D::Create(Config.EditorAssetPath.string() + "/Resources/Icons/ContentBrowser/Folder_icon.png");
		m_FileIcon = Texture2D::Create(Config.EditorAssetPath.string() + "/Resources/Icons/ContentBrowser/File_icon.png");
		m_CurrentDirectory = Config.GameContentPath.parent_path();
		m_AssetDirectory = Config.GameContentPath.parent_path();
	}
	void ContentBrowserPanel::OnImGuiRender()
	{
		if (m_CurrentDirectory.empty())
		{
			AppConfig Config = App::Get().GetAppConfig();
			m_CurrentDirectory = Config.GameContentPath;
		}
		switch (RendererAPI::GetAPI())
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			if (ImGui::Begin("Content Broswer"))
			{
				if (m_CurrentDirectory != std::filesystem::path(m_AssetDirectory))
				{
					if (ImGui::Button("<-"))
					{
						m_CurrentDirectory = m_CurrentDirectory.parent_path();
					}
				}

				static float Padding = 16.f;
				static float ThumbnailSize = 128.f;
				float CellSize = ThumbnailSize + Padding;

				float PanelWidth = ImGui::GetContentRegionAvail().x;
				int ColumnCount = (int)(PanelWidth / CellSize);
				if (ColumnCount < 1)
				{
					ColumnCount = 1;
				}

				ImGui::Columns(ColumnCount, 0, false);

				for (auto& DirectoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
				{
					const auto& Path = DirectoryEntry.path();
					auto AbsolutePath = std::filesystem::absolute(Path);
					std::string FileNameString = AbsolutePath.filename().string();

					ImGui::PushID(FileNameString.c_str());

					Ref<Texture2D> Icon = DirectoryEntry.is_directory() ? m_DirectoryIcon : m_FileIcon;
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
					ImGui::ImageButton((ImTextureID)Icon->GetTextureID(), { ThumbnailSize, ThumbnailSize }, { 0,1 }, { 1,0 });

					if (ImGui::BeginDragDropSource())
					{
						const wchar_t* ItemPath = AbsolutePath.c_str();
						ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", ItemPath, (wcslen(ItemPath) + 1) * sizeof(wchar_t));
						ImGui::EndDragDropSource();
					}
					ImGui::PopStyleColor();

					if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
					{
						if (DirectoryEntry.is_directory())
						{
							m_CurrentDirectory /= Path.filename();
						}
					}

					ImGui::TextWrapped(FileNameString.c_str());
					ImGui::NextColumn();

					ImGui::PopID();

				}

				ImGui::Columns(1);

				ImGui::SliderFloat("Thumbnail Size", &ThumbnailSize, 16, 512);
				ImGui::SliderFloat("Padding", &Padding, 0, 32);

				ImGui::End();

			}
			break;
		}
		}
		
	}
	void ContentBrowserPanel::OnEvent(Event& E)
	{
		EventDispatcher Dispatcher(E);

		Dispatcher.Dispatch<RendererChangeEvent>(BIND_EVENT_FN(ContentBrowserPanel::OnRendererChanged));
	}
	bool ContentBrowserPanel::OnRendererChanged(RendererChangeEvent& E)
	{
		AppConfig Config = App::Get().GetAppConfig();
		m_DirectoryIcon.reset();
		m_FileIcon.reset();

		m_DirectoryIcon = Texture2D::Create(Config.EditorAssetPath.string() + "/Resources/Icons/ContentBrowser/Folder_icon.png");
		m_FileIcon = Texture2D::Create(Config.EditorAssetPath.string() + "/Resources/Icons/ContentBrowser/File_icon.png");

		return false;
	}
}