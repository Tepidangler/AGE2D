//
// Created by gdmgp on 12/3/2025.
//

#include "../Public/UiLayer.h"
#include "UI/MainMenu/Public/MainMenu.h"

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

	}

	void UILayer::OnUpdate(AGE::TimeStep DeltaTime)
	{

	}

	void UILayer::OnAttach()
	{
		m_MenuStack.PushWidgetToStack(AGE::CreateRef<MainMenu>("MainMenu"));
		AGE::Renderer::m_WidgetStacks.emplace_back(m_MenuStack);
	}

	void UILayer::OnEvent(AGE::Event &Event)
	{
		AGE::EventDispatcher Dispatcher(Event);

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
} // Proj