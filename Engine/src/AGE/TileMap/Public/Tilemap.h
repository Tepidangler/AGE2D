//
// Created by gdmgp on 3/14/2026.
//

#ifndef AGE_TILEMAP_H
#define AGE_TILEMAP_H
#include "Core/Public/Pointers.h"
#include "Scene/Public/Scene.h"
#include "Texture/Public/Texture.h"
#include "Core/Public/UUID.h"
#include <tmx.h>

namespace AGE
{

	struct TMXData
	{
		std::vector<tmx_layer*> Layers;
	};
	class Tilemap
	{
	public:
		Tilemap(tmx_map* Map);
		~Tilemap();

		/**
 * @brief Gets the texture associated with this Tilemap object.
 *
 * @return A reference to the Texture object that is used by this Tilemap.
 */
Ref<Texture> GetTexture() {return m_TilemapTexture;}
		/**
 * @brief Retrieves the current scene object.
 *
 * This function returns a reference to the currently active scene in the application. The returned Scene object can be used for various operations such as rendering, updating, and interacting with the objects within it.
 * 
 * @return A reference to the current scene (Ref<Scene>). If no scene is set, this function will return an empty reference.
 */
Ref<Scene> GetScene() { return m_Scene; }
		/**
 * @brief Returns the path stored in the object.
 * @return The path as a std::filesystem::path object.
 */
std::filesystem::path GetPath() const { return m_Path; }
		/**
 * @brief This function returns the asset ID of an object.
 * @return UUID The unique identifier for the asset.
 */
UUID GetAssetID() { return m_AssetID; }
		void SetData(Ref<Texture> Atlas, std::filesystem::path& path);
		void SetScene(Ref<Scene> scene);



	private:
		Ref<Scene> m_Scene;
		Ref<Texture> m_AtlasTexture;
		Ref<Texture> m_TilemapTexture;
		std::filesystem::path m_Path;
		tmx_map* m_Map = nullptr;
		TMXData m_TMXData;
		UUID m_AssetID;

		void BuildTilemap();
		void SetTileLocations();
		int ProcessLayers(tmx_layer* Head);
	};
} // AGE

#endif //AGE_TILEMAP_H