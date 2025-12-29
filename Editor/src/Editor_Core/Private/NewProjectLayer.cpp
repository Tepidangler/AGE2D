//
// Created by gdmgp on 12/6/2025.
//

#include "../Public/NewProjectLayer.h"
#include "Editor_ImGui/Public/Dockspace.h"

namespace AGE
{
	NewProjectLayer::NewProjectLayer()
		:Layer("NewProjectLayer")
	{

	}

	NewProjectLayer::~NewProjectLayer()
	{
	}

	void NewProjectLayer::Init()
	{
		if (App::Get().GetCommandLineArgs().Count > 2)
		{
			App::Get().SetProject(Project::Load(App::Get().GetCommandLineArgs()[2]));
			ProjectLoadedEvent Event{};
			App::Get().OnEvent(Event);
		}
	}

	void NewProjectLayer::OnUpdate(TimeStep DeltaTime)
	{

	}

	void NewProjectLayer::OnEvent(AGE::Event &Event)
	{

	}

	void NewProjectLayer::OnAttach()
	{
		m_ProjectMenu = CreateRef<ProjectMenu>();
	}

	void NewProjectLayer::OnDetach()
	{
		m_ProjectMenu.reset();
	}

	void NewProjectLayer::OnImGuiRender(TimeStep DeltaTime)
	{
		DockSpace::MakeDockspace();
		m_ProjectMenu->OnImGuiRender();
	}
} // AGE