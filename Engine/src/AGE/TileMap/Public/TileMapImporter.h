#pragma once
#include <tmx.h>
#include "Core/Public/Core.h"


namespace AGE
{
	class TileMapImporter
	{
	public:

		TileMapImporter() = default;
		TileMapImporter(const TileMapImporter&) = delete;
		~TileMapImporter() = default;

		tmx_map* ImportMap(const std::string& FilePath);


	};
}