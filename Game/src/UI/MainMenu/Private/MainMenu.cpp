//
// Created by gdmgp on 12/3/2025.
//

#include "../Public/MainMenu.h"

namespace Proj
{
	MainMenu::MainMenu(const std::string& Name)
	{
		m_Name = Name;
		m_UIComponents.emplace_back(AGE::CreateRef<AGE::TextBoxComponent>("MainMenuTextBox"));
		m_UIComponents.back()->As<AGE::TextBoxComponent>()->m_StringProperties.Text = "This is the Main Menu";
		m_UIComponents.back()->As<AGE::TextBoxComponent>()->m_StringProperties.TextFont = AGE::Font::GetDefault();
		m_UIComponents.back()->As<AGE::TextBoxComponent>()->m_BoxProperties.TintColor = {0.f,0.f,1.f,1.f};
		m_UIComponents.back()->As<AGE::TextBoxComponent>()->m_BoxProperties.Position = {0.f,-2.2f,0.f};
		m_UIComponents.back()->As<AGE::TextBoxComponent>()->m_BoxProperties.Rotation = {0.f};
		m_UIComponents.back()->As<AGE::TextBoxComponent>()->m_BoxProperties.Scale = {15.f,3.f,1.f};
	}

	MainMenu::~MainMenu()
	{
		for (auto& UIComponent : m_UIComponents)
		{
			UIComponent.reset();
		}
	}

	void MainMenu::OnUpdate(AGE::TimeStep DeltaTime)
	{
		for (auto& UIComponent : m_UIComponents)
		{
			UIComponent->OnUpdate(DeltaTime);
		}
	}

	void MainMenu::OnEvent(AGE::Event &Event)
	{
		AGE::EventDispatcher Dispatcher(Event);

		Dispatcher.Dispatch<AGE::SceneChangedEvent>(BIND_EVENT_FN(MainMenu::OnSceneChanged));
		Dispatcher.Dispatch<AGE::WindowResizeEvent>(BIND_EVENT_FN(MainMenu::OnWindowResize));
	}

	bool MainMenu::OnSceneChanged(AGE::SceneChangedEvent &Event)
	{
		if (Event.GetScene()->GetName() == "MainMenu")
		{
			bIsVisible = true;

			return false;

		}
		if (Event.GetScene()->GetName() != "MainMenu")
		{
			bIsVisible = false;
			return false;
		}
		return false;
	}

	bool MainMenu::OnWindowResize(AGE::WindowResizeEvent &Event)
	{
		m_Resolution.SetResolution(Event.GetWidth(), Event.GetHeight());
		return false;
	}
} // Proj