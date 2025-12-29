#include "AGEpch.hpp"
#include "TileMap/Public/TileMapImporter.h"
#include "Scene/Public/Scene.h"
#include "Scene/Public/Entity.h"
#include "Texture/Public/Texture.h"



namespace AGE
{
	Ref<Scene> TileMapImporter::s_ActiveScene = nullptr;
	std::string TileMapImporter::s_TilesetPath = "";
	Ref<Texture2D> TileMapImporter::s_Texture = nullptr;

	TileMapImporter::TileMapImporter(const Ref<Scene>& S)
	{
		s_ActiveScene = S;
		tmx_img_load_func = ImageLoad;
		tmx_img_free_func = ImageFree;
	}
	TileMapImporter::TileMapImporter(const Scene& S)
	{
		tmx_img_load_func = ImageLoad;
		tmx_img_free_func = ImageFree;
	}
	TileMapImporter::~TileMapImporter()
	{
		if (m_TileMap)
		{
			tmx_map_free(m_TileMap);
		}
	}
	void TileMapImporter::SetActiveScene(const Ref<Scene>& S)
	{
		s_ActiveScene = S;
	}
	tmx_map* TileMapImporter::ImportMap(const std::string& FilePath)
	{
		if (FilePath == "")
		{
			return nullptr;
		}
		SetTileSetPath(FilePath);
		m_TileMap = tmx_load(FilePath.c_str());
		if (!m_TileMap)
		{
			CoreLogger::Error("Could not Load TileMap At {0} !", FilePath.c_str());
			return nullptr;
		}
		CoreLogger::Info("{0} Loaded Successfully!", FilePath.c_str());
		return m_TileMap;
	}
	void* TileMapImporter::ImageLoad(const char* Path)
	{
		AGE_PROFILE_FUNCTION();
		std::string tmp = Path;
		auto sepmissing = (tmp.find("/") == std::string::npos);
		auto sepmissingalt = (tmp.find("/") == std::string::npos);

		if (!sepmissing && !sepmissingalt)
		{
			std::string BasePath = tmp.substr(tmp.find_last_of("A"));
			Ref<Texture2D> Tex = Texture2D::Create(BasePath);
			s_Texture = Tex;
			if (Tex.get())
			{
				return Tex.get();
			}
		}
		return nullptr;
	}
	void TileMapImporter::ImageFree(void* Address)
	{
		memset(Address, 0, sizeof(Texture2D));
		return;
	}
}