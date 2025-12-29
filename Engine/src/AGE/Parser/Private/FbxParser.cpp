#include "AGEpch.hpp"
#include "Parser/Public/FbxParser.h"
#include "Core/Public/Log.h"
#include "Assets/Public/AssetManager.h"



namespace AGE
{
	FBXParser* FBXParser::s_Instance = nullptr;

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
	void FBXParser::FreeScene(ufbx_scene* scene)
	{
		ufbx_free_scene(scene);
	}
}