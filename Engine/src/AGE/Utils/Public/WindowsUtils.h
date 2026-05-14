#pragma once
#include "Core/Public/Core.h"
#include <ranges>
#include <string>

namespace AGE
{
	class FileDialogs
	{
	public:
		//Return "" if cancelled
		static std::string OpenFile(const std::string& Title, const std::filesystem::path& DefaultPath, std::vector<std::string> Filter);
		static std::string SaveFile(const std::string& Title, const std::filesystem::path& DefaultPath, std::vector<std::string> Filter);
	};
}