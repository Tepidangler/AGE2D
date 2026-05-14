//
// Created by gdmgp on 3/14/2026.
//

#include "TileMap/Public/Tilemap.h"

#include "Debug/Public/Instrumentor.h"

namespace AGE
{
	Tilemap::Tilemap(tmx_map* Map)
		:m_Map(Map)
	{

	}

	Tilemap::~Tilemap()
	{
	}

	void Tilemap::SetData(Ref<Texture> Atlas, std::filesystem::path& path)
	{
		m_AtlasTexture.reset(Atlas.get());
		Atlas.reset();
		m_Path = path;
		path.clear();
	}

	void Tilemap::SetScene(Ref<Scene> scene)
	{
		m_Scene =scene;
	}

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