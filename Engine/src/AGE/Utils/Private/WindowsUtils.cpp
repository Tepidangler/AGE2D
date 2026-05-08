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
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-conversion"
#include "portable-file-dialogs.h"

#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma clang diagnostic ignored "-Wsign-conversion"
#include "portable-file-dialogs.h"
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(push, 0)
#include "portable-file-dialogs.h"
#pragma warning(pop)
#else
#error "Compiler is not supported with AGE yet"
#endif

namespace AGE
{
#ifdef AG_PLATFORM_WINDOWS
	/**
 * @brief Searches for a file in the given directory and its subdirectories.
 * 
 * This function takes a filename, a path to search from, and an output parameter to store the found file's path. It returns true if it finds the file, false otherwise.
 * 
 * @param FileName The name of the file to be searched for.
 * @param Path The directory to start searching from.
 * @param OutPath An output parameter that will contain the full path of the found file.
 * 
 * @return Returns true if the file is found, false otherwise.
 */
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


	/**
 * @brief Opens a file dialog and returns the path of the selected file.
 *
 * This function opens an open file dialog with the given title, default path, and filter. If no file is selected, it returns an empty string. 
 * The returned string contains the path of the first selected file.
 *
 * @param Title The title of the file dialog.
 * @param DefaultPath The default path for the file dialog.
 * @param Filter A vector of strings representing the filter for the file dialog.
 *
 * @return Returns a string containing the path of the selected file, or an empty string if no file is selected.
 */
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

	/**
 * @brief This function opens a file dialog and allows the user to select a file for saving.
 * 
 * @param Title The title of the file dialog.
 * @param DefaultPath The default path where the file dialog will start from.
 * @param Filter A vector of strings representing the file types that can be selected in the dialog.
 * 
 * @return Returns a string containing the path to the selected file, or an empty string if no file was selected.
 */
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