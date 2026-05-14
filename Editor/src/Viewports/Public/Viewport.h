#pragma once
#if !AG_DIST
#include <Age.h>
#include <imgui.h>


namespace AGE
{

	class Viewport
	{
	public:

		Viewport(const char* Name);
		~Viewport() {};



		void OnUpdate(TimeStep DeltaTime);
		void OnImGuiRender(TimeStep DeltaTime, Ref<FrameBuffer> FrameBuffer, EditorCamera& Camera, int Index);
		void OnOverlayRender();

		void OnEvent(Event& E);

		bool OnKeyPressed(KeyPressedEvent& E);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& E);

	private:

		const char* m_Name;
		int m_GizmoType = -1;
		Vector2 m_ViewportBounds[2];
		[[maybe_unused]] int m_SelectedTile = -1;

		std::filesystem::path m_AssetPath;


	};
}

#endif //AG_DIST