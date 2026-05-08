#include "AGEpch.hpp"
#include "TileMap/Public/TileMapImporter.h"
#include "Scene/Public/Scene.h"
#include "Scene/Public/Entity.h"
#include "Texture/Public/Texture.h"



namespace AGE
{
	Ref<Scene> TileMapImporter::s_ActiveScene = nullptr;
	std::string TileMapImporter::s_TilesetPath = "";
	Ref<Texture2D> TileMapImporter::s_Texture = nullptr;

	/**
 * @brief Constructor for the TileMapImporter class.
 * 
 * This constructor initializes a new instance of the TileMapImporter class with a reference to an active scene. It also sets up the image loading and freeing functions used by the tmx parser library.
 * 
 * @param S A const reference to the current Scene object.
 */
TileMapImporter::TileMapImporter(const Ref<Scene>& S)
	{
		s_ActiveScene = S;
		tmx_img_load_func = ImageLoad;
		tmx_img_free_func = ImageFree;
	}
	/**
 * @brief Constructs a TileMapImporter object.
 *
 * This constructor sets up the TileMapImporter with the given Scene. It also sets two callback functions for loading and freeing images, which are used by the TMX library.
 * 
 * @param S The Scene to be imported.
 */
TileMapImporter::TileMapImporter(const Scene& S)
	{
		tmx_img_load_func = ImageLoad;
		tmx_img_free_func = ImageFree;
	}
	/**
 * @brief Destructor for the TileMapImporter class. Frees any memory allocated by tmx_map_free() if m_TileMap is not null.
 * 
 * This function frees up the memory that was previously allocated to store a tile map using tmx_map_free(). It does this in the destructor of the TileMapImporter class, which means it will automatically be called when an object of this class goes out of scope or is explicitly destroyed. 
 *
 * @return void
 */
TileMapImporter::~TileMapImporter()
	{
		if (m_TileMap)
		{
			tmx_map_free(m_TileMap);
		}
	}
	/**
 * @brief Sets the active scene for the TileMapImporter.
 *
 * This function sets the reference to the active scene that will be used by the importer.
 * The new active scene is passed as a const reference to avoid unnecessary copying.
 *
 * @param S A constant reference to the new active scene.
 */
void TileMapImporter::SetActiveScene(const Ref<Scene>& S)
	{
		s_ActiveScene = S;
	}
	/**
 * @brief Import a tile map from the specified file path.
 * 
 * This function attempts to load a tmx_map object from the provided file path. If successful, it sets the tileset path and returns the loaded map. Otherwise, it logs an error message and returns nullptr.
 * 
 * @param FilePath The path of the tile map file to be imported.
 * @return A pointer to the imported tmx_map object if successful; otherwise, nullptr.
 */
tmx_map* TileMapImporter::ImportMap(const std::string& FilePath)
	{
		if (FilePath == "")
		{
			return nullptr;
		}
		SetTileSetPath(FilePath);
		m_TileMap = tmx_load(FilePath.c_str());
		if (!m_TileMap)
		{
			CoreLogger::Error("Could not Load TileMap At {0} !", FilePath.c_str());
			return nullptr;
		}
		CoreLogger::Info("{0} Loaded Successfully!", FilePath.c_str());
		return m_TileMap;
	}
	/**
 * @brief Loads an image from a given path and returns its pointer.
 * 
 * This function takes in a string representing the file path of the image to be loaded. It checks if this path contains a "/" character, indicating that it is likely a full file path. If not, it attempts to load the image using only the base name (i.e., everything after the last "A").
 * 
 * @param Path The file path of the image to be loaded.
 * @return A pointer to the loaded texture or nullptr if loading fails.
 */
void* TileMapImporter::ImageLoad(const char* Path)
	{
		AGE_PROFILE_FUNCTION();
		std::string tmp = Path;
		auto sepmissing = (tmp.find("/") == std::string::npos);
		auto sepmissingalt = (tmp.find("/") == std::string::npos);

		if (!sepmissing && !sepmissingalt)
		{
			std::string BasePath = tmp.substr(tmp.find_last_of("A"));
			Ref<Texture2D> Tex = Texture2D::Create(BasePath);
			s_Texture = Tex;
			if (Tex.get())
			{
				return Tex.get();
			}
		}
		return nullptr;
	}
	/**
 * @brief Frees an image by setting its memory to zero and nullifying the pointer.
 * 
 * This function takes a void pointer as input which is expected to be of type Texture2D*. It sets all bytes in the memory block pointed to by Address to zero using memset, effectively freeing any resources associated with that texture. The pointer itself is then set to null.
 * 
 * @param Address A pointer to a Texture2D object which will be freed.
 * @return void
 */
void TileMapImporter::ImageFree(void* Address)
	{
		memset(Address, 0, sizeof(Texture2D));
		return;
	}
}