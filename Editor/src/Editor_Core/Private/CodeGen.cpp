//
// Created by gdmgp on 2/3/2026.
//

#include "../Public/CodeGen.h"
#include <AGE.h>

#include <format>

namespace AGE
{
	bool CodeGen::CreateFile(const std::string& FileName, AssetType Type)
	{
		switch (Type)
		{
			case AssetType::Widget:
			{
				Ref<WidgetCodeGen> CG = CreateRef<WidgetCodeGen>();
				return CG->CreateHeader(FileName) && CG->CreateSource(FileName);
			}
			default
			{
				CoreLogger::Error("Invalid Asset Type. Code generation cancelled!");
				return false;
			}
		}
	}

	bool WidgetCodeGen::CreateHeader(const std::string& FileName)
	{
		std::string HDR = R"(
#pragma once
#include <Age.h>
	class {} : public AGE::ScriptableWidget
	{
	public:
		void OnUpdate(AGE::TimeStep DeltaTime) override;
		void SetVisibility(bool Visibility) override {bIsVisible = Visibility;}
		void OnEvent(AGE::Event& Event) override;
		bool OnSceneChanged(AGE::SceneChangedEvent& Event);
		RTTR_ENABLE(AGE::ScriptableWidget)
		RTTR_REGISTRATION_FRIEND
	protected:
		void OnInit() override;
		void OnConstruct() override;
		void OnDestroy() override;
		void Reset() override;
	private:
		bool OnWindowResize(AGE::WindowResizeEvent& Event);
	};
	)";

			HDR = std::vformat(HDR, std::make_format_args(FileName));
			return false;
	}

	bool WidgetCodeGen::CreateSource(const std::string& FileName)
	{

		std::string SRC =
		R"(
#include "../Public/MainMenu.h"

RTTR_REGISTRATION{
	rttr::registration::class_<{0}>("{0}")
	.property("Components", &{0}::m_UIComponents)(rttr::metadata("Description", "Components that live inside of this widget"));
}

	void {0}::OnInit()
	{
	}

	void {0}::OnConstruct()
	{
		ScriptableWidget::OnConstruct();
	}


	void {0}::OnDestroy()
	{
		ScriptableWidget::OnDestroy();
		for (auto& UIComponent : m_UIComponents)
		{
			UIComponent.reset();
		}
	}

	void {0}::Reset()
	{
		ScriptableWidget::Reset();
	}

	void {0}::OnUpdate(AGE::TimeStep DeltaTime)
	{
		ScriptableWidget::OnUpdate(DeltaTime);
		for (auto& UIComponent : m_UIComponents)
		{
			UIComponent->OnUpdate(DeltaTime);
		}
	}

	void {0}::OnEvent(AGE::Event &Event)
	{
		AGE::EventDispatcher Dispatcher(Event);

		Dispatcher.Dispatch<AGE::SceneChangedEvent>(BIND_EVENT_FN({0}::OnSceneChanged));
		Dispatcher.Dispatch<AGE::WindowResizeEvent>(BIND_EVENT_FN({0}::OnWindowResize));

		for (auto& Comp : m_UIComponents)
		{
			Comp->OnEvent(Event);
		}
	}

	bool {0}::OnSceneChanged(AGE::SceneChangedEvent &Event)
	{
		if (Event.GetScene()->GetName() == "{0}")
		{
			bIsVisible = true;

			return false;

		}
		if (Event.GetScene()->GetName() != "{0}")
		{
			bIsVisible = false;
			return false;
		}
		return false;
	}

	bool {0}::OnWindowResize(AGE::WindowResizeEvent &Event)
	{
		m_Resolution.SetResolution(Event.GetWidth(), Event.GetHeight());
		return false;
	}
	)";

		SRC = std::vformat(SRC, std::make_format_args(FileName));
		return false;
	}
} // AGE