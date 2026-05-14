#pragma once

#include "Core/Public/Core.h"
#include <filesystem>
#include <ufbx.h>

namespace AGE
{
	class FBXParser
	{
	public:
		/**
 * @brief Default constructor for the FBXParser class.
 *
 * This function initializes an instance of the FBXParser class with default values. It does not perform any specific operations or require any parameters to be set. 
 *
 * @return A new instance of the FBXParser class with all fields initialized to their default values.
 */
/**
 * @brief Default constructor for the FBXParser class.
 */
FBXParser() = default;

		/**
 * @brief This function returns a reference to the singleton instance of the FBXParser class. If an instance does not already exist, it will be created.
 * @return A reference to the single instance of the FBXParser class.
 */
/**
 * @brief This function returns a reference to the singleton instance of the FBXParser class. If an instance does not already exist, it will be created.
 * @return A reference to the FBXParser instance.
 */
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