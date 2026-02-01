//
// Created by gdmgp on 2/1/2026.
//

#ifndef AGE2D_VERTICALBOXCOMPONENT_H
#define AGE2D_VERTICALBOXCOMPONENT_H
#include "UI/Public/UiComponent.h"

namespace AGE
{
	class VerticalBoxComponent : public UIComponent
	{
	public:
		VerticalBoxComponent() = default;
		void OnEvent(Event& Event) override;

	private:

		std::vector<UIComponent> m_Components;
	};
} // AGE

#endif //AGE2D_VERTICALBOXCOMPONENT_H