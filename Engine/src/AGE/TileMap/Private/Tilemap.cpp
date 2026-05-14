//
// Created by gdmgp on 3/14/2026.
//

#include "TileMap/Public/Tilemap.h"

#include "Debug/Public/Instrumentor.h"

namespace AGE
{
	/**
 * @brief Constructs a Tilemap object from a tmx_map pointer.
 * 
 * This function takes in a pointer to a tmx_map structure and assigns it to the member variable m_Map. The purpose of this constructor is to initialize an instance of the Tilemap class with a map data structure.
 * 
 * @param Map Pointer to a tmx_map object containing the map data.
 */
Tilemap::Tilemap(tmx_map* Map)
		:m_Map(Map)
	{

	}

	/**
 * @brief Destructor for the Tilemap class.
 */
Tilemap::~Tilemap()
	{
	}

	/**
 * @brief Sets the data for the tilemap.
 * 
 * This function sets the texture atlas and file path for the tilemap. The Atlas parameter is moved into the m_AtlasTexture member variable, while the path parameter is assigned to m_Path. After this operation, both parameters are cleared.
 * @param Atlas A reference to a Texture object that will be used as the texture atlas for the tilemap.
 * @param path The file path of the tilemap data.
 */
void Tilemap::SetData(Ref<Texture> Atlas, std::filesystem::path& path)
	{
		m_AtlasTexture.reset(Atlas.get());
		Atlas.reset();
		m_Path = path;
		path.clear();
	}

	/**
 * @brief Sets the Scene for the Tilemap object.
 *
 * This function sets the Scene member variable of the Tilemap class to a given Ref<Scene> object. It takes in one parameter, which is the new scene that will be set.
 *
 * @param scene The new Scene to be set for the Tilemap object.
 */
void Tilemap::SetScene(Ref<Scene> scene)
	{
		m_Scene =scene;
	}

	/**
 * @brief Builds the tilemap based on the provided configuration.
 * 
 * This function is responsible for creating a grid of tiles using the data from the provided configuration. The size and type of these tiles are determined by the configuration parameters.
 *
 * @return void
 */
void Tilemap::BuildTilemap()
	{
	}

	
void Tilemap::SetTileLocations()
	{
		AGE_PROFILE_FUNCTION();
		unsigned long Width, Height;

		//Now sure if 1 will always be valid, but it should be
		Width = m_Map->tiles[1]->tileset->image->width;
		Height = m_Map->tiles[1]->tileset->image->height;
#if 0
		for (unsigned long x = (Height / TileMap->tiles[1]->tileset->tile_height)-1; x >= 0 ; x--)
		{
			for (uint64_t y = 0; y < (Width / TileMap->tiles[1]->tileset->tile_width); y++)
			{
				TileLocs.push_back(Vector2((float)y, (float)x));
			}
		}

		for (size_t i = 0; i < TileLocs.size() - 1; i++)
		{
			TileTextures.push_back(SubTexture2D::CreateFromCoords(TileMapTexture, TileLocs[i], { (float)TileMap->tiles[1]->tileset->tile_width,(float)TileMap->tiles[1]->tileset->tile_height}));
		}
#endif
	}

	/**
 * @brief Processes the layers of a tilemap and adds them to the Layers member variable.
 *
 * This function iterates over all layers in the provided linked list, adding each layer to the end of the Layers vector. It also counts the number of layers processed and returns this count.
 *
 * @param Head Pointer to the first layer in a linked list of layers.
 * @return The number of layers processed.
 */
int Tilemap::ProcessLayers(tmx_layer* Head)
	{
		int Tmp = 0;
		tmx_layer* Current = Head;
		while (Current)
		{
			m_TMXData.Layers.emplace_back(Current);
			Current = Current->next;
			Tmp++;
		}

		return Tmp;
	}
} // AGE