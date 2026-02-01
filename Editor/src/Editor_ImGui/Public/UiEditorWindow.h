//
// Created by gdmgp on 12/8/2025.
//

#ifndef AGE2D_UIEDITORWINDOW_H
#define AGE2D_UIEDITORWINDOW_H
#include <Age.h>

namespace AGE
{
	class UIEditorWindow
	{
	public:
		UIEditorWindow();
		~UIEditorWindow();

		void OnUpdate(TimeStep DeltaTime, EditorCamera& Camera);
		void OnImGuiRender();
		void SetViewportSize(Vector2 Size);
		bool Splitter(bool SplitVertically, float Thickness, float* Size1, float* Size2, float Min_Size1, float Min_Size2, float SplitterLongAxisSize = -1.f);

	private:
		Ref<FrameBuffer> m_UIFrameBuffer;
		Vector2 m_ViewportBounds[2];
		Vector4 m_ClearColor;
		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;
		void RenderWidgetsPane(float PaneWidth);
		void RenderDetailsPane();
		void RenderHierarchyPane();
		void DrawProperties(Ref<UIComponent> Comp);
		void DrawContent(Ref<UIComponent> Comp);
		void DrawMenuBar();
		void LoadWidget(const std::filesystem::path& Path);
		void SaveWidget(const std::filesystem::path& Path);

		bool m_Opened = true;

		//std::vector<std::string> m_UIComponentTypes = {"TextBoxComponent", "TextComponent"};

		std::deque<Ref<UIComponent>> m_UIComponents;

		Ref<UIComponent> m_SelectionContext = nullptr;

		std::string m_CurrentSelectedComponent = "";

		EditorCamera m_EditorCamera;
		ImGuiID m_ImGuiWindowID;
	};


} // AGE

#endif //AGE2D_UIEDITORWINDOW_H