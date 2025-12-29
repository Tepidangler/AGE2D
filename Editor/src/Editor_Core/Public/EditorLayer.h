#pragma once

#include "Editor_ImGui/Public/Dockspace.h"
#include "Editor_Core/Public/Database.h"
#include "Editor_ImGui/Public/DatabaseWindow.h"
#include "Viewports/Public/Viewport.h"
#include "Editor_ImGui/Public/Panel.h"
#include "MenuSystem/Public/MainMenuBar.h"
#include "Editor_ImGui/Public/SceneHierarchyPanel.h"
#include "Editor_ImGui/Public/ContentBrowserPanel.h"
#include "Editor_ImGui/Public/QuestManagerWindow.h"
#include "Editor_ImGui/Public/AssetRegistryWindow.h"
#include "Editor_ImGui/Public/InventoryDatabase.h"
#include "Editor_ImGui/Public/ConsoleLog.h"
#include "Editor_ImGui/Public/Toolbar.h"
#include "Editor_ImGui/Public/UiEditorWindow.h"



namespace AGE
{


	class EditorLayer : public AGE::Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;


		void SetViewportSize(AGE::Vector2 Size);

		void Init() override;
		void OnUpdate(AGE::TimeStep DeltaTime) override;
		virtual void OnAttach() override;
		virtual void OnImGuiRender(AGE::TimeStep DeltaTime) override;


		void OnEvent(AGE::Event& Event) override;

		static EditorLayer& Get() { return *s_Instance; }

	private:

		bool OnRendererChanged(RendererChangeEvent& E);
	private:

		Scope<NodeEditorManager> m_NodeEditorManager;
		Ref<Viewport> m_Viewport;
		Ref<MainMenuBar> m_MainMenuBar;
		Ref<Panel> m_Panel;
		Ref<Toolbar> m_Toolbar;
		Ref<SceneHierarchyPanel> m_SceneHierarchyPanel;
		Ref<DatabaseWindow> m_DatabaseWindow;
		Ref<ContentBrowserPanel> m_ContentBrowserPanel;
		Ref<ConsoleLogWindow> m_LogWindow;
		Ref<InventoryDatabase> m_InventoryDatabase;
		Ref<QuestManagerWindow> m_QuestManagerWindow;
		Ref<AssetRegistryWindow> m_AssetRegistryWindow;
		Ref<FrameBuffer> m_FrameBuffer;
		Ref<UIEditorWindow> m_UIEditorWindow;
		Ref<Scene> m_ActiveScene;
		Ref<Scene> m_EditorScene;
		Scope<Database> m_Database;

		std::filesystem::path m_EditorScenePath;
		EditorCamera m_EditorCamera;
			
		static EditorLayer* s_Instance;
		Vector2 m_ViewportSize = { 1280.f,720.f };
		Entity m_HoveredEntity;

	

		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

		bool bShowProjectMenu = true;

		bool m_ShouldRegisterFunctions = true;

		bool m_bLoadedIni = false;

		float DT = 0.f;

		friend class Toolbar;
		friend class MainMenuBar;
		friend class Panel;
		friend class Viewport;
		friend class TileEditor;
		friend class ProjectMenu;
		friend class SceneHierarchyPanel;
		friend class QuestManagerWindow;
	};

}