#pragma once

#include "Core/Public/Core.h"
#include <filesystem>
#include <ufbx.h>

namespace AGE
{
	class FBXParser
	{
	public:
		FBXParser() = default;

		static FBXParser& Get()
		{
			if (!s_Instance)
			{
				s_Instance = new FBXParser();
			}
			return *s_Instance;
		}

		static ufbx_scene* LoadFile(const std::filesystem::path& Path);

		static void FreeScene(ufbx_scene* scene);

	private:
		static FBXParser* s_Instance;
	};
}