#pragma once
#include <Age.h>

namespace Proj
{
	class GameViewport : public AGE::Layer
	{
	public:

		GameViewport(const char* Name);
		virtual ~GameViewport() = default;

		void Init() override;
		virtual void OnUpdate(AGE::TimeStep DeltaTime) override;
		virtual void OnImGuiRender(AGE::TimeStep DeltaTime) override;

		virtual void OnEvent(AGE::Event& E) override;

	private:
		AGE::Ref<AGE::FrameBuffer> m_Framebuffer;
		std::string m_Name;
		AGE::Vector2 m_ViewportBounds[2];

	};
}