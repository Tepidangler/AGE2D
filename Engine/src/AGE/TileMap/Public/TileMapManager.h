#pragma once
#include <tmx.h>


namespace AGE
{
	class TileMapManager
	{
	public:

		TileMapManager();
		/**
 * @brief Default destructor for the TileMapManager class.
 *
 * This function is responsible for releasing any resources that were acquired by the TileMapManager during its lifetime, such as memory or file handles. It does not perform any operations on the objects themselves.
 */
~TileMapManager() = default;

	private:

		tmx_resource_manager* m_Manager;
	};

}