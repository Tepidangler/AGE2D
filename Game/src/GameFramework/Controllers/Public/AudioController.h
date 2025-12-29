#pragma once
#include "Scene/Public/ScriptableEntity.h"
#include "Audio/AGESound/Public/AGEAudio.h"


namespace GameFramework
{
	class AudioController : public AGE::ScriptableEntity
	{
	public:

		virtual void OnCreate() override;
		virtual void OnDestroy() override;
		virtual void OnUpdate(AGE::TimeStep DeltaTime) override;
		virtual std::string GetScriptableEntityType() override { return m_Name; }



	private:
		
		std::string m_Name = "AudioController";
	};
}