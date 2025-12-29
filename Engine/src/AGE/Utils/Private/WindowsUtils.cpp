#include "AGEpch.hpp"
#include "Core/Public/App.h"
#include "Utils/Public/WindowsUtils.h"
#include "Assets/Public/AssetManager.h"
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace AGE
{
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


	std::string FileDialogs::OpenFile(const char* Filter)
	{
		OPENFILENAMEA OFN;

		CHAR szFile[260] = { 0 };

		ZeroMemory(&OFN, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = glfwGetWin32Window((GLFWwindow*)App::Get().GetDeviceManager().GetWindow().GetNativeWindow());
		OFN.lpstrFile = szFile;
		OFN.nMaxFile = sizeof(szFile);
		OFN.lpstrFilter = Filter;
		OFN.lpstrInitialDir = AssetManager::Get().GetGameContentPath().string().c_str();
		OFN.nFilterIndex = 1;
		OFN.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&OFN) == TRUE)
		{
			return OFN.lpstrFile;
		}

		return std::string();
	}

	std::string FileDialogs::SaveFile(const char* Filter)
	{
		OPENFILENAMEA OFN;

		CHAR szFile[260] = { 0 };

		ZeroMemory(&OFN, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = glfwGetWin32Window((GLFWwindow*)App::Get().GetDeviceManager().GetWindow().GetNativeWindow());
		OFN.lpstrFile = szFile;
		OFN.nMaxFile = sizeof(szFile);
		OFN.lpstrFilter = Filter;
		OFN.lpstrInitialDir = AssetManager::Get().GetGameContentPath().string().c_str();
		OFN.nFilterIndex = 1;
		OFN.lpstrDefExt = std::strchr(Filter, '\0') + 1;
		OFN.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR | OFN_OVERWRITEPROMPT;

		if (GetSaveFileNameA(&OFN) == TRUE)
		{
			return OFN.lpstrFile;
		}
		return std::string();
	}
}