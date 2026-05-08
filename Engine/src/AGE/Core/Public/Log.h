#pragma once
#include "AGEpch.hpp"
#include "Core/Public/Core.h"
#include "Core/Public/Pointers.h"

#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)

#include "spdlog/sinks/stdout_color_sinks.h"
#include <string_view>
#include <format>
#ifdef AG_PLATFORM_WINDOWS
#include <debugapi.h>
#else
#include <csignal>
#endif


namespace AGE 
{
	enum class LogType : uint8_t
	{
		Trace = 0,
		Info = 1,
		Warn = 2,
		Error = 3,
		Critical = 4

	};
	class Log
	{
	public:

		static void Init();

		/**
 * @brief This function returns a reference to the core logger used by the application.
 * @return A reference to the core logger.
 */
inline static Ref<spdlog::logger>& GetCoreLogger() { return s_AGECoreLogger; }
		/**
 * @brief This function returns a reference to the game logger object.
 *
 * The game logger is used for logging messages related to the gameplay. It provides detailed information about what's happening in the game, which can be useful for debugging and performance tuning.
 *
 * @return A reference to the game logger object.
 */
inline static Ref<spdlog::logger>& GetGameLogger() { return s_AGEGameLogger; }
		/**
 * @brief This function returns a reference to the vector 's_Logs'. The purpose of this function is to provide access to the logs for other parts of the program.
 * @return A reference to the vector 's_Logs'
 */
inline static std::vector<char>& GetLogs() { return s_Logs; }
		/**
 * @brief This function returns a reference to the vector `s_Offsets` which is used for storing offset values.
 * @return A reference to the vector `s_Offsets`.
 */
inline static std::vector<size_t>& GetOffsets() { return s_Offsets; }
		/**
 * @brief Returns a reference to the internal vector of LogTypes.
 * @return Reference to the internal vector of LogTypes.
 */
inline static std::vector<LogType>& GetTypes() { return s_Type; }


	private:

		static Ref<spdlog::logger> s_AGECoreLogger;
		static Ref<spdlog::logger> s_AGEGameLogger;

		static std::vector<char> s_Logs;
		static std::vector<size_t> s_Offsets;
		static std::vector<LogType> s_Type;

	};

	namespace CoreLogger
	{
		template<typename ... Args>
		/**
 * @brief This function logs a trace message with the specified format and arguments. 
 * The formatted string is prefixed with "[AGECORE] ". It also adds each character of the log line to Log::GetLogs() and updates Log::GetOffsets().
 * 
 * @param fmt A std::string_view representing the format string for the trace message.
 * @param args Variadic arguments representing the values to be formatted into the trace message.
 * 
 * @return void
 */
void Trace(std::string_view fmt, Args&& ... args)
		{
			std::string Line = "[AGECORE] " + std::vformat(fmt, std::make_format_args(args...)) + "\n";
			size_t Size = Line.size();
			Log::GetCoreLogger()->trace(Line);
			for (auto& c : Line)
			{
				Log::GetLogs().push_back(c);
			}
			Log::GetOffsets().push_back(Log::GetOffsets().back() + Size);
			Log::GetTypes().push_back(LogType::Trace);
#ifdef AG_PLATFORM_WINDOWS
			std::wstring wLine(Line.begin(), Line.end());
			OutputDebugString(wLine.c_str());
#elif defined(AG_PLATFORM_LINUX)
			printf("%s", Line.c_str());
#endif
		}
		template<typename ... Args>
		
void Info(std::string_view fmt, Args&& ... args)
		{
			std::string Line = "[AGECORE] " + std::vformat(fmt, std::make_format_args(args...)) + "\n";
			size_t Size = Line.size();
			Log::GetCoreLogger()->info(Line);
			for (auto& c : Line)
			{
				Log::GetLogs().push_back(c);


			}
			Log::GetOffsets().push_back(Log::GetOffsets().back() + Size);
			Log::GetTypes().push_back(LogType::Info);
#ifdef AG_PLATFORM_WINDOWS
			std::wstring wLine(Line.begin(), Line.end());
			OutputDebugString(wLine.c_str());
#elif defined(AG_PLATFORM_LINUX)
			printf("%s", Line.c_str());
#endif
		}
		template<typename ... Args>
		/**
 * @brief This function logs a warning message to the console and stores it in the log buffer for later retrieval.
 * 
 * @param fmt The format string used to create the warning message. It should follow the same syntax as printf or std::format.
 * @param args The arguments that will be substituted into the format string.
 * 
 * @return None
 */
void Warn(std::string_view fmt, Args&& ... args)
		{
			std::string Line = "[AGECORE] " + std::vformat(fmt, std::make_format_args(args...)) + "\n";
			size_t Size = Line.size();
			Log::GetCoreLogger()->warn(Line);
			for (auto& c : Line)
			{
				Log::GetLogs().push_back(c);


			}
			Log::GetOffsets().push_back(Log::GetOffsets().back() + Size);
			Log::GetTypes().push_back(LogType::Warn);
#ifdef AG_PLATFORM_WINDOWS
			std::wstring wLine(Line.begin(), Line.end());
			OutputDebugString(wLine.c_str());
#elif defined(AG_PLATFORM_LINUX)
			printf("%s", Line.c_str());
#endif
		}
		template<typename ... Args>
		/**
 * @brief This function logs an error message to the core logger and various other logging systems. 
 * The error message is formatted using a variadic template, allowing for flexible formatting of the error message.
 *
 * @param fmt A string_view representing the format string for the error message.
 * @param args Variadic arguments representing the values to be inserted into the format string.
 * 
 * @return void This function does not return a value.
 */
void Error(std::string_view fmt, Args&& ... args)
		{
			std::string Line = "[AGECORE] " + std::vformat(fmt, std::make_format_args(args...)) + "\n";
			size_t Size = Line.size();
			Log::GetCoreLogger()->error(Line);
			for (auto& c : Line)
			{
				Log::GetLogs().push_back(c);


			}
			Log::GetOffsets().push_back(Log::GetOffsets().back() + Size);
			Log::GetTypes().push_back(LogType::Error);
#ifdef AG_PLATFORM_WINDOWS
			std::wstring wLine(Line.begin(), Line.end());
			OutputDebugString(wLine.c_str());
#elif defined(AG_PLATFORM_LINUX)
			printf("%s", Line.c_str());
#endif
		}
		template<typename ... Args>
		/**
 * @brief This function logs a critical message to the system. The message is formatted using fmt::format and includes the prefix "[AGECORE] ". 
 *        It also pushes each character of the logged string into Log::GetLogs() for later analysis, increments the offset by the size of the logged string, 
 *        and sets the log type to Critical. The function supports both Windows and Linux platforms via preprocessor directives.
 * @param fmt A std::string_view representing the format string for the message.
 * @param args Variadic arguments representing the values to be formatted into the message.
 * @return void
 */
void Critical(std::string_view fmt, Args&& ... args)
		{
			std::string Line = "[AGECORE] " + std::vformat(fmt, std::make_format_args(args...)) + "\n";
			size_t Size = Line.size();
			Log::GetCoreLogger()->critical(Line);
			for (auto& c : Line)
			{
				Log::GetLogs().push_back(c);


			}
			Log::GetOffsets().push_back(Log::GetOffsets().back() + Size);
			Log::GetTypes().push_back(LogType::Critical);
#ifdef AG_PLATFORM_WINDOWS
			std::wstring wLine(Line.begin(), Line.end());
			OutputDebugString(wLine.c_str());
#elif defined(AG_PLATFORM_LINUX)
			printf("%s", Line.c_str());
#endif
		}
#ifdef AGE_ENABLE_ASSERTS
		template<typename ... Args> // CoreLogger->Assert(true ==  false, "True does not equal false")
		"This function is a critical part of debugging and should only be used when you know what you're doing."
void Assert(bool Condition, std::string_view fmt, Args&& ... args)
		{
			if (!(Condition)) {
				std::string Line = "[AGECOREASSERT] " + std::vformat(fmt, std::make_format_args(args...)) + "\n";
				size_t Size = Line.size();
				Log::GetCoreLogger()->critical(Line);
				for (auto& c : Line)
				{
					Log::GetLogs().push_back(c);


				}
				Log::GetOffsets().push_back(Log::GetOffsets().back() + Size);
				Log::GetTypes().push_back(LogType::Critical);
#ifdef AG_PLATFORM_WINDOWS
				std::wstring wLine(Line.begin(), Line.end());
				OutputDebugString(wLine.c_str());
				__debugbreak();
#elif defined(AG_PLATFORM_LINUX)
				printf("%s", Line.c_str());
#ifdef __clang__
				__builtin_debugtrap();
#else
				__builtin_trap();
#endif
#endif
			}
		}
#else// Just Do Nothing
		template<typename ... Args>
/**
 * @brief This function is used for asserting conditions in the code. If the condition is false, it throws an exception with a formatted message.
 * @param Condition The condition to be checked. It should evaluate to true if the program state is valid and false otherwise.
 * @param fmt A format string that describes how the arguments should be formatted when included into the error message.
 * @param args Variadic arguments representing values to include in the error message.
 * @return void This function does not return a value. It throws an exception if the condition is false.
 */
void Assert(bool Condition, std::string_view fmt, Args&& ... args){}
#endif

	}

	namespace GameLogger
	{
		// GameLogger::Trace("This is a logged event {0}", 12);
		template<typename ... Args>
		/**
 * @brief This function traces a message to the game logger and various other logging systems.
 * 
 * The function takes in a format string and variable arguments, formats them into a line of text, then logs this line both to the game logger and any number of additional loggers. It also records the offsets at which each character was logged for later retrieval.
 * 
 * @param fmt A std::string_view representing the format string.
 * @param args Variable arguments representing values to be inserted into the format string.
 * 
 * @return void
 */
void Trace(std::string_view fmt, Args&& ... args)
		{
			std::string Line = "[AGEGAME] " + std::vformat(fmt, std::make_format_args(args...)) + "\n";
			size_t Size = Line.size();
			Log::GetGameLogger()->trace(Line);
			for (auto& c : Line)
			{
				Log::GetLogs().push_back(c);


			}
			Log::GetOffsets().push_back(Log::GetOffsets().back() + Size);
			Log::GetTypes().push_back(LogType::Trace);
#ifdef AG_PLATFORM_WINDOWS
			std::wstring wLine(Line.begin(), Line.end());
			OutputDebugString(wLine.c_str());
#elif defined(AG_PLATFORM_LINUX)
			printf("%s", Line.c_str());
#endif
		}
		template<typename ... Args>
		/**
 * @brief This function logs informational messages to the game logger and various other logging systems.
 * 
 * @param fmt A format string that specifies how subsequent arguments are converted for output.
 * @param args Arguments following the format string.
 * 
 * @return None
 */
void Info(std::string_view fmt, Args&& ... args)
		{
			std::string Line = "[AGEGAME] " + std::vformat(fmt, std::make_format_args(args...)) + "\n";
			size_t Size = Line.size();
			Log::GetGameLogger()->info(Line);
			for (auto& c : Line)
			{
				Log::GetLogs().push_back(c);


			}
			Log::GetOffsets().push_back(Log::GetOffsets().back() + Size);
			Log::GetTypes().push_back(LogType::Info);
#ifdef AG_PLATFORM_WINDOWS
			std::wstring wLine(Line.begin(), Line.end());
			OutputDebugString(wLine.c_str());
#elif defined(AG_PLATFORM_LINUX)
			printf("%s", Line.c_str());
#endif
		}
		template<typename ... Args>
		/**
 * @brief This function is used for logging warnings in the game. It takes a format string and variable arguments, formats them into a string, 
 *        then logs this string as a warning along with other information such as log type and offsets. The formatted string is also added to 
 *        the game's logs. If the platform is Windows, it uses OutputDebugString for logging; if it's Linux, printf is used instead.
 * @param fmt A format string that specifies how the remaining arguments are converted to strings.
 * @param ...args Variable number of arguments, which will be formatted according to the provided format string.
 * @return void
 */
void Warn(std::string_view fmt, Args&& ... args)
		{
			std::string Line = "[AGEGAME] " + std::vformat(fmt, std::make_format_args(args...)) + "\n";
			size_t Size = Line.size();
			Log::GetGameLogger()->warn(Line);
			for (auto& c : Line)
			{
				Log::GetLogs().push_back(c);


			}
			Log::GetOffsets().push_back(Log::GetOffsets().back() + Size);
			Log::GetTypes().push_back(LogType::Warn);
#ifdef AG_PLATFORM_WINDOWS
			std::wstring wLine(Line.begin(), Line.end());
			OutputDebugString(wLine.c_str());
#elif defined(AG_PLATFORM_LINUX)
			printf("%s", Line.c_str());
#endif
		}
		template<typename ... Args>
		/**
 * @brief This function is used for logging errors in the game. 
 * It takes a format string and variable arguments, formats them into a line of text, logs it to various outputs (game log, debug output on Windows, standard output on Linux), and stores it for later retrieval.
 *
 * @param fmt The format string used to generate the error message. This should be a printf-style format string.
 * @param args The variable arguments that will replace placeholders in the format string. 
 *
 * @return void No return value is expected as this function only logs errors and does not handle them.
 */
void Error(std::string_view fmt, Args&& ... args)
		{
			std::string Line = "[AGEGAME] " + std::vformat(fmt, std::make_format_args(args...)) + "\n";
			size_t Size = Line.size();
			Log::GetGameLogger()->error(Line);
			for (auto& c : Line)
			{
				Log::GetLogs().push_back(c);


			}
			Log::GetOffsets().push_back(Log::GetOffsets().back() + Size);
			Log::GetTypes().push_back(LogType::Error);
#ifdef AG_PLATFORM_WINDOWS
			std::wstring wLine(Line.begin(), Line.end());
			OutputDebugString(wLine.c_str());
#elif defined(AG_PLATFORM_LINUX)
			printf("%s", Line.c_str());
#endif
		}
		template<typename ... Args>
		
void Critical(std::string_view fmt, Args&& ... args)
		{
			std::string Line = "[AGEGAME] " + std::vformat(fmt, std::make_format_args(args...)) + "\n";
			size_t Size = Line.size();
			Log::GetGameLogger()->critical(Line);
			for (auto& c : Line)
			{
				Log::GetLogs().push_back(c);


			}
			Log::GetOffsets().push_back(Log::GetOffsets().back() + Size);
			Log::GetTypes().push_back(LogType::Critical);
#ifdef AG_PLATFORM_WINDOWS
			std::wstring wLine(Line.begin(), Line.end());
			OutputDebugString(wLine.c_str());
#elif defined(AG_PLATFORM_LINUX)
			printf("%s", Line.c_str());
#endif
		}
#ifdef AGE_ENABLE_ASSERTS
		template<typename ... Args>
		"This function is used for asserting conditions in the code. If a condition fails, it logs a critical message and triggers a debug breakpoint."
void Assert(bool Condition, std::string_view fmt, Args&& ... args)
		{
			if (!(Condition)) {
				std::string Line = "[AGEGAMEASSERT] " + std::vformat(fmt, std::make_format_args(args...)) + "\n";
				size_t Size = Line.size();
				Log::GetCoreLogger()->critical(Line);
				for (auto& c : Line)
				{
					Log::GetLogs().push_back(c);


				}
				Log::GetOffsets().push_back(Log::GetOffsets().back() + Size);
				Log::GetTypes().push_back(LogType::Critical);
#ifdef AG_PLATFORM_WINDOWS
				std::wstring wLine(Line.begin(), Line.end());
				OutputDebugString(wLine.c_str());
				__debugbreak();
#elif defined(AG_PLATFORM_LINUX)
				printf("%s", Line.c_str());
#ifdef __clang__
				__builtin_debugtrap();
#else
				__builtin_trap();
#endif
#endif
			}
		}
#else //Just Do Nothing
		template<typename ... Args>
/**
 * @brief This function is used to assert a condition. If the condition is not met, it throws an exception with a formatted message.
 * 
 * @param Condition The condition that needs to be checked.
 * @param fmt A format string for the error message.
 * @param args Arguments for the format string.
 */
void Assert(bool Condition, std::string_view fmt, Args&& ... args){}
#endif
	}

}