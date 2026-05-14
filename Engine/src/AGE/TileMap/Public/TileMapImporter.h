#pragma once
#include <tmx.h>
#include "Core/Public/Core.h"


namespace AGE
{
	class TileMapImporter
	{
	public:

		/**
 * @brief Default constructor for the TileMapImporter class.
 */
TileMapImporter() = default;
		/**
 * @brief This function is a copy constructor for the TileMapImporter class and it has been explicitly deleted to prevent copying of objects.
 * 
 * @param[in] other The object to be copied.
 * 
 * @return No return value as this function is declared '= delete'.
 */
TileMapImporter(const TileMapImporter&) = delete;
		/**
 * @brief Destructor for the TileMapImporter class.
 *
 * This function is responsible for releasing any resources that were acquired during the lifetime of an instance of this class, such as memory or file handles. It does not perform any operations on the actual data contained within the object itself.
 */
~TileMapImporter() = default;

		tmx_map* ImportMap(const std::string& FilePath);


	};
}