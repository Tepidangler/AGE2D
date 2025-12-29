#include "AGEpch.hpp"

#include "Texture/Public/SubTexture.h"

namespace AGE 
{
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& Texture, const Vector2& Min, const Vector2& Max)
		:m_Texture(Texture)
	{
		m_TexCoords[0] = { Min[0], Min[1] };
		m_TexCoords[1] = { Max[0], Min[1] };
		m_TexCoords[2] = { Max[0], Max[1] };
		m_TexCoords[3] = { Min[0], Max[1] };
	}
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

	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& Texture, const Vector2& SpriteLoc, const Vector2& CellSize, const Vector2& SpriteSize)
	{
		Vector2 min = { (SpriteLoc[0] * CellSize[0]) / (float)Texture->GetWidth(), (SpriteLoc[1] * CellSize[1]) / (float)Texture->GetHeight() };
		Vector2 max = { ((SpriteLoc[0] + SpriteSize[0]) * (float)CellSize[0]) / Texture->GetWidth(), ((SpriteLoc[1] + SpriteSize[1]) * CellSize[1]) / (float)Texture->GetHeight()};

		return CreateRef<SubTexture2D>(Texture, min, max);
	}
}