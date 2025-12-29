#pragma once
#include <filesystem>
#include <Texture/Public/Texture.h>
#include <Age.h>

namespace AGE
{
	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender();

		void OnEvent(Event& E);

	private:
		bool OnRendererChanged(RendererChangeEvent& E);
	private:

		std::filesystem::path m_CurrentDirectory;
		std::filesystem::path m_AssetDirectory;

		Ref<Texture2D> m_DirectoryIcon;
		Ref<Texture2D> m_FileIcon;
	};
}