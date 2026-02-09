#pragma once
#include "Core/Public/Core.h"

#undef INFINITE
#include "msdf-atlas-gen/msdf-atlas-gen.h"

namespace AGE
{
	struct MSDFData
	{
		std::vector<msdf_atlas::GlyphGeometry> Glyphs;
		msdf_atlas::FontGeometry FontGeometry;
	};
}