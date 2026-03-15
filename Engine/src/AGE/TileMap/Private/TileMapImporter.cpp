#include "AGEpch.hpp"
#include "TileMap/Public/TileMapImporter.h"

#include "Platform/OpenGL/Public/OpenGLTexture.h"
#include "Scene/Public/Scene.h"
#include "Scene/Public/Entity.h"
#include "Texture/Public/Texture.h"



namespace AGE
{
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