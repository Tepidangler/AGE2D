#pragma once
#include "Core/Public/Core.h"


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
		static std::string OpenFile(const char* Filter);
		static std::string SaveFile(const char* Filter);
	};
}