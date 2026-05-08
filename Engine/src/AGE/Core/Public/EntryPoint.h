#pragma once
#include"Core/Public/App.h"



//Creates our Game/App for us rather than having to do that inside of the application itself because we don't truly know what anyone might use this for.
// Looking at you here Donald.

extern AGE::App* AGE::CreateApp(ApplicationCommandLineArgs args);

/**
 * @brief Main function of the application. Initializes logging, creates an instance of the application, runs it and deletes it before ending the program.
 * 
 * @param argc The number of command line arguments passed to the program.
 * @param argv An array of pointers to the command line arguments.
 * 
 * @return int Returns 0 upon successful execution of the application.
 */
int main(int argc, char** argv)
{
	AGE::Log::Init();
	AGE::CoreLogger::Info("Initialized AGECORE Log");
	AGE::GameLogger::Info("Initialized AGEGame Log"); 
	AGE_PROFILE_BEGIN_SESSION("Startup", "./AGEProfile-Startup.json");
	auto app = AGE::CreateApp({argc, argv});
	AGE_PROFILE_END_SESSION();
	AGE_PROFILE_BEGIN_SESSION("Runtime", "./AGEProfile-Runtime.json");
	app->Run();
	AGE_PROFILE_END_SESSION();
	AGE_PROFILE_BEGIN_SESSION("Shutdown", "./AGEProfile-Shutdown.json");
	delete app;
	AGE_PROFILE_END_SESSION();
}


