//
// Created by gdmgp on 12/3/2025.
//
#pragma once
#ifndef AGE2D_MAINMENU_H
#define AGE2D_MAINMENU_H
#include <Age.h>

namespace Proj
{
	class MainMenu : public AGE::ScriptableWidget
	{
	public:
#if 0
		MainMenu(const std::string& Name);
		~MainMenu();
#endif
		void OnUpdate(AGE::TimeStep DeltaTime) override;

		void SetVisibility(bool Visibility) override {bIsVisible = Visibility;}

		void OnEvent(AGE::Event& Event) override;

		bool OnSceneChanged(AGE::SceneChangedEvent& Event);

	protected:
		void OnInit() override;
		void OnConstruct() override;
		void OnDestroy() override;
		void Reset() override;


	private:


		bool OnWindowResize(AGE::WindowResizeEvent& Event);
	};
} // Proj

#endif //AGE2D_MAINMENU_H