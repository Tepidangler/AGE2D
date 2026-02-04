#pragma once
#include"Core/Public/App.h"

#ifdef AG_PLATFORM_WINDOWS

//Creates our Game/App for us rather than having to do that inside of the application itself because we don't truly know what anyone might use this for.
// Looking at you here Donald.

extern AGE::App* AGE::CreateApp(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	AGE::Log::Init();
	AGE::CoreLogger::Info("Initialized AGECORE Log");
	AGE::GameLogger::Info("Initialized AGEGame Log"); 
	AGE_PROFILE_BEGIN_SESSION("Startup", "./AGEProfile-Startup.json");
	auto app = AGE::CreateApp({argc, argv});
	AGE_PROFILE_END_SESSION();
	AGE_PROFILE_BEGIN_SESSION("Runtime", "./AGEProfile-Runtime.json");
	try {

	app->Run();
	}
	catch (const std::exception& e) {
		AGE::CoreLogger::Error("{}", e.what());
	}
	AGE_PROFILE_END_SESSION();
	AGE_PROFILE_BEGIN_SESSION("Shutdown", "./AGEProfile-Shutdown.json");
	delete app;
	AGE_PROFILE_END_SESSION();
}

#endif
