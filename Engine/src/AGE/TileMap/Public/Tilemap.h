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

		Ref<Texture> GetTexture() {return m_TilemapTexture;}
		Ref<Scene> GetScene() { return m_Scene; }
		std::filesystem::path GetPath() const { return m_Path; }
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