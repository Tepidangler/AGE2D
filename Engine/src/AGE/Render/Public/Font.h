#pragma once
#include "Core/Public/Core.h"
#include "Texture/Public/Texture.h"

namespace AGE
{
	struct MSDFData;

	class AGEFont
	{
	public:
		AGEFont(const std::filesystem::path& Font);
		~AGEFont();

		const MSDFData* GetMSDFData() const { return m_Data; }
		Ref<Texture2D> GetAtlasTexture() const { return m_AtlasTexture; }

		void SaveFont() const;
		void LoadFont(const std::string& FontName);

		static Ref<AGEFont> GetDefault();

	private:
		MSDFData* m_Data;
		Ref<Texture2D> m_AtlasTexture;
	};
}