#include "AGEpch.hpp"

#include "Texture/Public/SubTexture.h"

namespace AGE 
{
	/**
 * @brief Constructs a SubTexture2D object from a reference to a Texture2D, and two Vector2 objects representing the minimum and maximum texture coordinates.
 * @param Texture A const reference to a Texture2D object. This is the texture that the subtexture will be created for.
 * @param Min A const reference to a Vector2 object. This represents the bottom-left corner of the subtexture within the parent texture.
 * @param Max A const reference to a Vector2 object. This represents the top-right corner of the subtexture within the parent texture.
 */
SubTexture2D::SubTexture2D(const Ref<Texture2D>& Texture, const Vector2& Min, const Vector2& Max)
		:m_Texture(Texture)
	{
		m_TexCoords[0] = { Min[0], Min[1] };
		m_TexCoords[1] = { Max[0], Min[1] };
		m_TexCoords[2] = { Max[0], Max[1] };
		m_TexCoords[3] = { Min[0], Max[1] };
	}
	/**
 * @brief Constructor for SubTexture2D class. It takes a void pointer to data and initializes the texture, texcoords, width and height based on the data provided.
 * 
 * @param Data A void pointer to the data from which the initialization will be done. The exact type of this data is unknown.
 */
SubTexture2D::SubTexture2D(void* Data)
	{

		SubTexture2D* Tex = (SubTexture2D*)Data;
		m_Texture = Tex->GetTexture();
		for (int i = 0; i < 4; i++)
		{
			m_TexCoords[i] = Tex->GetTexCoords()[i];

		}
		m_Width = Tex->GetWidth();
		m_Height = Tex->GetHeight();
	}

	/**
 * @brief Creates a subtexture from given texture at specified coordinates.
 * 
 * This function takes in Texture2D, Vector2 (SpriteLoc, CellSize, SpriteSize) to calculate the min and max UVs for SubTexture2D.
 */
Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& Texture, const Vector2& SpriteLoc, const Vector2& CellSize, const Vector2& SpriteSize)
	{
		Vector2 min = { (SpriteLoc[0] * CellSize[0]) / (float)Texture->GetWidth(), (SpriteLoc[1] * CellSize[1]) / (float)Texture->GetHeight() };
		Vector2 max = { ((SpriteLoc[0] + SpriteSize[0]) * (float)CellSize[0]) / (float)Texture->GetWidth(), ((SpriteLoc[1] + SpriteSize[1]) * CellSize[1]) / (float)Texture->GetHeight()};

		return CreateRef<SubTexture2D>(Texture, min, max);
	}
}