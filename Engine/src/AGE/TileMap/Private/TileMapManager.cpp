#include "AGEpch.hpp"
#include "TileMap/Public/TileMapManager.h"

#include "Debug/Public/Instrumentor.h"
#include "Texture/Public/Texture.h"
#include "TileMap/Public/Tilemap.h"

namespace AGE
{
	/**
 * @brief Constructs a TileMapManager object.
 * 
 * This function initializes the TileMapManager by creating an instance of `tmx_resource_manager` and assigning it to member variable `m_Manager`.
 */
/**
 * @brief Constructs a TileMapManager object.
 * This function initializes the TileMapManager, setting up the resource manager and tile map importer.
 */
TileMapManager::TileMapManager()
	{
		m_Manager = tmx_make_resource_manager();
		m_Importer = CreateRef<TileMapImporter>();
		tmx_img_load_func = ImageLoad;
		tmx_img_free_func = ImageFree;

	}

	/** 
 * @brief Loads a tile map from the specified path into the TileMapManager.
 * 
 * This function takes in a file system path, uses an importer to import the map data from that path, creates a new Tilemap object with this imported data, sets its data (atlas texture and path) based on the current tile map's data, and then adds it to the list of tile maps.
 * 
 * @param Path The file system path where the tile map is located.
 * @return void No return value.
 */
void TileMapManager::LoadTileMap(const std::filesystem::path &Path)
	{
		Tilemap NewMap(m_Importer->ImportMap(Path.string()));

		NewMap.SetData(m_CurrentTileMap.m_AtlasTexture,m_CurrentTileMap.m_Path);
		m_TileMaps.emplace_back(NewMap);
	}

	/**
 * @brief Loads a list of tile maps from the given paths into the manager's collection.
 * 
 * This function iterates over each path in the provided vector, imports the corresponding tile map using the importer, and adds it to the manager's collection. The imported tile map is then configured with the current atlas texture and path before being added to the collection.
 * 
 * @param Paths A list of file paths representing the locations of the tile maps to be loaded.
 */
void TileMapManager::LoadTileMaps(const std::vector<std::filesystem::path> &Paths)
	{
		std::ranges::for_each(Paths, [&](const std::filesystem::path &Path)
		{
			Tilemap NewMap(m_Importer->ImportMap(Path.string()));

			NewMap.SetData(m_CurrentTileMap.m_AtlasTexture,m_CurrentTileMap.m_Path);
			m_TileMaps.emplace_back(NewMap);
		});
	}

	/**
 * @brief Loads the tile maps into memory from a specified address.
 * 
 * This function loads all the tile maps stored in memory at a given address. The address is passed as a void pointer, allowing for flexibility in terms of data types that can be loaded.
 *
 * @param Addr A pointer to the start of the tile map data.
 */
void TileMapManager::LoadTileMaps(void *Addr)
	{
	}

	/**
 * @brief Loads an image from a specified path and creates a Texture2D object for it.
 * 
 * This function takes in a string representing the file path of the image to be loaded, loads this image using stb_image library, generates a texture from the image data, and returns a void pointer to that texture.
 * 
 * @param Path The file path of the image to load.
 * @return A void pointer to the created Texture2D object.
 */
void* TileMapManager::ImageLoad(const char* Path)
	{
		AGE_PROFILE_FUNCTION();

		Get().m_CurrentTileMap.m_AtlasTexture = Texture2D::Create(Path);
		Get().m_CurrentTileMap.m_Path = Path;
		return (void*)(uintptr_t)Get().m_CurrentTileMap.m_AtlasTexture.get();
	}
	/**
 * @brief Frees an image previously allocated with ImageAlloc.
 *
 * This function takes a void pointer to an image that was previously allocated using the ImageAlloc function and frees it, effectively deallocating the memory used by this image. The size of the image is determined by sizeof(Texture2D). 
 *
 * @param Address A void pointer to the image to be freed. This should have been obtained from a previous call to ImageAlloc.
 */
void TileMapManager::ImageFree(void* Address)
	{
		// Here we'll convert the void* to a Texture and then just delete it
		memset(Address, 0, sizeof(Texture2D));
		free(Address);
	}


}
