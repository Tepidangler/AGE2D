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