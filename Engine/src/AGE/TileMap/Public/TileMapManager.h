#pragma once
#include <tmx.h>


namespace AGE
{
	class TileMapManager
	{
	public:

		TileMapManager();
		~TileMapManager() = default;

	private:

		tmx_resource_manager* m_Manager;
	};

}