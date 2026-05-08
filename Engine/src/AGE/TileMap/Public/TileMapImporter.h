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

		/**
 * @brief Default constructor for the TileMapImporter class.
 *
 * This function initializes an instance of the TileMapImporter class with its members set to their default values.
 */
TileMapImporter() = default;
		TileMapImporter(const Ref<Scene>& S);
		TileMapImporter(const Scene& S);
		/**
 * @brief Default copy constructor for the TileMapImporter class.
 *
 * This function is used to create a new instance of the TileMapImporter class by copying an existing one. It uses the 'default' keyword, which means that it will use the compiler-generated version if available.
 *
 * @param other The existing TileMapImporter instance to copy from.
 */
TileMapImporter(const TileMapImporter&) = default;

		~TileMapImporter();

		/**
 * @brief This function returns the active scene in the application.
 * @return A reference to the active Scene object. If no active scene exists, it will return an empty Ref<Scene> object.
 */
Ref<Scene> GetActiveScene() { return s_ActiveScene; }
		void SetActiveScene(const Ref<Scene>& S);

		/**
 * @brief This function returns a reference to the string 's_TilesetPath'. It is used to get the path of the tileset.
 * @return A reference to the string 's_TilesetPath' which contains the path of the tileset.
 */
std::string& GetTileSetPath() { return s_TilesetPath; }
		/**
 * @brief Returns a reference to the texture object.
 *
 * This function returns a reference to the Texture2D object stored in the variable 's_Texture'. The returned value can be used for various operations related to textures, such as rendering or manipulation.
 * 
 * @return A reference to the Texture2D object.
 */
Ref<Texture2D> GetTexture() { return s_Texture; }
		/**
 * @brief Sets the path for the tileset.
 *
 * This function sets the base path for the tileset images. The path is used to load the tilesets from disk.
 *
 * @param BasePath The new base path for the tileset images.
 */
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