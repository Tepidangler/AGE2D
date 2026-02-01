//
// Created by gdmgp on 12/3/2025.
//
#pragma once
#include <Age.h>
#ifndef AGE2D_UILAYER_H
#define AGE2D_UILAYER_H

namespace Proj
{
	class UILayer : public AGE::Layer
	{
	public:
		UILayer();
		virtual ~UILayer();

		void Init() override;
		void OnUpdate(AGE::TimeStep DeltaTime) override;
		virtual void OnAttach() override;
		void OnEvent(AGE::Event& Event) override;


	private:
		AGE::EWidgetStack m_TopWidgetStack = AGE::EWidgetStack::INVALID;
		AGE::WidgetStack m_ModalStack;
		AGE::WidgetStack m_GameStack;
		AGE::WidgetStack m_MenuStack;
		AGE::WidgetStack m_SplashStack;
		AGE::EditorCamera m_EditorCamera;
		AGE::Ref<AGE::FrameBuffer> m_FrameBuffer;
		AGE::StringProperties m_Props;
		AGE::TimeStep m_DT;

		bool OnWidgetConstructed(AGE::WidgetConstructedEvent& E);
		bool OnRenderUI(AGE::RenderUIEvent& E);
	};
} // Proj

#endif //AGE2D_UILAYER_H