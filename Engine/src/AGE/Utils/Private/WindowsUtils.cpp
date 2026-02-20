#include "AGEpch.hpp"
#include "Core/Public/App.h"
#include "Utils/Public/WindowsUtils.h"
#include "Assets/Public/AssetManager.h"
#include <GLFW/glfw3.h>


#ifdef AG_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif defined( AG_PLATFORM_LINUX)
#define GLFW_EXPOSE_NATIVE_X11
#elif defined( AG_PLATFORM_MACOS)
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3native.h>
#include "portable-file-dialogs.h"

namespace AGE
{
#ifdef AG_PLATFORM_WINDOWS
	bool WindowsUtils::FindFileFromDirectory(const char* FileName, std::filesystem::path Path, std::string& OutPath)
	{
		std::filesystem::path CurrentPath;

		if (std::filesystem::is_directory(Path))
		{
			for (auto& p : std::filesystem::recursive_directory_iterator(Path, std::filesystem::directory_options::skip_permission_denied))
			{
				Path = p;
				if (Path.filename() == FileName)
				{
					CurrentPath = Path;
					OutPath = Path.generic_string();
					CoreLogger::Info("File Found at: {0}", CurrentPath.generic_string());
					return true;
				}
				else
				{
					//Logging stuff here
					continue;
				}

			}
		}
		else
		{
			CoreLogger::Info("Path Given is not a directory!");
			return false;
		}
		CoreLogger::Info("File Not Found!");
		return false;
	}
#endif


	std::string FileDialogs::OpenFile(const std::string& Title, const std::filesystem::path& DefaultPath, std::vector<std::string> Filter)
	{
		auto f = pfd::open_file(Title.c_str(), DefaultPath.generic_string(),
			Filter);

		if (f.result().empty())
		{
			return {};
		}

		return {f.result().front()};
	}

	std::string FileDialogs::SaveFile(const std::string& Title, const std::filesystem::path& DefaultPath, std::vector<std::string> Filter)
	{
		auto f = pfd::open_file(Title.c_str(), DefaultPath.generic_string(),
			Filter
			,pfd::opt::force_overwrite);

		if (f.result().empty())
		{
			return {};
		}

		return {f.result().front()};
	}
}