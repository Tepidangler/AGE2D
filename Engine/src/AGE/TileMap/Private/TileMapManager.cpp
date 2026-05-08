#include "AGEpch.hpp"
#include "TileMap/Public/TileMapManager.h"

namespace AGE
{
	/**
 * @brief Constructs a TileMapManager object.
 * 
 * This function initializes the TileMapManager by creating an instance of `tmx_resource_manager` and assigning it to member variable `m_Manager`.
 */
TileMapManager::TileMapManager()
	{
		m_Manager = tmx_make_resource_manager();

	}
}