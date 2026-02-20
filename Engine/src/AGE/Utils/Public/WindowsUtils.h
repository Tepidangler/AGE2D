#pragma once
#include "Core/Public/Core.h"
#include <ranges>
#include <string>

namespace AGE
{
	class WindowsUtils
	{
	public:

		static bool FindFileFromDirectory(const char* FileName, std::filesystem::path Path, std::string& OutPath);
	};

	class FileDialogs
	{
	public:
		//Return "" if cancelled
		static std::string OpenFile(const std::string& Title, const std::filesystem::path& DefaultPath, std::vector<std::string> Filter);
		static std::string SaveFile(const std::string& Title, const std::filesystem::path& DefaultPath, std::vector<std::string> Filter);
	};
}