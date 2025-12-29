#pragma once

#include "Core.h"
#include "Events/Public/Event.h"
#include "Core/Public/DeltaTime.h"



namespace AGE
{
	class AGE_API Layer
	{
	public:

		Layer(const std::string& name = "Layer");

		virtual ~Layer();

		virtual void Init() {};

		virtual void OnAttach() {}
		
		virtual void OnDetach() {}
		
		virtual void OnUpdate(TimeStep DeltaTime) {} 

		virtual void OnImGuiRender(TimeStep DeltaTime) {}
		
		virtual void OnEvent(Event& Event) {}

		float GetTime();

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}