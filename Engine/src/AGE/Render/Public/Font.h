#pragma once
#include "Core/Public/Core.h"
#include "Texture/Public/Texture.h"

namespace AGE
{
	struct MSDFData;

	class Font
	{
	public:
		Font(const std::filesystem::path& Font);
		~Font();

		const MSDFData* GetMSDFData() const { return m_Data; }
		Ref<Texture2D> GetAtlasTexture() const { return m_AtlasTexture; }

		static Ref<Font> GetDefault();

	private:
		MSDFData* m_Data;
		Ref<Texture2D> m_AtlasTexture;
	};
}