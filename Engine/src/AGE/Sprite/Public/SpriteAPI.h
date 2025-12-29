#pragma once
#include "Texture/Public/SubTexture.h"
#include "Structs/Public/DataStructures.h"


namespace AGE
{
	class SpriteSheetUtils
	{
	public:

		static void SetTexCoords(const Ref<SubTexture2D> SubTex, QuadProperties& Properties, bool Reverse = false);

	private:

	};
}