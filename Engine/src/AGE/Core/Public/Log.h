#pragma once
#include "AGEpch.hpp"
#include "Core.h"

#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)
#include "spdlog/sinks/stdout_color_sinks.h"
#include <string_view>
#include <format>
#include <debugapi.h>





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
	class AGE_API Log
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
			std::wstring wLine(Line.begin(), Line.end());

			OutputDebugString(wLine.c_str());

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
			std::wstring wLine(Line.begin(), Line.end());

			OutputDebugString(wLine.c_str());

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
			std::wstring wLine(Line.begin(), Line.end());

			OutputDebugString(wLine.c_str());

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
			std::wstring wLine(Line.begin(), Line.end());

			OutputDebugString(wLine.c_str());

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
			std::wstring wLine(Line.begin(), Line.end());

			OutputDebugString(wLine.c_str());

		}

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
			std::wstring wLine(Line.begin(), Line.end());

			OutputDebugString(wLine.c_str());

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
			std::wstring wLine(Line.begin(), Line.end());

			OutputDebugString(wLine.c_str());

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
			std::wstring wLine(Line.begin(), Line.end());

			OutputDebugString(wLine.c_str());

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
			std::wstring wLine(Line.begin(), Line.end());

			OutputDebugString(wLine.c_str());

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
			std::wstring wLine(Line.begin(), Line.end());

			OutputDebugString(wLine.c_str());

		}
	}

}




/**
* Leaving these here for compatibility sake, however I will at some point phase out the use of what's below in favor for what is above
*/

//Core Log macros


#define AGE_CORE_TRACE(...) AGE::Log::GetCoreLogger()->trace(__VA_ARGS__); std::cout << "Will be Deprecated soon!" << std::endl;
#define AGE_CORE_INFO(...) AGE::Log::GetCoreLogger()->info(__VA_ARGS__); std::cout << "Will be Deprecated soon!" << std::endl;
#define AGE_CORE_WARN(...) AGE::Log::GetCoreLogger()->warn(__VA_ARGS__); std::cout << "Will be Deprecated soon!" << std::endl;
#define AGE_CORE_ERROR(...) AGE::Log::GetCoreLogger()->error(__VA_ARGS__); std::cout << "Will be Deprecated soon!" << std::endl;
#define AGE_CORE_CRITICAL(...) AGE::Log::GetCoreLogger()->critical(__VA_ARGS__); std::cout << "Will be Deprecated soon!" << std::endl;


// Game Log macros

#define AGE_GAME_TRACE(...) AGE::Log::GetGameLogger()->trace(__VA_ARGS__); std::cout << "Will be Deprecated soon!" << std::endl;
#define AGE_GAME_INFO(...)AGE::Log::GetGameLogger()->info(__VA_ARGS__); std::cout << "Will be Deprecated soon!" << std::endl;
#define AGE_GAME_WARN(...) AGE::Log::GetGameLogger()->warn(__VA_ARGS__); std::cout << "Will be Deprecated soon!" << std::endl;
#define AGE_GAME_ERROR(...) AGE::Log::GetGameLogger()->error(__VA_ARGS__); std::cout << "Will be Deprecated soon!" << std::endl;
#define AGE_GAME_CRITICAL(...) AGE::Log::GetGameLogger()->critical(__VA_ARGS__); std::cout << "Will be Deprecated soon!" << std::endl;
