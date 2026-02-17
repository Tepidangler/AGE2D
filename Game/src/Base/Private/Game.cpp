#if AG_DIST
#include <Age.h>
#include <Core/Public/EntryPoint.h>

#include "Base/Public/GameLayer.h"
#include "Base/Public/GameViewport.h"
#include "Base/Public/Dockspace.h"

namespace AGE
{
	class GameApp : public AGE::App
	{
	public:
		GameApp(ApplicationCommandLineArgs args)
			:App("Test Project", args)
		{
			PushLayer(new Proj::GameLayer());
			PushLayer(new Proj::Dockspace());
			PushLayer(new Proj::GameViewport("Viewport"));

		}

		~GameApp()
		{


		}

	};




	AGE::App* CreateApp(ApplicationCommandLineArgs args)
	{
		return new GameApp(args);
	}
}
#endif // AG_DIST