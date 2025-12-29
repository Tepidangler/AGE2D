//
// Created by gdmgp on 12/6/2025.
//

#ifndef AGE2D_NEWPROJECTLAYER_H
#define AGE2D_NEWPROJECTLAYER_H
#include <Age.h>
#include "MenuSystem/Public/CreateProjectMenu.h"

namespace AGE
{
	class NewProjectLayer : public Layer
	{
	public:
		NewProjectLayer();
		~NewProjectLayer();
		void Init() override;
		void OnUpdate(TimeStep DeltaTime) override;
		void OnEvent(AGE::Event& Event) override;
		virtual void OnAttach() override;
		void OnDetach() override;
		virtual void OnImGuiRender(TimeStep DeltaTime) override;

	private:

		Ref<ProjectMenu> m_ProjectMenu;


	};
} // AGE

#endif //AGE2D_NEWPROJECTLAYER_H