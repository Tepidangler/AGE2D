#include "AGEpch.hpp"

#include "Sprite/Public/SpriteAPI.h"

namespace AGE
{
	void SpriteSheetUtils ::SetTexCoords(const Ref<SubTexture2D> SubTex, QuadProperties& Properties, bool Reverse)
	{
		if (!Reverse)
		{
			Properties.TextureCoords[0] = SubTex->GetTexCoords()[0];
			Properties.TextureCoords[1] = SubTex->GetTexCoords()[1];
			Properties.TextureCoords[2] = SubTex->GetTexCoords()[2];
			Properties.TextureCoords[3] = SubTex->GetTexCoords()[3];
		}
		else
		{
			Properties.TextureCoords[0] = SubTex->GetTexCoords()[1];
			Properties.TextureCoords[1] = SubTex->GetTexCoords()[0];
			Properties.TextureCoords[2] = SubTex->GetTexCoords()[3];
			Properties.TextureCoords[3] = SubTex->GetTexCoords()[2];
		}
	}
}