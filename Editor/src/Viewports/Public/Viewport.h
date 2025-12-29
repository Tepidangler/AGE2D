#pragma once
#if !AG_DIST
#include <Age.h>
#include <imgui.h>


namespace AGE
{

	class Viewport : public Layer
	{
	public:

		Viewport(const char* Name);
		~Viewport() {};



		virtual void OnUpdate(TimeStep DeltaTime) override;
		virtual void OnImGuiRender(TimeStep DeltaTime, Ref<FrameBuffer> FrameBuffer, EditorCamera& Camera, int Index);
		void OnOverlayRender();

		virtual void OnEvent(Event& E) override;

		bool OnKeyPressed(KeyPressedEvent& E);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& E);

	private:

		const char* m_Name;
		int m_GizmoType = -1;
		Vector2 m_ViewportBounds[2];
		int m_SelectedTile = -1;

		std::filesystem::path m_AssetPath;


	};
}

#endif //AG_DIST