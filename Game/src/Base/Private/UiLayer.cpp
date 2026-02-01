//
// Created by gdmgp on 12/3/2025.
//

#include "../Public/UiLayer.h"
//#include "UI/MainMenu/Public/MainMenu.h"

namespace Proj
{
	UILayer::UILayer()
		:Layer("UILayer")
	{
	}

	UILayer::~UILayer()
	{
	}

	void UILayer::Init()
	{
		m_Props.Text = "Assalamu Alaykum!";
		m_Props.TextFont = AGE::Font::GetDefault();
		m_Props.FontSize = 5.0;

	}

	void UILayer::OnUpdate(AGE::TimeStep DeltaTime)
	{
		m_DT = DeltaTime;
	}

	void UILayer::OnAttach()
	{
		Init();
	}

	void UILayer::OnEvent(AGE::Event &Event)
	{
		AGE::EventDispatcher Dispatcher(Event);
		Dispatcher.Dispatch<AGE::WidgetConstructedEvent>(BIND_EVENT_FN(UILayer::OnWidgetConstructed));
		Dispatcher.Dispatch<AGE::RenderUIEvent>(BIND_EVENT_FN(UILayer::OnRenderUI));

		for (auto W : m_MenuStack)
		{
			W->OnEvent(Event);
		}
		for (auto W : m_ModalStack)
		{
			W->OnEvent(Event);
		}
		for (auto W : m_GameStack)
		{
			W->OnEvent(Event);
		}
	}

	bool UILayer::OnWidgetConstructed(AGE::WidgetConstructedEvent &E)
	{
		switch ((AGE::EWidgetStack) E.GetStack())
		{
			case AGE::EWidgetStack::Menu:
			{
				m_MenuStack.PushWidgetToStack(E.GetWidget());
				m_TopWidgetStack = AGE::EWidgetStack::Menu;
				return false;
			}
			case AGE::EWidgetStack::Modal:
			{
				m_ModalStack.PushWidgetToStack(E.GetWidget());
				m_TopWidgetStack = AGE::EWidgetStack::Modal;
				return false;
			}
			case AGE::EWidgetStack::Game:
			{
				m_GameStack.PushWidgetToStack(E.GetWidget());
				m_TopWidgetStack = AGE::EWidgetStack::Game;
				return false;
			}
			case AGE::EWidgetStack::Splash:
			{
				m_SplashStack.PushWidgetToStack(E.GetWidget());
				m_TopWidgetStack = AGE::EWidgetStack::Splash;
				return false;
			}
			default:
			{
				AGE::GameLogger::Error("Invalid widget stack type");
				return true;
			}
		}
	}

	bool UILayer::OnRenderUI(AGE::RenderUIEvent &E)
	{
		AGE::Renderer2D::DrawString(m_Props);
		switch (m_TopWidgetStack)
		{
			case AGE::EWidgetStack::Menu:
			{
				m_MenuStack.OnTopUpdate(E.GetDeltaTime());
				break;
			}
			case AGE::EWidgetStack::Modal:
			{

				m_ModalStack.OnTopUpdate(E.GetDeltaTime());
				break;
			}
			case AGE::EWidgetStack::Game:
			{
				m_GameStack.OnTopUpdate(E.GetDeltaTime());
				break;
			}
			case AGE::EWidgetStack::Splash:
			{
				m_SplashStack.OnTopUpdate(E.GetDeltaTime());
				break;
			}
			default:
			{
				break;
			}
		}
		return true;
	}
} // Proj