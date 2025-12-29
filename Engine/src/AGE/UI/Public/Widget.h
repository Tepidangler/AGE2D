//
// Created by gdmgp on 12/3/2025.
//

#ifndef AGE2D_WIDGET_H
#define AGE2D_WIDGET_H
#include "Core/Public/Core.h"
#include "Core/Public/DeltaTime.h"
#include "Events/Public/Event.h"

#include "Structs/Public/DataStructures.h"

namespace AGE
{
	class Widget
	{
	public:
		virtual ~Widget() = default;

		virtual void OnUpdate(TimeStep DeltaTime) = 0;

		virtual void OnEvent(Event& E) = 0;
		virtual bool ShouldBeVisible() const = 0;
		virtual void SetVisibility(bool Visibility)  =0;

		ScreenResolution m_Resolution;
	protected:
		std::string m_Name;
		bool bIsVisible = true;
	};
} // AGE

#endif //AGE2D_WIDGET_H