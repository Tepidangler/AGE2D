#pragma once
#include "TileMap/Public/TileMapImporter.h"
#include "Core/Public/UUID.h"
#include "Core/Public/Pointers.h"
#include <tmx.h>


namespace AGE
{
	class Texture;

	struct TileMapData
	{
		Ref<Texture> m_AtlasTexture;
		std::filesystem::path m_Path;
	};

	class TileMapManager
	{
	public:

		TileMapManager();
		~TileMapManager() = default;

		static TileMapManager& Get()
		{
			static TileMapManager* instance;
			if (!instance)
			{
				instance = new TileMapManager();
			}
			return *instance;
		}
		void LoadTileMap(const std::filesystem::path& Path);
		void LoadTileMaps(const std::vector<std::filesystem::path>& Paths);
		void LoadTileMaps(void* Addr);

		static void* ImageLoad(const char* Path);
		static void ImageFree(void* Address);
	private:

		Ref<TileMapImporter> m_Importer;
		tmx_resource_manager* m_Manager;
		TileMapData m_CurrentTileMap; // Represents the map currently being loaded
		std::vector<class Tilemap> m_TileMaps;


	};

}