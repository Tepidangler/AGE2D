#include "AGEpch.hpp"
#include "TileMap/Public/TileMapManager.h"

namespace AGE
{
	TileMapManager::TileMapManager()
	{
		m_Manager = tmx_make_resource_manager();

	}
}