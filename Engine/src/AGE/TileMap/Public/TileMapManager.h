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
		/**
 * @brief Default destructor for the TileMapManager class.
 *
 * This function is responsible for releasing any resources that were acquired by the TileMapManager during its lifetime, such as memory or file handles. It does not perform any operations on the objects themselves.
 */
/**
 * @brief Default destructor for TileMapManager class.
 */
~TileMapManager() = default;

		/**
 * @brief Get the singleton instance of the TileMapManager. If it doesn't exist, create a new one.
 * @return Reference to the single instance of TileMapManager.
 */
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