#pragma once
#include <Age.h>
#include <imgui.h>


namespace AGE
{
	enum class SceneState
	{
		Edit = 0,
		Play = 1
	};

	enum class TileDrawMode
	{
		Brush = 0,
		Rectangle
	};

	class Toolbar 
	{
	public:
		Toolbar();
		~Toolbar() = default;

		void OnImGuiRender();
		void OnScenePlay();
		void OnSceneStop();
		SceneState& GetSceneState() { return m_SceneState; }
		TileDrawMode& GetDrawMode() { return m_Mode; }

		void OnEvent(Event& E);

	private:
		bool OnRendererChanged(RendererChangeEvent& E);

	private:
		Ref<Texture2D> m_PlayIcon;
		Ref<Texture2D> m_StopIcon;
		SceneState m_SceneState = SceneState::Edit;
		TileDrawMode m_Mode = TileDrawMode::Brush;
	};
}
