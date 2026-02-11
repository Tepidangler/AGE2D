#pragma once
#include <tmx.h>
#include "Core/Public/Core.h"


namespace AGE
{
	class Scene;
	class Texture2D;

	class TileMapImporter
	{
	public:

		TileMapImporter() = default;
		TileMapImporter(const Ref<Scene>& S);
		TileMapImporter(const Scene& S);
		TileMapImporter(const TileMapImporter&) = default;

		~TileMapImporter();

		Ref<Scene> GetActiveScene() { return s_ActiveScene; }
		void SetActiveScene(const Ref<Scene>& S);

		std::string& GetTileSetPath() { return s_TilesetPath; }
		Ref<Texture2D> GetTexture() { return s_Texture; }
		static void SetTileSetPath(std::string BasePath) { s_TilesetPath = BasePath; }

		tmx_map* ImportMap(const std::string& FilePath);

		static void* ImageLoad(const char* Path);

		static void ImageFree(void* Address);

	private:

		tmx_map* m_TileMap = nullptr;
		
		static std::string s_TilesetPath;

		static Ref<Scene> s_ActiveScene;

		static Ref<Texture2D> s_Texture;
	};
}