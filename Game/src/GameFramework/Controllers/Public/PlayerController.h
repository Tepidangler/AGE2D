#pragma once

#include "Scene/Public/ScriptableEntity.h"
#include "Scene/Public/Components.h"

#include "Core/Public/Input.h"


namespace GameFramework
{
	class PlayerController : public AGE::ScriptableEntity
	{
	public:

		virtual void OnCreate() override;

		virtual void OnDestroy() override;

		virtual void OnUpdate(AGE::TimeStep DeltaTime) override;

		virtual std::string GetScriptableEntityType() override { return m_Name;} 

	private:

		std::string m_Name = "PlayerController";

	};
}