#if !AG_DIST
#include <Age.h>
#include <Core/Public/EntryPoint.h>

#include "Editor_Core/Public/EditorLayer.h"
#include "Editor_Core/Public/NewProjectLayer.h"
#include <Base/Public/GameLayer.h>
#include <Base/Public/GameViewport.h>
#include <Base/Public/UiLayer.h>
#if AG_DIST

#endif 

namespace AGE
{
	class Editor : public AGE::App
	{
	public:
		Editor(ApplicationCommandLineArgs args)
			:App("AGE Editor", args)
		{

			PushLayer(new NewProjectLayer());
			PushLayer(new Proj::GameLayer());
			//PushLayer(new Proj::GameViewport("GameViewport"));
			PushLayer(new EditorLayer());
			PushLayer(new Proj::UILayer());
		}

		~Editor()
		{


		}

	};




	AGE::App* AGE::CreateApp(ApplicationCommandLineArgs args)
	{
		return new Editor(args);
	}
}
#endif