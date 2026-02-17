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

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_AGECoreLogger; }
		inline static Ref<spdlog::logger>& GetGameLogger() { return s_AGEGameLogger; }
		inline static std::vector<char>& GetLogs() { return s_Logs; }
		inline static std::vector<size_t>& GetOffsets() { return s_Offsets; }
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
void Assert(bool Condition, std::string_view fmt, Args&& ... args){}
#endif

	}

	namespace GameLogger
	{
		// GameLogger::Trace("This is a logged event {0}", 12);
		template<typename ... Args>
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
void Assert(bool Condition, std::string_view fmt, Args&& ... args){}
#endif
	}

}