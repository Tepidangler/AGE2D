//
// Created by gdmgp on 12/3/2025.
//
#pragma once
#ifndef AGE2D_MAINMENU_H
#define AGE2D_MAINMENU_H
#include <Age.h>


namespace Proj
{
	class MainMenu : public AGE::Widget
	{
		public:
		MainMenu(const std::string& Name);
		~MainMenu();

		void OnUpdate(AGE::TimeStep DeltaTime) override;

		bool ShouldBeVisible() const override {return bIsVisible;}
		void SetVisibility(bool Visibility) override {bIsVisible = Visibility;}

		void OnEvent(AGE::Event& Event) override;

		bool OnSceneChanged(AGE::SceneChangedEvent& Event);



	private:
		std::vector<AGE::Ref<AGE::UIComponent>> m_UIComponents;


		bool OnWindowResize(AGE::WindowResizeEvent& Event);
	};
} // Proj

#endif //AGE2D_MAINMENU_H