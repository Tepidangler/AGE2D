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
		AGE::WidgetStack m_ModalStack;
		AGE::WidgetStack m_GameStack;
		AGE::WidgetStack m_MenuStack;
		AGE::EditorCamera m_EditorCamera;
	};
} // Proj

#endif //AGE2D_UILAYER_H