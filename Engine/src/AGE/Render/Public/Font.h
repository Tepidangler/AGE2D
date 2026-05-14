#pragma once
#include "Core/Public/Core.h"
#include "Texture/Public/Texture.h"

namespace AGE
{
	struct MSDFData;

	class AGEFont : public std::enable_shared_from_this<AGEFont>
	{
	public:
		AGEFont(const std::filesystem::path& Font, bool LoadingDefault = false);
		~AGEFont();

		/**
 * @brief Retrieves the MSDF data associated with this object.
 * @return A pointer to the MSDF data, or nullptr if no data is available.
 */
const MSDFData* GetMSDFData() const { return m_Data; }
		/**
 * @brief Returns the atlas texture reference.
 *
 * This function returns a constant reference to the atlas texture stored in the object. The returned reference can be used to access and manipulate the atlas texture data.
 *
 * @return A constant reference to the atlas texture.
 */
Ref<Texture2D> GetAtlasTexture() const { return m_AtlasTexture; }

		void SaveFont();
		void LoadFont(const std::string& FontName);

		static Ref<AGEFont> GetDefault();

		const std::string& GetFontName() const { return m_FontName; }
		uint64_t GetAssetID() const { return m_AssetID; }

	private:
		void SaveDefaultFont();
		void LoadDefaultFont(const std::string& FontName);
		MSDFData* m_Data;
		Ref<Texture2D> m_AtlasTexture;
		std::string m_FontName;
		uint64_t m_AssetID;
	};
}