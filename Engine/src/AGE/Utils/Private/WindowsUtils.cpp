#include "AGEpch.hpp"
#include "Utils/Public/WindowsUtils.h"

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
	/**
 * @brief Opens a file dialog and returns the path of the selected file.
 *
 * This function opens a file dialog with the given title, default path, and filter. If no file is selected, it returns an empty string. 
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
 * @param DefaultPath The default path where the file dialog starts from.
 * @param Filter A vector of strings representing the types of files that can be selected in the dialog.
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