#include "AGEpch.hpp"
#include "Log.h"

#include "fmt/chrono.h"

namespace AGE
{
	Ref<spdlog::logger> Log::s_AGECoreLogger;
	Ref<spdlog::logger> Log::s_AGEGameLogger;
	std::vector<char> Log::s_Logs;
	std::vector<size_t> Log::s_Offsets;
	std::vector<LogType> Log::s_Type;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_AGECoreLogger = spdlog::stdout_color_mt("AGECORE");
		s_AGECoreLogger->set_level(spdlog::level::trace);
		s_AGEGameLogger = spdlog::stdout_color_mt("AGEGAME");
		s_AGEGameLogger->set_level(spdlog::level::trace);
		s_Offsets.push_back(0);

	}
}
