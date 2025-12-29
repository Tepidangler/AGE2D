#if AG_DIST
#include <AGE.h>
#include <Core/Public/Entrypoint.h>

#include "Base/Public/GameLayer.h"
#include "Base/Public/GameViewport.h"
#include "Base/Public/Dockspace.h"

namespace AGE
{
	class Game : public AGE::App
	{
	public:
		Game(ApplicationCommandLineArgs args)
			:App("Test Project", args)
		{
			PushLayer(new Proj::GameLayer());
			PushLayer(new Proj::Dockspace());
			PushLayer(new Proj::GameViewport("Viewport"));

		}

		~Game()
		{


		}

	};




	AGE::App* AGE::CreateApp(ApplicationCommandLineArgs args)
	{
		return new Game(args);
	}
}
#endif // AG_DIST