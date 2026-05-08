#include "AGEpch.hpp"
#include "Parser/Public/FbxParser.h"
#include "Core/Public/Log.h"
#include "Assets/Public/AssetManager.h"



namespace AGE
{
	FBXParser* FBXParser::s_Instance = nullptr;

	/**
 * @brief Loads a FBX file into memory and returns the loaded scene.
 * 
 * This function loads an FBX file from the specified path, adjusting transforms if necessary. The target axes are left-handed with Y as up, and the target unit is set to be 0.01 meters. If the loading fails for any reason, it logs an error message and returns nullptr.
 * 
 * @param Path The file system path of the FBX file to load.
 * @return A pointer to the loaded ufbx_scene if successful, otherwise nullptr.
 */
ufbx_scene* FBXParser::LoadFile(const std::filesystem::path& Path)
	{
		ufbx_space_conversion Flags = ufbx_space_conversion::UFBX_SPACE_CONVERSION_ADJUST_TRANSFORMS;
		ufbx_load_opts Opts{};
		Opts.target_axes = ufbx_axes_left_handed_y_up;
		Opts.target_unit_meters = .01f;
		Opts.space_conversion = Flags;

		ufbx_error Error;

		ufbx_scene* scene = ufbx_load_file(Path.string().c_str(), &Opts, &Error);

		if (!scene)
		{
			CoreLogger::Error("Failed to load: {}!\n\tReturning empty struct!", Path.string());
			return nullptr;
		}
		
		return scene;
	}
	/**
 * @brief This function frees an allocated ufbx_scene.
 * 
 * @param scene Pointer to the ufbx_scene that needs to be freed.
 * 
 * @return None
 */
void FBXParser::FreeScene(ufbx_scene* scene)
	{
		ufbx_free_scene(scene);
	}
}