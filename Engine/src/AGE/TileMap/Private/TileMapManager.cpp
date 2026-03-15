#include "AGEpch.hpp"
#include "TileMap/Public/TileMapManager.h"

#include "Debug/Public/Instrumentor.h"
#include "Texture/Public/Texture.h"
#include "TileMap/Public/Tilemap.h"

namespace AGE
{
	TileMapManager::TileMapManager()
	{
		m_Manager = tmx_make_resource_manager();
		m_Importer = CreateRef<TileMapImporter>();
		tmx_img_load_func = ImageLoad;
		tmx_img_free_func = ImageFree;

	}

	void TileMapManager::LoadTileMap(const std::filesystem::path &Path)
	{
		Tilemap NewMap(m_Importer->ImportMap(Path.string()));

		NewMap.SetData(m_CurrentTileMap.m_AtlasTexture,m_CurrentTileMap.m_Path);
		m_TileMaps.emplace_back(NewMap);
	}

	void TileMapManager::LoadTileMaps(const std::vector<std::filesystem::path> &Paths)
	{
		std::ranges::for_each(Paths, [&](const std::filesystem::path &Path)
		{
			Tilemap NewMap(m_Importer->ImportMap(Path.string()));

			NewMap.SetData(m_CurrentTileMap.m_AtlasTexture,m_CurrentTileMap.m_Path);
			m_TileMaps.emplace_back(NewMap);
		});
	}

	void TileMapManager::LoadTileMaps(void *Addr)
	{
	}

	void* TileMapManager::ImageLoad(const char* Path)
	{
		AGE_PROFILE_FUNCTION();

		Get().m_CurrentTileMap.m_AtlasTexture = Texture2D::Create(Path);
		Get().m_CurrentTileMap.m_Path = Path;
		return (void*)(uintptr_t)Get().m_CurrentTileMap.m_AtlasTexture.get();
	}
	void TileMapManager::ImageFree(void* Address)
	{
		// Here we'll convert the void* to a Texture and then just delete it
		memset(Address, 0, sizeof(Texture2D));
		free(Address);
	}


}
