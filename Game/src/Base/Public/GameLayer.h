#pragma once
#include <Age.h>
#include "GameFramework/GameState/Public/GameState.h"

namespace Proj
{
	class GameLayer : public AGE::Layer
	{
	public:

		GameLayer();

		virtual ~GameLayer();

		void Init() override;
		void SetViewportSize(AGE::Vector2 Size);

		void OnUpdate(AGE::TimeStep DeltaTime) override;
		virtual void OnAttach() override;
		void OnEvent(AGE::Event& Event) override;

		AGE::Ref<AGE::FrameBuffer> GetFramebuffer() { return m_FrameBuffer; }

		static GameLayer& Get() { return *s_Instance; }

		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

	private:
		AGE::Ref<AGE::FrameBuffer> m_FrameBuffer;
		AGE::Ref<AGE::Scene> m_ActiveScene;
		AGE::Ref<GameFramework::GameState> m_GameState;
		AGE::Vector2 m_ViewportSize = { 1280.f,720.f };
		static GameLayer* s_Instance;

		bool m_bLoadedIni = false;


		float DT = 0.f;
	};
}