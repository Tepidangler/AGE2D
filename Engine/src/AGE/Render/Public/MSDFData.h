#pragma once
#include "Core/Public/Core.h"

#undef INFINITE
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wint-in-bool-context"
#include "msdf-atlas-gen/msdf-atlas-gen.h"
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "msdf-atlas-gen/msdf-atlas-gen.h"
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(push, 0)
#include "msdf-atlas-gen/msdf-atlas-gen.h"
#pragma warning(pop)
#else
#error "Compiler is not supported with AGE yet"
#endif

namespace AGE
{
	struct MSDFData
	{
		std::vector<msdf_atlas::GlyphGeometry> Glyphs;
		msdf_atlas::FontGeometry FontGeometry;
	};
}