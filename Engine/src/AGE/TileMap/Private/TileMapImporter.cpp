#include "AGEpch.hpp"
#include "TileMap/Public/TileMapImporter.h"

#include "Platform/OpenGL/Public/OpenGLTexture.h"
#include "Scene/Public/Scene.h"
#include "Scene/Public/Entity.h"
#include "Texture/Public/Texture.h"



namespace AGE
{
	/**
 * @brief Import a tile map from the given file path.
 * 
 * This function attempts to load a tmx_map object from the provided file path. If the file path is empty or if there's an issue with loading the file, it returns nullptr. Otherwise, it logs that the map was loaded successfully and then returns the map.
 * 
 * @param FilePath The path of the tile map file to load.
 * @return A pointer to a tmx_map object representing the loaded tile map or nullptr if there's an issue with loading the file.
 */
tmx_map* TileMapImporter::ImportMap(const std::string& FilePath)
	{
		if (FilePath == "")
		{
			return nullptr;
		}
		tmx_map* Map = nullptr;
		Map = tmx_load(FilePath.c_str());
		if (!Map)
		{
			CoreLogger::Error("Could not Load TileMap At {0} !", FilePath.c_str());
			return nullptr;
		}
		CoreLogger::Info("{0} Loaded Successfully!", FilePath.c_str());
		return Map;
	}

}