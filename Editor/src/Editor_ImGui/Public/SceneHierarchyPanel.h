#pragma once
#include <AGE/Scene/Public/Scene.h>
#include <AGE/Audio/AGESound/Public/Sound.h>
#include <AGE/Scene/Public/Entity.h>
#include <AGE/Texture/Public/Texture.h>


namespace AGE
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& Scene);

		Ref<Scene> GetContext() { return m_Context; }
		void SetContext(const Ref<Scene>& Context);

		Entity GetSelectedEntity() const { return m_SelectionContext; }

		void SetSelectedEntity(Entity Entt) { m_SelectionContext = Entt; }

		virtual void OnImGuiRender();

	private:

		tmx_map* SelectTileMap();

		Ref<AudioSource> SelectSound();

		void OpenNodeEditor(const std::string& Name, void* Target);

		std::filesystem::path SelectStatsFile();

		std::filesystem::path SelectSoundBank();

		void DrawEntityNode(Entity E);

		void DrawComponents(Entity E);

		void DrawCharacterComponent(ScriptableEntity* Char);

		void LoadAsepriteFile(const std::filesystem::path& FilePath);

		std::string GetFileName(const std::filesystem::path& FilePath);

	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;

		Ref<TileMapImporter> m_Importer;
		Ref<Aseprite> m_AsepriteManager;

		std::filesystem::path m_AssetPath;

		std::string m_AnimationName;

	};
};