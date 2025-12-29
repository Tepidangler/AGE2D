#pragma once
#include "Scene/Public/ScriptableEntity.h"
#include "Scene/Public/Components.h"


namespace GameFramework
{
	class AIController : public AGE::ScriptableEntity
	{
	public:

		virtual void OnCreate() override;

		virtual void OnDestroy() override;

		virtual void OnUpdate(AGE::TimeStep DeltaTime) override;
		virtual void OnEvent(AGE::Event& E) override;

		virtual std::string GetScriptableEntityType() override { return m_Name; }

	private:

		std::string m_Name = "AIController";

	};
}